#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;

//定义人数据结构
typedef struct{
    BYTE m_name[10];   //姓名
    BYTE m_age;
    BYTE m_sex;   //性别，=0标识男性，=1标识女性
}people_t;


int main(int argc,char **argv)
{
    people_t tom;
    memset(&tom,0,sizeof(people_t));
    memcpy(tom.m_name,"tom",3);
    tom.m_age=15;
    tom.m_sex=0;

    printf("tom info:\n");
    printf("\tname: %s.\n",tom.m_name);
    printf("\tage: %d.\n",tom.m_age);
    if(tom.m_sex==0)
        printf("\tsex: male.\n");
    else
        printf("\tsex: female.\n");

    return 0;
}
