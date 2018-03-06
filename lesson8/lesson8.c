#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//对调试信息进行分类，并控制可输出的级别
#define DB_LEVEL    0   //调试信息输出阀值

#define DB_NORMAL   1   //普通调试信息输出
#define DB_WARN     2   //警告调试信息输出

//由于上一节定义的debug在使用的时候结尾不能添加;号，这样会导致代码很奇怪，改造如下，就可以使用debug(....);了
#define debug(db ,x) do{ if( db>=DB_LEVEL ) printf x;}while(0)

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;

//引入枚举来定义性别，枚举同样可以用typedef来重定义类型，从而使得调用简洁，同时需要清楚枚举内部=的作用和递增机制
typedef enum {
    male=0,     //搞清楚枚举定义时的成员赋值机制
    female,
}sex_e;

//定义银行卡数据结构
typedef struct{
    BYTE m_bankName[16];    //银行名，此处如果用指针的话会有什么不同？
    int m_money;            //金额
}BankCard_t;

//定义人数据结构
typedef struct{
    BYTE *m_name;   //姓名，因为姓名的长度不固定，所以此处改用指针表示，然后通过malloc来分配空间
    BYTE m_age;
    sex_e m_sex;   //性别，=male标识男性，=female标识女性
    BankCard_t m_bc;    //银行卡
    void (*m_run)(BYTE *name);  //拥有的功能,跑步，函数指针的定义及使用
}people_t;

void run(BYTE *name)
{
    debug(DB_NORMAL,("%s is running\n",name));
}

int main(int argc,char **argv)
{
    people_t tom;
    memset(&tom,0,sizeof(people_t));
    //给name分配空间
    tom.m_name=malloc(sizeof(3));    //由于我们需要给name赋值为tom,为3个字节，所以分配3个字节的空间
    if(tom.m_name==NULL)
    {
        debug(DB_WARN,("error:malloc faild\n"));     //思考此处为什么不能用;号，如果要用debug应该怎样构造
    }
    memcpy(tom.m_name,"tom",3);     //name赋值
    tom.m_age=15;
    tom.m_sex=male;

    BYTE tempBank[]="zhaoshang bank";
    memcpy(tom.m_bc.m_bankName,tempBank,sizeof(tempBank));
    tom.m_bc.m_money=8000;

    tom.m_run=run;      //函数指针赋值

    debug(DB_NORMAL,("tom info:\n"));
    debug(DB_NORMAL,("\tname: %s.\n",tom.m_name));
    debug(DB_NORMAL,("\tage: %d.\n",tom.m_age));
    if(tom.m_sex==male)
        debug(DB_NORMAL,("\tsex: male.\n"));
    else
        debug(DB_NORMAL,("\tsex: female.\n"));

    debug(DB_NORMAL,("\thas a bank card:\n"));
    debug(DB_NORMAL,("\t\tname: %s.\n",tom.m_bc.m_bankName));
    debug(DB_NORMAL,("\t\tmoney: %d.\n",tom.m_bc.m_money));

    if(tom.m_run!=NULL)
    {
        debug(DB_NORMAL,("\t"));
        tom.m_run(tom.m_name);  //函数指针回调
        debug(DB_NORMAL,("\n"));
    }

    return 0;
}
