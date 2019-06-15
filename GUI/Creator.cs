using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TICREATE
{
    class Creator
    {
       
        public static string hex(string name,byte[] Bytes)
        {
            String PRE = "char  " + name + "[" + Bytes.Length + "] = {\n";
            char[] Output = new char[5 * Bytes.Length + (int)(Bytes.Length / 10)+1];
            String buf;
            int off = 0;
            for (int i = 0; i < Bytes.Length - 1; i++)
            {
                Output[5 * i + off] = '0';
                Output[5 * i + 1 + off] = 'x';
                buf = Bytes[i].ToString("X2");
                Output[5 * i + 2 + off] = buf[0];
                Output[5 * i + 3 + off] = buf[1];
                Output[5 * i + 4 + off] = ',';
                if ((i + 1) % 10 == 0)//every 10 times
                {
                    Output[5 * i + 5 + off] = '\n';
                    off++;
                }
            }
            //last one without ','
            Output[5 * (Bytes.Length - 1) + off] = '0';
            Output[5 * (Bytes.Length - 1) + 1 + off] = 'x';
            buf = Bytes[(Bytes.Length - 1)].ToString("X2");
            Output[5 * (Bytes.Length - 1) + 2 + off] = buf[0];
            Output[5 * (Bytes.Length - 1) + 3 + off] = buf[1];
            String result = PRE + new string(Output,0,off+5*Bytes.Length-1);
            result += "};";
            return (result);
        }
        public static byte[] convertImage(string path, char format,out int resx,out int resy)
        {
            switch (format)
            {
                case '2':
                    //  Console.WriteLine("Col:"+COL222(Color.FromArgb(0,100,200)));
                    Bitmap IN = new Bitmap(path);
                    byte[] OUTPUT = new byte[(int)(IN.Width * IN.Height)];
                    Console.WriteLine("Image Size:" + (IN.Width * IN.Height));
                    for (int x = 0; x < IN.Width; x++)
                    {
                        for (int y = 0; y < IN.Height; y++)
                        {
                            OUTPUT[(int)(y * IN.Width + x)] = COL222(IN.GetPixel(x, y));
                        }
                    }
                    resx = IN.Height;
                    resy = IN.Width;
                    return (OUTPUT);
                case '1':
                    Console.WriteLine("1bpp selected:" + path);
                    Bitmap IN2 = new Bitmap(path);
                    int flipvalue = 380;
                    UInt64 total = 0;
                    for(int x = 0; x < IN2.Width; x++)
                    {
                        for (int y = 0; y < IN2.Height; y++)
                        {
                            total += (UInt64)(IN2.GetPixel(x, y).R + IN2.GetPixel(x, y).G + IN2.GetPixel(x, y).B);
                        }
                    }
                    flipvalue = (int)(total / (UInt64)(IN2.Height * IN2.Width));

                    Console.WriteLine("conversion started flipvalue:"+flipvalue);
                    bool[] OUTPUT2 = new bool[IN2.Height * IN2.Width];
                    for (int x = 0; x < IN2.Width; x++)
                    {
                        for (int y = 0; y < IN2.Height; y++)
                        {
                            OUTPUT2[y * IN2.Width + x] = COL1(IN2.GetPixel(x, y),flipvalue);
                        }
                    }
                    Console.WriteLine("saving...");
                    byte[] output2 = booltobyte(OUTPUT2);
                    resx = IN2.Height;
                    resy = IN2.Width;
                    return(output2);
                case '3':
                    //Text
                    resy = 320;
                    resx = 240;
                    List<byte> D = File.ReadAllBytes(path).ToList();
                    D.Add(0x00);
                    return (D.ToArray());
            }
            resx = 0;
            resy = 0;
            return (new byte[]{ 0xFF,0xFF });
        }
        public static byte[] booltobyte(bool[] input)
        {
            Console.WriteLine("bool2byte");
            byte[] OUT = new byte[(int)Math.Round(input.Length / 8 + 1.5)];
            for (int i = 0; i < OUT.Length; i++)
            {
                OUT[i] = 0;
            }
            for (int i = 0; i < input.Length; i++)
            {
                int bytepos = i % 8;
                // Console.WriteLine("bytepos:"+bytepos);
                int byteindex = (int)(i / 8 + 0.99);
                //  Console.WriteLine("byteindex:" + byteindex);
                if (input[i])
                {
                    OUT[byteindex] |= (byte)(128 >> bytepos);
                }
            }
            return (OUT);
        }
        public static bool COL1(Color input,int flipvalue)
        {
            if ((input.R + input.G + input.B) > flipvalue)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        public static byte COL222(Color input)
        {
            return ((byte)(192 + ((input.R & 0b11000000) >> 2) | ((input.G & 0b11000000) >> 4) | ((input.B & 0b11000000) >> 6)));
        }
        public static string file(string[] paths,string[] formats)
        {
            List<string> temp = new List<string>();
            temp = paths.ToList();
            temp.Remove("");
            paths = temp.ToArray();
            string output = "#include \"GUI.c\"" + Environment.NewLine;
            for(int i = 0;i<paths.Length;i++)
            {
                switch (formats[i])
                {
                    case "rgb":
                        output += IMG(paths[i], '2');//Color
                        break;
                    case "1bpp":
                        output += IMG(paths[i], '1');//Black White
                        break;
                    case "txt":
                        output += IMG(paths[i], '3');//Black White
                        break;
                }
                    Console.WriteLine("path:" + paths[i]);
            }
            output += Menue(paths);
            return (output+Environment.NewLine);
        }
        public static string Menue(string[] paths)
        {
            string output = "void FileBrowser(){"+Environment.NewLine;
            
            output += "void(*OPTIONSENTERR[]) = {";
            foreach(string path in paths)
            {
                output += Path.GetFileName(path).Replace('.', '_') + "_SHOW,";
            }
            output = output.Substring(0, output.Length - 1);
            output += "};";
            output += Environment.NewLine;

            output += "char* namE[] = { ";
            int longest = 0;
            foreach (string path in paths)
            {
                output += "\"" + Path.GetFileName(path)+ "\""  + ",";
                if (Path.GetFileName(path).Length > longest)
                {
                    longest = Path.GetFileName(path).Length;
                }
            }
            output = output.Substring(0, output.Length - 1);
            output += " };" + Environment.NewLine;
            //init all iage structs
            foreach (string path in paths)
            {
                output += Path.GetFileName(path).Replace('.', '_') + "_setup();" + Environment.NewLine;
            }
           
            output += "GUI_SELECT_MENUE_VERTICAL_XYS(namE, "+paths.Count()+", OPTIONSENTERR, 1,10,20," +longest+");" + Environment.NewLine;
    
            output += "GUI_HANDLE();"+Environment.NewLine;
            output += "}";
            return (output);
        }
        public static string IMG(string path,char format)
        {
            return (Imagestring(path, format) + Imgcode(path));
        }
        public static string Imagestring(string path, char format)
        {
            int resx;
            int resy;
            byte[] A = convertImage(path, format, out resy, out resx);
            String varname = Path.GetFileName(path).Replace('.', '_');
            String IMG = hex(varname+"_data", A);
            String RES =
               "uint16_t " + varname + "_resx = " + resx.ToString() + " ;\n" +
               "uint16_t " + varname + "_resy = " + resy.ToString() + " ;\n";
            char typ = (char)0;
            switch (format)
            {
                case '1':
                    typ = '1';
                    break;
                case '2':
                    typ = '0';
                    break;
                case '3':
                    typ = '2';
                    break;
            }
            Console.WriteLine("Done");
            string result = IMG + " \n" + RES + "char " + varname + "_type" + " = " + typ + " ;";
           // Console.WriteLine(result);
            return (result);
  
        }
        public static string Imgcode(string path)
        {
            string p = Path.GetFileName(path).Replace('.', '_');
            string stru = "struct Image "+p+"_struct ;"+Environment.NewLine;
            string setup = "void " + p + "_setup(){"+Environment.NewLine+
            p + "_struct.data = " + p+"_data;"+Environment.NewLine +
            p + "_struct.resx = " + p + "_resx;" + Environment.NewLine +
            p + "_struct.resy = " + p + "_resy;" + Environment.NewLine +
            p + "_struct.type = " + p + "_type;" + Environment.NewLine +
                "}"+Environment.NewLine;
            string code = "void " + p + "_SHOW(){" + Environment.NewLine +
                "GUI_DRAW_IMAGE(&"+ p + "_struct"+", 0, 0);" + Environment.NewLine +
                "while(os_GetKey()!=5);" + Environment.NewLine+
                "}";
            return (stru+setup+code);
        }
    }
}
