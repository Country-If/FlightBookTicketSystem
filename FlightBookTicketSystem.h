#pragma once
#ifndef FlightBookTicketSystem_H_INCLUDED
#define FlightBookTicketSystem_H_INCLUDED

/* �������� */
#define MINSIZE 40
#define MAXSIZE 40

typedef enum Status
{
	error,
	ok
}Status;

/* �Ѷ�Ʊ�Ŀͻ�����--���Ա�(˫������)ʵ�� */
typedef struct clientNode
{
	char name[MINSIZE];		//����
	int amount;		//��Ʊ��
	int rank;	 //��λ�ȼ�1��2��3
	
	struct clientNode* prior, * next;	//ָ���򣬶�������
}clientNode, * clientList;

/* �Ⱥ��油�Ŀͻ�����--������ʵ�� */
typedef struct waitNode
{
	char name[MAXSIZE];		//����
	int amount;		//��Ʊ��
	
	struct waitNode* next;		//ָ���򣬵�������
}waitNode, * waitPtr;

//������
typedef struct waitQueue
{
	waitPtr front;	 //��ͷָ��
	waitPtr rear;	 //��βָ��
}waitQueue, * waitQueuePtr;

/* ��������Ϣ--���Ա�(��ͷ���ĵ�����)ʵ�� */
typedef struct Flight
{
	char destination[MAXSIZE];		//�յ�վ��
	char flightID[MAXSIZE];		 //�����
	char planeID[MAXSIZE];		//�ɻ���
	char time[MAXSIZE];		//���ʱ��
	int num;	 //��Ա����
	int tickets;	//��Ʊ��
	clientList clist;	//�Ѷ�Ʊ�Ŀͻ�����(������������Ʊ������λ�ȼ�1��2��3)
	waitQueue wqueue;	//�Ⱥ��油�Ŀͻ�����(��������������Ʊ��)
	
	struct Flight* next;	//ָ���򣬵�������
}Flight, * FlightList;

#endif
