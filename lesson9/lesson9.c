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

//去女子学校上学
int GoFemaleSchool(people_t *p)     //结构体指针传参的使用
{
    if(p==NULL)
    {
        debug(DB_WARN,("p is invaild.\n"));
        return -1;
    }
    
    if(p->m_name==NULL)
    {
        debug(DB_WARN,("p->m_name is invaild.\n"));
        return -1;
    }

    if(p->m_sex!=female)
    {
        debug(DB_WARN,("性别不符合入学条件.\n"));
        return -2;
    }

    if(p->m_age<6)
    {
        debug(DB_WARN,("age=%d,年龄不符合入校条件.\n",p->m_age));
        return -2;
    }

    if(p->m_bc.m_money<1000)
    {
        debug(DB_WARN,("money=%d,学费不够，不能入学.\n",p->m_bc.m_money));
        return -2;
    }

    if(p->m_run!=NULL)
    {
        return 0;
    }
    else
    {
        debug(DB_WARN,("该同学时残疾人员.\n",p->m_bc.m_money));
        return -1;
    }
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

    tom.m_run(tom.m_name);  //函数指针回调

    int iRet = GoFemaleSchool(&tom);    //tom入学
    switch(iRet)
    {
        case -1:
            debug(DB_NORMAL,("this is invaild people.\n"));
            break;
        case -2:
            debug(DB_NORMAL,("can't go to this school.\n"));   //条件不足，无法进入该学校
            break;
        case 0:
            debug(DB_NORMAL,("go to school success.\n"));      //成功入学
            break;
        case 1:
            debug(DB_NORMAL,("go to school success.but go to special class.\n"));  //成功入学，但是需要分配到特殊班级
            break;
        default:
            debug(DB_NORMAL,("invaild return value.\n"));      //无效的返回值
    }

    return 0;
}
