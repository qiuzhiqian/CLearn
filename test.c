#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * 其他未提及的知识要点:
 * 1、与或非，取反，左移右移
 * 2、i++,++i,*p++=x等
 * 3、main函数的参数
*/

//理解这些定义有什么作用
#define DB_LEVEL    0   //调试信息输出阀值

#define DB_NORMAL   1   //普通调试信息输出
#define DB_WARN     2   //警告调试信息输出

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;

//学习枚举的使用
enum sex_e{
    male=0,     //搞清楚枚举定义时的成员赋值机制
    female,
};

//搞清楚结构体的多种定义方式，以及typedef的重定义功能
//定义银行卡数据结构
typedef struct{
    BYTE m_bankName[16];    //银行名，此处如果用指针的话会有什么不同？
    int m_money;            //金额
}BankCard_t;

//定义人数据结构
struct people{
    BYTE *m_name;   //姓名，此处如果用数组的话会有什么不同？
    BYTE m_age;
    enum sex_e m_sex;   //性别
    struct people *m_friend;    //朋友，此处为难点
    int m_friendCnt;    //朋友个数
    BankCard_t m_bc;    //银行卡，此处如果用结构体指针的话会有什么不同？
    void (*m_run)(BYTE *name);  //拥有的功能,跑步，搞清楚的函数指针的回调机制？
};

//对调试信息输出的重定义，增加输出优先级，思考使用while(0)的用途
#define debug(debug, x)  do { if (debug >= DB_LEVEL) {	printf x ;	}} while(0)

void run(BYTE *name)
{
    debug(DB_NORMAL,("%s is running\n",name));
}

//去女子学校上学
int GoFemaleSchool(struct people *p)
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
    BYTE tempBank[]="zhaoshang bank";
    struct people tom;
    memset(&tom,0,sizeof(struct people));
    tom.m_name=malloc(3);
    memcpy(tom.m_name,"tom",3);
    tom.m_age=15;
    tom.m_sex=male;

//----此处为难点
    struct people *friend=NULL;
    friend=malloc(sizeof(struct people)*3);
    struct people *tmpfriend=friend;

    tmpfriend->m_name=malloc(4);
    memcpy(tmpfriend->m_name,"jack",4);
    tmpfriend++;

    tmpfriend->m_name=malloc(4);
    memcpy(tmpfriend->m_name,"mary",4);
    tmpfriend++;

    tmpfriend->m_name=malloc(5);
    memcpy(tmpfriend->m_name,"james",5);
    tmpfriend++;

    tom.m_friend=friend;
    tom.m_friendCnt=3;

    memcpy(tom.m_bc.m_bankName,tempBank,sizeof(tempBank));
    tom.m_bc.m_money=8000;
    tom.m_run=run;

    debug(DB_NORMAL,("tom info:\n"));
    debug(DB_NORMAL,("\tname: %s\n",tom.m_name));
    if(tom.m_sex==male)
        debug(DB_NORMAL,("\tsex: male\n"));
    else
        debug(DB_NORMAL,("\tsex: female\n"));

    debug(DB_NORMAL,("\tfriend: \n"));
    tmpfriend=tom.m_friend;
    for(int i=0;i<tom.m_friendCnt;i++)
    {
        debug(DB_NORMAL,("\t\t%s.\n",tmpfriend->m_name));
        tmpfriend++;
    }

    debug(DB_NORMAL,("\thas a bank card:\n"));
    debug(DB_NORMAL,("\t\tname: %s\n",tom.m_bc.m_bankName));
    debug(DB_NORMAL,("\t\tmoney: %d\n",tom.m_bc.m_money));
    if(tom.m_run!=NULL)
    {
        debug(DB_NORMAL,("\t"));
        tom.m_run(tom.m_name);
        debug(DB_NORMAL,("\n"));
    }

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
