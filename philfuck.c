/*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
*
* This is Phil's super simple and minimalistic Brainfuck interpreter. 
* Have fun.
* 
* Requirements:
*   - gcc
*/


#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *in;
FILE *out;

void fuckin(char c){
    switch(c){
        case '+':fputs("arr[idx]++;\n",out);break;
        case '-':fputs("arr[idx]--;\n",out);break;
        case '>':fputs("idx++;\n",out);break;
        case '<':fputs("idx--;\n",out);break;
        case '[':fputs("while(arr[idx]!=0){\n",out);break;
        case ']':fputs("}\n",out);break;
        case ',':fputs("arr[idx]=getchar();\n",out);break;
        case '.':fputs("putchar(arr[idx]);\n",out);break;
        default: break;
        }
}

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Usage:\n./philfuck [brainfuck-source-file]\n");
        return(EXIT_SUCCESS);
        }    
    in = fopen(argv[1],"r");
    if(in == NULL){
        printf("file not found\n");
        return(EXIT_FAILURE);
        }
    out = fopen("bf.c","w");
    fputs("#include<stdio.h>\nvoid main(){\n",out);
    fputs("char arr[30000]={0};\nint idx = 0;",out);
    char c = fgetc(in);
    while(c!=EOF){
        fuckin(c);
        putchar(c);
        c = fgetc(in);
    }
    fputs("}",out);
    fclose(in);
    fclose(out);
    char cmd[255] = "gcc ";
    strcat(cmd,"bf.c");
    strcat(cmd, " -o ");
    strcat(cmd,argv[1]);
    strcat(cmd,".out");
    system(cmd);
    unlink("bf.c");
    return(EXIT_SUCCESS);
}
