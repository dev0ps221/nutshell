#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[])
{
    FILE *fp1, *fp2;
    char ch;
    if(!argv[1] || !argv[2])
    {
        printf("Usage: %s <source file> <destination file>\n", argv[0]);
        exit(1);
    }
    fp1 = fopen(argv[1], "r");
    fp2 = fopen(argv[2], "w");
    while((ch = fgetc(fp1)) != EOF)
        fputc(ch, fp2);
    fclose(fp1);
    fclose(fp2);
}