#include "MEMFIND.h"
char* MEMFIND(char*Key,int length,int addr,int endaddr){
  int currentlength = 0;
    while(addr<endaddr ){
        if(*(char*)(addr) == Key[currentlength]){
            //great we found a matching char
            currentlength++;
        }else{
            currentlength = 0;
        }  
        if(currentlength == length){
            return((char*)addr-length);
        }
        addr++;
    }
    return((char*)0);
}