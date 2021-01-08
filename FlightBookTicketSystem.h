#pragma once
#ifndef FlightBookTicketSystem_H_INCLUDED
#define FlightBookTicketSystem_H_INCLUDED

/* 常量定义 */
#define MINSIZE 40
#define MAXSIZE 40

typedef enum Status
{
	error,
	ok
}Status;

/* 已订票的客户名单--线性表(双向链表)实现 */
typedef struct clientNode
{
	char name[MINSIZE];		//姓名
	int amount;		//订票量
	int rank;	 //舱位等级1，2或3
	
	struct clientNode* prior, * next;	//指针域，二叉链表
}clientNode, * clientList;

/* 等候替补的客户名单--链队列实现 */
typedef struct waitNode
{
	char name[MAXSIZE];		//姓名
	int amount;		//订票量
	
	struct waitNode* next;		//指针域，单向链表
}waitNode, * waitPtr;

//链队列
typedef struct waitQueue
{
	waitPtr front;	 //队头指针
	waitPtr rear;	 //队尾指针
}waitQueue, * waitQueuePtr;

/* 航班总信息--线性表(带头结点的单链表)实现 */
typedef struct Flight
{
	char destination[MAXSIZE];		//终点站名
	char flightID[MAXSIZE];		 //航班号
	char planeID[MAXSIZE];		//飞机号
	char time[MAXSIZE];		//起飞时间
	int num;	 //乘员定额
	int tickets;	//余票量
	clientList clist;	//已订票的客户名单(包括姓名、订票量、舱位等级1，2或3)
	waitQueue wqueue;	//等候替补的客户名单(包括姓名、所需票量)
	
	struct Flight* next;	//指针域，单向链表
}Flight, * FlightList;

#endif
