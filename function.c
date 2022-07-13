#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "FlightBookTicketSystem.h"

#pragma warning(disable:4996) //visual studio安全性问题scanf,getchar
#pragma warning(disable:6031) //visual studio 返回值被忽略问题strcmp

/* 防止用户乱输入其他的字符，规范用户输入整数 */
int judge_int(void)
{
    int len, num = 0, arg = 1;
    char word[10] = { 0 };
    int m, j = 1, k;
    while (j)
    {
        scanf("%s", word);
        len = strlen(word);
        for (m = 0;m < len;m++)
        {
            if (word[m] < '0' || word[m]>'9')  //检验是否有乱输入其他字符
            {
                printf("请输入整数：");
                break;
            }
            else
            {
                if (m == len - 1)
                    j = 0;
            }
        }
    }
    j = len - 1;
    for (m = 0;m < len;m++)  // 将字符重新转换为数字
    {
        for (k = 0;k < j;k++)
            arg *= 10;
        num += (word[m] - '0') * arg;
        arg = 1;
        j--;
    }
    return num;
}

/* 创建客户订单结点 */
clientList Creat_clientNode(char name[MAXSIZE], int amount, int rank)
{
    clientList c = NULL;
    c = (clientList)malloc(sizeof(clientNode));
    if (c == NULL)
    {
        printf("内存分配失败\n");
        system("pause");
        exit(0);
    }
    strcpy(c->name, name);
    c->amount = amount;
    c->rank = rank;
    c->prior = NULL;
    c->next = NULL;
    return c;
}

/* 插入客户名单到总的已订票客户名单 */
Status Insert_clientList(clientList* total, clientList* c)
{
    clientList ptr = *total;
    if ((*c) == NULL)
    {
        return error;
    }
    if (ptr == NULL)
    {
        *total = *c;
    }
    else
    {
        while (ptr)
        {
            if (strcmp(ptr->name, (*c)->name) >= 0) //比较姓名顺序，插入顺序为按客户姓名从小到大排序
            {
                if (ptr->prior == NULL) //比头结点小，插在头结点之前
                {
                    (*c)->next = ptr;
                    ptr->prior = *c;
                    *total = *c;
                    break;
                }
                else //插在中间
                {
                    (*c)->prior = ptr->prior;
                    (*c)->next = ptr;
                    (*c)->prior->next = *c;
                    ptr->prior = *c;
                    break;
                }
            }
            else
            {
                if (ptr->next == NULL) //比尾结点大，插在尾结点之后
                {
                    ptr->next = *c;
                    (*c)->prior = ptr;
                    break;
                }
            }
            ptr = ptr->next;
        }
    }
    return ok;
}

/* 删除航线总订单中的指定订单 */
Status Delete_clientList(clientList* total, clientList* c, int amount)
{
    clientList ptr = *total;
    if ((*c) == NULL || ptr == NULL)
    {
        return error;
    }
    if ((*c)->amount == amount) //退票量等于订票量
    {
        if (ptr == *c) //删除结点为头结点
        {
            ptr = ptr->next;
            *total = ptr;
            if (*total != NULL)
            {
                (*total)->prior = NULL;
            }
            free(*c);
        }
        else
        {
            if ((*c)->next != NULL)
            {
                (*c)->next->prior = (*c)->prior;
            }
            (*c)->prior->next = (*c)->next;
            free(*c);
        }
    }
    else //退票量小于订票量
    {
        (*c)->amount -= amount;
    }
    return ok;
}

/* 初始化队列 */
//Status Init_waitQueue(waitQueue* q)
//{
//	q = (waitQueue*)malloc(sizeof(waitQueue));
//	if (q == NULL)
//	{
//		printf("内存分配失败\n");
//		system("pause");
//		exit(0);
//	}
//	q->front = NULL;
//	q->rear = NULL;
//	return ok;
//}

/* 入队 */
Status En_waitQueue(waitQueue* wqueue, char name[MINSIZE], int amount)
{
    waitPtr ptr = (waitPtr)malloc(sizeof(waitNode));
    if (ptr == NULL)
    {
        printf("内存分配失败\n");
        system("pause");
        exit(0);
    }
    strcpy(ptr->name, name);
    ptr->amount = amount;
    ptr->next = NULL;
    if (wqueue->front == NULL)
    {
        wqueue->front = ptr;
        wqueue->rear = ptr;
    }
    else
    {
        wqueue->rear->next = ptr;
        wqueue->rear = ptr;
    }
    return ok;
}

/* 出队 */
Status De_waitQueue(waitQueue* wqueue, waitPtr de)
{
    if ((*wqueue).front == NULL)
    {
        return error;
    }
    waitPtr ph = (waitPtr)malloc(sizeof(waitNode));
    waitPtr phr = (waitPtr)malloc(sizeof(waitNode));
    if (ph == NULL || phr == NULL)
    {
        printf("内存分配失败\n");
        system("pause");
        exit(0);
    }
    ph = wqueue->front;
    phr = ph->next;
    if (wqueue->front == wqueue->rear)
    {
        wqueue->front = NULL;
        wqueue->rear = NULL;
        free(ph);
        free(phr);
    }
    else if (ph == de)
    {
        wqueue->front = wqueue->front->next;
        free(ph);
        free(phr);
    }
    else
    {
        while (phr != NULL)
        {

            if (phr == de)
            {
                ph->next = de->next;
                free(ph);
                free(phr);
                break;
            }
            phr = phr->next;
            ph = ph->next;
        }
    }
    return ok;
}

/* 遍历队列 */


/* 初始化(航班总信息)单链表 */
Status Init_Flight(FlightList* f)
{
    *f = (FlightList)malloc(sizeof(Flight));
    if ((*f) == NULL)
    {
        printf("内存分配失败\n");
        system("pause");
        exit(0);
    }
    strcpy((*f)->destination, "");
    strcpy((*f)->flightID, "");
    strcpy((*f)->planeID, "");
    strcpy((*f)->time, "");
    (*f)->num = 0;
    (*f)->tickets = 0;
    (*f)->next = NULL;
    return ok;
}

/* 创建航班结点 */
FlightList Creat_Flight(char* des, char* fid, char* pid, char* time, int num, int tickets)
{
    FlightList fl = (FlightList)malloc(sizeof(Flight));
    if (fl == NULL)
    {
        printf("内存分配失败\n");
        system("pause");
        exit(0);
    }
    strcpy(fl->destination, des);
    strcpy(fl->flightID, fid);
    strcpy(fl->planeID, pid);
    strcpy(fl->time, time);
    fl->num = num;
    fl->tickets = tickets;
    fl->clist = NULL;
    //Init_waitQueue(&(fl->wqueue));
    fl->wqueue.front = NULL;
    fl->wqueue.rear = NULL;
    fl->next = NULL;
    return fl;
}

/* 插入新的航班 */
Status Insert_Flight(FlightList* f1, FlightList* f2)
{
    FlightList p, pr;
    p = *f1;
    pr = NULL;
    if ((*f2) == NULL)
    {
        return error;
    }
    while (p != NULL)
    {
        if ((strcmp(p->destination, "") != 0) && (strcmp(p->destination, (*f2)->destination) >= 0)) //比较终点站名顺序，插入顺序为按终点站名从小到大排序
        {
            break;
        }
        pr = p;
        p = p->next;
    }
    if (pr == NULL)
    {
        return error;
    }
    pr->next = *f2;
    (*f2)->next = p;
    return ok;
}

/* 删除指定航班 */
int Delete_Flight(FlightList* f, char* flightID)
{
    int flag = 0;
    FlightList p, pr;
    p = *f;
    pr = NULL;
    if (strcmp(flightID, "") == 0)
    {
        return error;
    }
    while (p != NULL)
    {
        if (strcmp(p->flightID, flightID) == 0)
        {
            flag = 1;
            break;
        }
        pr = p;
        p = p->next;
    }
    if (pr == NULL)
    {
        return error;
    }
    if (flag == 1)
    {
        pr->next = p->next;
        free(p);
    }
    return flag;
}

/* 查询航线，输出最近一天的航班信息 */
void SearchFlight(FlightList* flight)
{
    system("cls");
    printf("\n\n");
    printf("************************************\n");
    printf("*      欢迎使用航空客运系统        *\n");
    printf("*----------------------------------*\n");
    printf("*       当前为：查询窗口           *\n");
    printf("************************************\n");
    char destination[MAXSIZE] = { 0 };
    printf("\n请输入终点站名：");
    scanf("%s", destination);
    int flag = 0;
    FlightList p = *flight;
    while (p != NULL)
    {
        if (strcmp(destination, p->destination) == 0)
        {
            printf("查找成功！\n最近一天的航班信息如下：\n");
            printf("|  航班号  |-|   机型  |-|     起飞时间      |-|  剩余票数 |\n");
            printf("    %-14s%-11s%-23s%-10d\n", p->flightID, p->planeID, p->time, p->tickets);
            flag = 1;
            break;
        }
        p = p->next;
    }
    if (flag == 0)
    {
        printf("查找失败!\n");
    }
    getchar();
    printf("\n输入任意键返回上一界面......");
    getchar();
    system("cls");
}

/* 订票 */
void booking(FlightList* f, int amount)
{
    (*f)->tickets -= amount;
    char name[MAXSIZE] = { 0 };
    printf("\n请输入您的名字：");
    scanf("%s", name);
    int rank = 0;
    printf("\n请输入舱位等级：");
    rank = judge_int();
    clientList c = Creat_clientNode(name, amount, rank);
    if (Insert_clientList(&((*f)->clist), &c))
    {
        printf("订票成功\n");
    }
    else
    {
        printf("订票失败\n");
    }
}

/* 客户订票 */
int BookTicket(FlightList* flight)
{
    system("cls");
    printf("\n\n");
    printf("************************************\n");
    printf("*      欢迎使用航空客运系统        *\n");
    printf("*----------------------------------*\n");
    printf("*       当前为：订票窗口           *\n");
    printf("************************************\n");
    char flightID[MAXSIZE] = { 0 };
    int amount = 0;
    printf("\n请输入航班号：");
    scanf("%s", flightID);
    printf("\n请输入订购的票数：");
    amount = judge_int();
    FlightList p = *flight;
    int flag = 0;
    while (p != NULL)
    {
        if (strcmp(flightID, p->flightID) == 0)
        {
            flag = 1;
            if (p->tickets >= amount)
            {
                booking(&p, amount);
            }
            else if (p->tickets == 0)
            {
                printf("\n抱歉，本趟航班已满员\n");
                printf("请问是否添加至候补队列?(y/n)\n");
                while (1)
                {
                    char queuechoice;
                    fflush(stdin);
                    scanf("%c", &queuechoice);
                    if (queuechoice == 'y' || queuechoice == 'Y')
                    {
                        char name[MAXSIZE] = { 0 };
                        printf("\n请输入您的名字：");
                        scanf("%s", name);
                        if (En_waitQueue(&(p->wqueue), name, amount))
                        {
                            printf("已添加至候补队列\n");
                        }
                        else
                        {
                            printf("添加至候补队列失败\n");
                        }
                        break;
                    }
                    else if (queuechoice == 'n' || queuechoice == 'N')
                    {
                        break;
                    }
                    else
                    {
                        printf("请重新输入(y/n)");
                    }
                }
            }
            else if (p->tickets != 0 && p->tickets < amount)
            {
                printf("\n抱歉，余票不足\n");
                printf("请问是否添加至候补队列?(y/n)\n");
                while (1)
                {
                    char queuechoice;
                    fflush(stdin);
                    scanf("%c", &queuechoice);
                    if (queuechoice == 'y' || queuechoice == 'Y')
                    {
                        char name[MAXSIZE] = { 0 };
                        printf("\n请输入您的名字：");
                        scanf("%s", name);
                        if (En_waitQueue(&(p->wqueue), name, amount))
                        {
                            printf("已添加至候补队列\n");
                        }
                        else
                        {
                            printf("添加至候补队列失败\n");
                        }
                        break;
                    }
                    else if (queuechoice == 'n' || queuechoice == 'N')
                    {
                        break;
                    }
                    else
                    {
                        printf("请重新输入(y/n)");
                    }
                }
            }
            break;
        }
        p = p->next;
    }
    if (flag == 0)
    {
        printf("\n查询不到该航班！请返回重新输入\n");
    }
    getchar();
    printf("\n输入任意键返回上一界面......");
    getchar();
    system("cls");
    return flag;
}

/* 替补订票 */
void booking_wait(FlightList* f, int amount, char* name)
{
    FlightList p = *f;
    p->tickets -= amount;
    int rank = 0;
    printf("\n航班中有人退票\n请%s订票\n输入舱位等级：", name);
    rank = judge_int();
    clientList c = Creat_clientNode(name, amount, rank);
    if (Insert_clientList(&((*f)->clist), &c))
    {
        printf("订票成功\n");
    }
    else
    {
        printf("订票失败\n");
    }
}

/* 更新替补队列 */
void update_queue(FlightList* f, int amount)
{
    FlightList pf = *f;
    waitPtr pw = (*f)->wqueue.front;
    while (pw != NULL)
    {
        if (pw->amount <= amount)
        {
            int waitamount = pw->amount;
            char waitname[MAXSIZE] = { 0 };
            strcpy(waitname, pw->name);
            De_waitQueue(&((*f)->wqueue), pw);
            booking_wait(f, waitamount, waitname);
            break;
        }
        pw = pw->next;
    }
}

/* 客户退票 */
int RefundTicket(FlightList* flight)
{
    system("cls");
    printf("\n\n");
    printf("************************************\n");
    printf("*      欢迎使用航空客运系统        *\n");
    printf("*----------------------------------*\n");
    printf("*       当前为：退票窗口           *\n");
    printf("************************************\n");
    char flightID[MAXSIZE] = { 0 };
    int amount = 0;
    char name[MAXSIZE] = { 0 };
    printf("\n请输入您的名字：");
    scanf("%s", name);
    printf("\n请输入航班号：");
    scanf("%s", flightID);
    printf("\n请输入退订的票数：");
    scanf("%d", &amount);
    FlightList p = *flight;
    int flag = 0;
    clientList pc = NULL;
    while (p != NULL)
    {
        if (strcmp(p->flightID, flightID) == 0)
        {
            pc = p->clist;
            while (pc != NULL)
            {
                if (strcmp(pc->name, name) == 0)
                {
                    flag = 1;
                    if (pc->amount >= amount) //退票量小于订票量
                    {
                        p->tickets += amount;
                        Delete_clientList(&(p->clist), &pc, amount);
                        printf("\n退票成功！退款金额将在两小时内返回支付账户\n");
                        if (p->wqueue.front != NULL)
                        {
                            update_queue(&p, amount);
                        }
                    }
                    else
                    {
                        printf("退票量大于订票量！\n");
                        printf("退票失败\n");
                    }
                    break;
                }
                pc = pc->next;
            }
        }
        p = p->next;
    }
    if (flag == 0)
    {
        printf("\n查询不到该订单，退票失败\n");
    }
    getchar();
    printf("\n输入任意键返回上一界面......");
    getchar();
    system("cls");
    return flag;
}

/* 显示所有航班信息 */
void DisplayAllInfo(FlightList flight)
{
    system("cls");
    printf("\n\n");
    printf("************************************\n");
    printf("*      欢迎使用航空客运系统        *\n");
    printf("*----------------------------------*\n");
    printf("*       以下为所有航班信息         *\n");
    printf("************************************\n");
    FlightList p = flight;
    printf("\n|  航班号  |-|   终点站  |-|   机型    |-|      起飞时间      |-|  可乘坐乘客数  |-| 剩余票数  |\n");
    p = p->next;
    while (p != NULL)
    {
        printf("    %-14s%-13s%-15s%-26s%-15d%-5d\n", p->flightID, p->destination, p->planeID, p->time, p->num, p->tickets);
        p = p->next;
    }
    getchar();
    printf("\n输入任意键返回上一界面......");
    getchar();
    system("cls");
}

/* 添加新的航班 */
void addFlight(FlightList* flight)
{
    system("cls");
    printf("\n\n");
    printf("************************************\n");
    printf("*      欢迎进入管理员窗口          *\n");
    printf("*----------------------------------*\n");
    printf("*      当前为：添加航班窗口        *\n");
    printf("************************************\n");
    char destination[MAXSIZE] = { 0 };
    char flightID[MAXSIZE] = { 0 };
    char planeID[MAXSIZE] = { 0 };
    char time[MAXSIZE] = { 0 };
    int num = 0;
    int tickets = 0;
    printf("\n请输入终点站名：");
    scanf("%s", destination);
    printf("\n请输入航班号：");
    scanf("%s", flightID);
    printf("\n请输入飞机号：");
    scanf("%s", planeID);
    printf("\n请输入起飞时间(格式为yyyy-mm-dd-hh:mm)：");
    scanf("%s", time);
    printf("\n请输入乘员定额：");
    num = judge_int();
    printf("\n请输入余票数量：");
    tickets = judge_int();
    FlightList newFlight = Creat_Flight(destination, flightID, planeID, time, num, tickets);
    if (Insert_Flight(flight, &newFlight))
    {
        printf("\n航班添加成功！\n");
    }
    getchar();
    printf("\n输入任意键返回上一界面......");
    getchar();
    system("cls");
}

/* 删除指定航班 */
void deleteFlight(FlightList* flight)
{
    system("cls");
    printf("\n\n");
    printf("************************************\n");
    printf("*      欢迎进入管理员窗口          *\n");
    printf("*----------------------------------*\n");
    printf("*      当前为：删除航班窗口        *\n");
    printf("************************************\n");
    char flightID[MAXSIZE] = { 0 };
    printf("\n请输入航班号：");
    scanf("%s", flightID);
    if (Delete_Flight(flight, flightID))
    {
        printf("\n航班删除成功！\n");
    }
    else
    {
        printf("\n航班删除失败！请输入系统存在的航班号！\n");
    }
    getchar();
    printf("\n输入任意键返回上一界面......");
    getchar();
    system("cls");
}

/* 显示指定航线上的客户订单 */
void displayClientInfo(FlightList flight)
{
    system("cls");
    printf("\n\n");
    printf("************************************\n");
    printf("*      欢迎进入管理员窗口          *\n");
    printf("*----------------------------------*\n");
    printf("*      当前为：查看所有订单窗口    *\n");
    printf("************************************\n");
    int flag = 0;
    char flightID[MAXSIZE] = { 0 };
    printf("\n请输入航班号：");
    scanf("%s", flightID);
    FlightList p = flight;
    while (p != NULL)
    {
        if (strcmp(flightID, p->flightID) == 0)
        {
            flag = 1;
            break;
        }
        p = p->next;
    }
    if (flag == 1)
    {
        clientList cp = p->clist;
        if (cp == NULL)
        {
            printf("\n该航线客户订单为空\n");
        }
        else
        {
            printf("航班：%s  的所有客户名单\n\n", flightID);
            while (cp != NULL)
            {
                printf("\n");
                printf("\n客户名字：%s  订票数：%d   舱位等级：%d 等舱", cp->name, cp->amount, cp->rank);
                cp = cp->next;
            }
        }
    }
    else
    {
        printf("\n查询不到该航班信息，请输入正确的航班号！");
    }
    getchar();
    printf("\n\n输入任意键返回上一界面......");
    getchar();
    system("cls");
}

/* 管理员验证 */
Status AdministratorVerify(void)
{
    char pwd[20] = { "admin" };	//管理员密码
    char password[20] = { 0 };	//待输入密码，用来验证
    printf("请输入管理员密码:\n");
    scanf("%s", password);
    if (strcmp(pwd, password)) {
        printf("密码错误，请重新输入:\n");
        return error;
    }
    printf("验证成功\n");
    return ok;
}

void MainMenu(void)
{
    printf("\n\n");
    printf("************************************\n");
    printf("*       欢迎使用航空客运系统       *\n");
    printf("*----------------------------------*\n");
    printf("*          0.退出系统              *\n");
    printf("*          1.用户界面              *\n");
    printf("*          2.管理员界面            *\n");
    printf("************************************\n");
}

void UserMenu(void)
{
    printf("\n\n");
    printf("************************************\n");
    printf("*       欢迎使用航空客运系统       *\n");
    printf("*----------------------------------*\n");
    printf("*          0.返回上一级            *\n");
    printf("*          1.查询航线              *\n");
    printf("*          2.订购机票              *\n");
    printf("*          3.退订机票              *\n");
    printf("*          4.查看所有航班          *\n");
    printf("************************************\n");
}

void AdminMenu(void)
{
    printf("\n\n");
    printf("************************************\n");
    printf("*         欢迎进入管理员系统       *\n");
    printf("*----------------------------------*\n");
    printf("*          0.返回上一级            *\n");
    printf("*          1.添加航线              *\n");
    printf("*          2.删除航班              *\n");
    printf("*          3.查看航线所有订单      *\n");
    printf("*          4.查看所有航班          *\n");
    printf("************************************\n");
}
