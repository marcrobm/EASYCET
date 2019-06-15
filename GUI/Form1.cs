using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TICREATE
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
           
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            UInt32 storage = 0;
            OpenFileDialog OPEN = new OpenFileDialog();
            OPEN.Filter = "All Files (*.*)|*.*";
            OPEN.FilterIndex = 1;
            OPEN.Multiselect = true;
            if (OPEN.ShowDialog() == DialogResult.OK)
            {
                string[] Files = OPEN.FileNames; //used when Multiselect = true           
                foreach(string s in Files)
                {
                    textBox1.Text += s + Environment.NewLine;
                    switch (Path.GetExtension(s))
                    {
                        case ".jpeg":
                        case ".jpg":
                        case ".png":
                            textBox2.Text += "1bpp" + Environment.NewLine;
                            break;
                        case ".txt":
                            textBox2.Text += "txt" + Environment.NewLine;
                            break;
                    }
                }                
            }
            Console.WriteLine("Added new Files");
            updatestorage();
        }
        private void updatestorage()
        {
            try
            {
                int storage = 0;
                for (int e = 0; e < textBox1.Lines.Count(); e++)
                {
                    if (textBox2.Lines.Count() > e )
                    {
                        switch (textBox2.Lines[e])
                        {
                            case "1bpp":
                                Bitmap A = new Bitmap(textBox1.Lines[e]);
                                storage += ((A.Width * A.Height) / 8);
                                break;
                            case "rgb":
                                Bitmap AD = new Bitmap(textBox1.Lines[e]);
                                storage += (AD.Width * AD.Height);
                                break;
                        }
                    }
                }
                if ((int)((storage / 120000) * 100) < 100)
                {
                    progressBar1.Value = (int)(((double)storage / 120000.0) * 100);
                    progressBar1.Refresh();
                }
                else
                {
                    progressBar1.Value = 100;
                    progressBar1.Refresh();
                }
                Console.WriteLine(storage);
            }catch(Exception e)
            {

            }
        }
        private void button2_Click(object sender, EventArgs e)
        {
            Create();
        }
        void Create()
        {
            this.BackColor = Color.Red;
            SaveFileDialog OPEN = new SaveFileDialog();
            OPEN.Title = "save c header";
            OPEN.Filter = "All Files (*.*)|*.*";
            OPEN.FilterIndex = 1;
            if (OPEN.ShowDialog() == DialogResult.OK)
            {
                File.WriteAllText(OPEN.FileName, Creator.file(textBox1.Lines, textBox2.Lines));
            }
            this.BackColor = Color.White;
        }
        void IMGCONVERT(string image,string bin,string type)
        {
            ProcessStartInfo startInfo = new ProcessStartInfo();
            startInfo.FileName = "IMGCONV.exe";
            startInfo.Arguments = image + " "+ bin + type;
            Process.Start(startInfo);
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            updatestorage();
        }

        private void progressBar1_Click(object sender, EventArgs e)
        {
            updatestorage();
        }
    }
}
