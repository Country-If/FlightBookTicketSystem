#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "FlightBookTicketSystem.h"

#pragma warning(disable:4996) //visual studio��ȫ������scanf,getchar
#pragma warning(disable:6031) //visual studio����ֵ����������strcmp

/* ��ֹ�û��������������ַ����淶�û��������� */
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
			if (word[m] < '0' || word[m]>'9')  //�����Ƿ��������������ַ�
			{
				printf("������������");
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
	for (m = 0;m < len;m++)  // ���ַ�����ת��Ϊ����
	{
		for (k = 0;k < j;k++)
			arg *= 10;
		num += (word[m] - '0') * arg;
		arg = 1;
		j--;
	}
	return num;
}

/* ��ʼ��������� */
Status Init_clientList(clientList* c)
{
	/**c = (clientList)malloc(sizeof(clientNode));
	if ((*c) == NULL)
	{
		printf("�ڴ����ʧ��\n");
		system("pause");
		exit(0);
	}
	(*c)->next = NULL;
	(*c)->prior = NULL;*/
	*c = NULL;
	return ok;
}

/* �����ͻ�������� */
clientList Creat_clientNode(char name[MAXSIZE], int amount, int rank)
{
	clientList c = NULL;
	c = (clientList)malloc(sizeof(clientNode));
	if (c == NULL)
	{
		printf("�ڴ����ʧ��\n");
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

/* ����ͻ��������ܵ��Ѷ�Ʊ�ͻ����� */
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
			if (strcmp(ptr->name, (*c)->name) >= 0) //�Ƚ�����˳�򣬲���˳��Ϊ���ͻ�������С��������
			{
				if (ptr->prior == NULL) //��ͷ���С������ͷ���֮ǰ
				{
					(*c)->next = ptr;
					ptr->prior = *c;
					*total = *c;
					break;
				}
				else //�����м�
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
				if (ptr->next == NULL) //��β���󣬲���β���֮��
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

/* ɾ�������ܶ����е�ָ������ */
Status Delete_clientList(clientList* total, clientList* c, int amount)
{
	clientList ptr = *total;
	if ((*c) == NULL || ptr == NULL)
	{
		return error;
	}
	if ((*c)->amount == amount) //��Ʊ�����ڶ�Ʊ��
	{
		if (ptr == *c) //ɾ�����Ϊͷ���
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
	else //��Ʊ��С�ڶ�Ʊ��
	{
		(*c)->amount -= amount;
	}
	return ok;
}

/* ��ʼ������ */
Status Init_waitQueue(waitQueuePtr q)
{
	q = (waitQueuePtr)malloc(sizeof(waitQueue));
	if (q == NULL)
	{
		printf("�ڴ����ʧ��\n");
		system("pause");
		exit(0);
	}
	q->front = NULL;
	q->rear = NULL;
	return ok;
}

/* ��� */
Status En_waitQueue(waitQueue* wqueue, char name[MINSIZE], int amount)
{
	waitPtr ptr = (waitPtr)malloc(sizeof(waitNode));
	if (ptr == NULL)
	{
		printf("�ڴ����ʧ��\n");
		system("pause");
		exit(0);
	}
	strcpy(ptr->name, name);
	ptr->amount = amount;
	ptr->next = NULL;
	if (wqueue->front == wqueue->rear)
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

/* ���� */
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
		printf("�ڴ����ʧ��\n");
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

/* ��ʼ��(��������Ϣ)������ */
Status Init_Flight(FlightList* f)
{
	*f = (FlightList)malloc(sizeof(Flight));
	if ((*f) == NULL)
	{
		printf("�ڴ����ʧ��\n");
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
	Init_clientList(&(*f)->clist);
	return ok;
}

/* ���������� */
FlightList Creat_Flight(char* des, char* fid, char* pid, char* time, int num, int tickets)
{
	FlightList fl = (FlightList)malloc(sizeof(Flight));
	if (fl == NULL)
	{
		printf("�ڴ����ʧ��\n");
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
	Init_waitQueue(&(fl->wqueue));
	fl->next = NULL;
	return fl;
}

/* �����µĺ��� */
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
		if ((strcmp(p->destination, "") != 0) && (strcmp(p->destination, (*f2)->destination) >= 0)) //�Ƚ��յ�վ��˳�򣬲���˳��Ϊ���յ�վ����С��������
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

/* ɾ��ָ������ */
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

/* ��ѯ���ߣ�������һ��ĺ�����Ϣ */
void SearchFlight(FlightList* flight)
{
	system("cls");
	printf("\n\n");
	printf("************************************\n");
	printf("*      ��ӭʹ�ú��տ���ϵͳ        *\n");
	printf("*----------------------------------*\n");
	printf("*       ��ǰΪ����ѯ����           *\n");
	printf("************************************\n");
	char destination[MAXSIZE] = { 0 };
	printf("\n�������յ�վ����");
	scanf("%s", destination);
	int flag = 0;
	FlightList p = *flight;
	while (p != NULL)
	{
		if (strcmp(destination, p->destination) == 0)
		{
			printf("���ҳɹ���\n���һ��ĺ�����Ϣ���£�\n");
			printf("|  �����  |-|   ����  |-|     ���ʱ��      |-|  ʣ��Ʊ�� |\n");
			printf("    %-14s%-11s%-23s%-10d\n", p->flightID, p->planeID, p->time, p->tickets);
			flag = 1;
			break;
		}
		p = p->next;
	}
	if (flag == 0)
	{
		printf("����ʧ��!\n");
	}
	getchar();
	printf("\n���������������һ����......");
	getchar();
	system("cls");
}

/* ��Ʊ */
void booking(FlightList* f, int amount)
{
	(*f)->tickets -= amount;
	char name[MAXSIZE] = { 0 };
	printf("\n�������������֣�");
	scanf("%s", name);
	int rank = 0;
	printf("\n�������λ�ȼ���");
	rank = judge_int();
	clientList c = Creat_clientNode(name, amount, rank);
	if (Insert_clientList(&((*f)->clist), &c))
	{
		printf("��Ʊ�ɹ�\n");
	}
	else
	{
		printf("��Ʊʧ��\n");
	}
}

/* �ͻ���Ʊ */
int BookTicket(FlightList* flight)
{
	system("cls");
	printf("\n\n");
	printf("************************************\n");
	printf("*      ��ӭʹ�ú��տ���ϵͳ        *\n");
	printf("*----------------------------------*\n");
	printf("*       ��ǰΪ����Ʊ����           *\n");
	printf("************************************\n");
	char flightID[MAXSIZE] = { 0 };
	int amount = 0;
	printf("\n�����뺽��ţ�");
	scanf("%s", flightID);
	printf("\n�����붩����Ʊ����");
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
				booking(flight, amount);
			}
			else if (p->tickets == 0)
			{
				printf("\n��Ǹ�����˺�������Ա\n");
				printf("�����Ƿ�������򲹶���?(y/n)\n");
				while (1)
				{
					char queuechoice;
					fflush(stdin);
					scanf("%c", &queuechoice);
					if (queuechoice == 'y' || queuechoice == 'Y')
					{
						char name[MAXSIZE] = { 0 };
						printf("\n�������������֣�");
						scanf("%s", name);
						if (En_waitQueue(&((*flight)->wqueue), name, amount))
						{
							printf("��������򲹶���\n");
						}
						else
						{
							printf("������򲹶���ʧ��\n");
						}
						break;
					}
					else if (queuechoice == 'n' || queuechoice == 'N')
					{
						break;
					}
					else
					{
						printf("����������(y/n)");
					}
				}
			}
			else if (p->tickets != 0 && p->tickets < amount)
			{
				printf("\n��Ǹ����Ʊ����\n");
				printf("�����Ƿ�������򲹶���?(y/n)\n");
				while (1)
				{
					char queuechoice;
					fflush(stdin);
					scanf("%c", &queuechoice);
					if (queuechoice == 'y' || queuechoice == 'Y')
					{
						char name[MAXSIZE] = { 0 };
						printf("\n�������������֣�");
						scanf("%s", name);
						if (En_waitQueue(&((*flight)->wqueue), name, amount))
						{
							printf("��������򲹶���\n");
						}
						else
						{
							printf("������򲹶���ʧ��\n");
						}
						break;
					}
					else if (queuechoice == 'n' || queuechoice == 'N')
					{
						break;
					}
					else
					{
						printf("����������(y/n)");
					}
				}
			}
			break;
		}
		p = p->next;
	}
	if (flag == 0)
	{
		printf("\n��ѯ�����ú��࣡�뷵����������\n");
	}
	getchar();
	printf("\n���������������һ����......");
	getchar();
	system("cls");
	return flag;
}

/* �油��Ʊ */
void booking_wait(FlightList* f, int amount, char* name)
{
	FlightList p = *f;
	p->tickets -= amount;
	int rank = 0;
	printf("\n������������Ʊ\n��%s��Ʊ\n�����λ�ȼ���", name);
	rank = judge_int();
	clientList c = Creat_clientNode(name, amount, rank);
	if (Insert_clientList(&((*f)->clist), &c))
	{
		printf("��Ʊ�ɹ�\n");
	}
	else
	{
		printf("��Ʊʧ��\n");
	}
}

/* �����油���� */
void update_queue(FlightList* f, int amount)
{
	FlightList pf = *f;
	waitPtr pw = (*f)->wqueue.front;
	while (pw != NULL)
	{
		if (pw->amount <= amount)
		{
			De_waitQueue(&(*f)->wqueue, pw);
			booking_wait(f, pw->amount, pw->name);
			break;
		}
		pw = pw->next;
	}
}

/* �ͻ���Ʊ */
int RefundTicket(FlightList* flight)
{
	system("cls");
	printf("\n\n");
	printf("************************************\n");
	printf("*      ��ӭʹ�ú��տ���ϵͳ        *\n");
	printf("*----------------------------------*\n");
	printf("*       ��ǰΪ����Ʊ����           *\n");
	printf("************************************\n");
	char flightID[MAXSIZE] = { 0 };
	int amount = 0;
	char name[MAXSIZE] = { 0 };
	printf("\n�������������֣�");
	scanf("%s", name);
	printf("\n�����뺽��ţ�");
	scanf("%s", flightID);
	printf("\n�������˶���Ʊ����");
	scanf("%d", &amount);
	FlightList p = *flight;
	int flag = 0;
	clientList total = NULL;
	while (p != NULL)
	{
		if (strcmp(p->flightID, flightID) == 0)
		{
			total = p->clist;
			while (total != NULL)
			{
				if (strcmp(total->name, name) == 0)
				{
					flag = 1;
					if (total->amount >= amount) //��Ʊ��С�ڶ�Ʊ��
					{
						p->tickets += amount;
						Delete_clientList(&((*flight)->clist), &total, amount);
						printf("\n��Ʊ�ɹ����˿������Сʱ�ڷ���֧���˻�\n");
						if (p->wqueue.front != NULL)
						{
							update_queue(flight, amount);
						}
					}
					else
					{
						printf("��Ʊ�����ڶ�Ʊ����\n");
						printf("��Ʊʧ��\n");
					}
					break;
				}
				total = total->next;
			}
		}
		p = p->next;
	}
	if (flag == 0)
	{
		printf("\n��ѯ�����ö�������Ʊʧ��\n");
	}
	getchar();
	printf("\n���������������һ����......");
	getchar();
	system("cls");
	return flag;
}

/* ��ʾ���к�����Ϣ */
void DisplayAllInfo(FlightList flight)
{
	system("cls");
	printf("\n\n");
	printf("************************************\n");
	printf("*      ��ӭʹ�ú��տ���ϵͳ        *\n");
	printf("*----------------------------------*\n");
	printf("*       ����Ϊ���к�����Ϣ         *\n");
	printf("************************************\n");
	FlightList p = flight;
	printf("\n|  �����  |-|   �յ�վ  |-|   ����    |-|      ���ʱ��      |-|  �ɳ����˿���  |-| ʣ��Ʊ��  |\n");
	p = p->next;
	while (p != NULL)
	{
		printf("    %-14s%-13s%-15s%-26s%-15d%-5d\n", p->flightID, p->destination, p->planeID, p->time, p->num, p->tickets);
		p = p->next;
	}
	getchar();
	printf("\n���������������һ����......");
	getchar();
	system("cls");
}

/* ����µĺ��� */
void addFlight(FlightList* flight)
{
	system("cls");
	printf("\n\n");
	printf("************************************\n");
	printf("*      ��ӭ�������Ա����          *\n");
	printf("*----------------------------------*\n");
	printf("*      ��ǰΪ����Ӻ��ര��        *\n");
	printf("************************************\n");
	char destination[MAXSIZE] = { 0 };
	char flightID[MAXSIZE] = { 0 };
	char planeID[MAXSIZE] = { 0 };
	char time[MAXSIZE] = { 0 };
	int num = 0;
	int tickets = 0;
	printf("\n�������յ�վ����");
	scanf("%s", destination);
	printf("\n�����뺽��ţ�");
	scanf("%s", flightID);
	printf("\n������ɻ��ţ�");
	scanf("%s", planeID);
	printf("\n���������ʱ��(��ʽΪyyyy-mm-dd-hh:mm)��");
	scanf("%s", time);
	printf("\n�������Ա���");
	num = judge_int();
	printf("\n��������Ʊ������");
	tickets = judge_int();
	FlightList newFlight = Creat_Flight(destination, flightID, planeID, time, num, tickets);
	if (Insert_Flight(flight, &newFlight))
	{
		printf("\n������ӳɹ���\n");
	}
	getchar();
	printf("\n���������������һ����......");
	getchar();
	system("cls");
}

/* ɾ��ָ������ */
void deleteFlight(FlightList* flight)
{
	system("cls");
	printf("\n\n");
	printf("************************************\n");
	printf("*      ��ӭ�������Ա����          *\n");
	printf("*----------------------------------*\n");
	printf("*      ��ǰΪ��ɾ�����ര��        *\n");
	printf("************************************\n");
	char flightID[MAXSIZE] = { 0 };
	printf("\n�����뺽��ţ�");
	scanf("%s", flightID);
	if (Delete_Flight(flight, flightID))
	{
		printf("\n����ɾ���ɹ���\n");
	}
	else
	{
		printf("\n����ɾ��ʧ�ܣ�������ϵͳ���ڵĺ���ţ�\n");
	}
	getchar();
	printf("\n���������������һ����......");
	getchar();
	system("cls");
}

/* ��ʾָ�������ϵĿͻ����� */
void displayClientInfo(FlightList flight)
{
	system("cls");
	printf("\n\n");
	printf("************************************\n");
	printf("*      ��ӭ�������Ա����          *\n");
	printf("*----------------------------------*\n");
	printf("*      ��ǰΪ���鿴���ж�������    *\n");
	printf("************************************\n");
	int flag = 0;
	char flightID[MAXSIZE] = { 0 };
	printf("\n�����뺽��ţ�");
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
			printf("\n�ú��߿ͻ�����Ϊ��\n");
		}
		else
		{
			printf("���ࣺ%s  �����пͻ�����\n\n", flightID);
			while (cp != NULL)
			{
				printf("\n");
				printf("\n�ͻ����֣�%s  ��Ʊ����%d   ��λ�ȼ���%d �Ȳ�", cp->name, cp->amount, cp->rank);
				cp = cp->next;
			}
		}
	}
	else
	{
		printf("\n��ѯ�����ú�����Ϣ����������ȷ�ĺ���ţ�");
	}
	getchar();
	printf("\n\n���������������һ����......");
	getchar();
	system("cls");
}

/* ����Ա��֤ */
Status AdministratorVerify(void) {
	char pwd[20] = { "admin" };	//����Ա����
	char password[20] = { 0 };	//���������룬������֤
	printf("���������Ա����:\n");
	scanf("%s", password);
	if (strcmp(pwd, password)) {
		printf("�����������������:\n");
		return error;
	}
	printf("��֤�ɹ�\n");
	return ok;
}

void MainMenu(void)
{
	printf("\n\n");
	printf("************************************\n");
	printf("*       ��ӭʹ�ú��տ���ϵͳ       *\n");
	printf("*----------------------------------*\n");
	printf("*          0.�˳�ϵͳ              *\n");
	printf("*          1.�û�����              *\n");
	printf("*          2.����Ա����            *\n");
	printf("************************************\n");
}

void UserMenu(void)
{
	printf("\n\n");
	printf("************************************\n");
	printf("*       ��ӭʹ�ú��տ���ϵͳ       *\n");
	printf("*----------------------------------*\n");
	printf("*          0.������һ��            *\n");
	printf("*          1.��ѯ����              *\n");
	printf("*          2.������Ʊ              *\n");
	printf("*          3.�˶���Ʊ              *\n");
	printf("*          4.�鿴���к���          *\n");
	printf("************************************\n");
}

void AdminMenu(void)
{
	printf("\n\n");
	printf("************************************\n");
	printf("*         ��ӭ�������Աϵͳ       *\n");
	printf("*----------------------------------*\n");
	printf("*          0.������һ��            *\n");
	printf("*          1.��Ӻ���              *\n");
	printf("*          2.ɾ������              *\n");
	printf("*          3.�鿴�������ж���      *\n");
	printf("*          4.�鿴���к���          *\n");
	printf("************************************\n");
}

int main(void)
{
	FlightList flight = NULL;
	Init_Flight(&flight);

	FlightList f1 = Creat_Flight("����", "011", "022", "2021-1-7-14:00", 200, 200);
	FlightList f2 = Creat_Flight("����", "012", "021", "2021-1-8-14:00", 100, 100);
	Insert_Flight(&flight, &f1);
	Insert_Flight(&flight, &f2);

	int choice = 0;
	do
	{
		MainMenu();
		choice = judge_int();
		system("cls");
		switch (choice)
		{
		case 0:
			break;
		case 1: {
			int choice = 0;
			do
			{
				UserMenu();
				choice = judge_int();
				system("cls");
				switch (choice)
				{
				case 0: 
					break;
				case 1:
					printf("\n\n\n\n\n\n\n\n\n\n");
					SearchFlight(&flight);
					break;
				case 2:
					printf("\n\n\n\n\n\n\n\n\n\n");
					BookTicket(&flight);
					break;
				case 3:
					printf("\n\n\n\n\n\n\n\n\n\n");
					RefundTicket(&flight);
					break;
				case 4:
					printf("\n\n\n\n\n\n\n\n\n\n");
					DisplayAllInfo(flight);
					break;
				default:
					printf("�����������������룡");
					break;
				}
			} while (choice != 0);
			break;
		}
		case 2: {
			while (1)
			{
				if (AdministratorVerify())
					break;
			}
			int choice = 0;
			do
			{
				AdminMenu();
				choice = judge_int();
				system("cls");
				switch (choice)
				{
				case 0:
					break;
				case 1:
					printf("\n\n\n\n\n\n\n\n\n\n");
					addFlight(&flight);
					break;
				case 2:
					printf("\n\n\n\n\n\n\n\n\n\n");
					deleteFlight(&flight);
					break;
				case 3:
					printf("\n\n\n\n\n\n\n\n\n\n");
					displayClientInfo(flight);
					break;
				case 4:
					printf("\n\n\n\n\n\n\n\n\n\n");
					DisplayAllInfo(flight);
					break;
				default:
					printf("�����������������룡");
					break;
				}
			} while (choice != 0);
			break;
		}
		default:
			printf("�����������������룡");
			break;
		}
	} while (choice != 0);

	free(flight);
	free(f1);
	free(f2);
	printf("\n\n\t\t��лʹ�ú��տ��˶�Ʊϵͳ��\n\n\n");
	printf("\n\n\n\n\t\t�༶��19���Ű�1��\n\n\t\t�����������\n\n\t\tѧ�ţ�3119005436\n\n\n\n\n\n\n\n\n");
	system("pause");
	return 0;
}
