#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
//#include "FlightBookTicketSystem.h"

#pragma warning(disable:4996) //visual studio��ȫ������scanf,getchar
#pragma warning(disable:6031) //visual studio ����ֵ����������strcmp

/* ��ʼ��(�Ѷ�Ʊ�Ŀͻ�����)˫������ */
Status Init_clientList(clientList* c)
{
	*c = (clientList)malloc(sizeof(clientNode));
	if (*c == NULL)
	{
		printf("�ڴ����ʧ��\n");
		system("pause");
		exit(0);
	}
	(*c)->prior = NULL;
	(*c)->next = NULL;
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
	if (c == NULL)
	{
		return error;
	}
	if (ptr == NULL)
	{
		*total = ptr;
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
Status Delete_clientList(clientList* total, clientList* c)
{
	clientList ptr = *total;
	if ((*c) == NULL || ptr == NULL)
	{
		return error;
	}
	if (ptr == *c) //ɾ�����Ϊͷ���
	{
		ptr = ptr->next;
		*total = ptr;
		if ((*total) != NULL)
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
	return ok;
}

/* ��ʼ��(�򲹿ͻ�����)������ */
Status Init_waitQueue(waitQueuePtr q)
{
	q->front = q->rear = (waitPtr)malloc(sizeof(waitPtr));
	if (q->front == NULL || q->rear == NULL)
	{
		printf("�ڴ����ʧ��\n");
		system("pause");
		exit(0);
	}
	q->front->next = q->rear->next = NULL;	//��ͷ���
	return ok;
}

/* ��� */
Status En_waitQueue(waitQueuePtr wqueue, char name[MINSIZE], int amount)
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
	if (wqueue->front == NULL)
	{
		wqueue->front = ptr;
	}
	else
	{
		wqueue->rear->next = ptr;
	}
	wqueue->rear = ptr;
	return ok;
}

/* ����г��� */
int Length_queue(waitQueue q)
{
	int length = 0;
	waitPtr ptr = q.front;
	ptr = ptr->next;
	while (ptr)
	{
		length++;
		ptr = ptr->next;
	}
	return length;
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
		if (strcmp(p->flightID,flightID) == 0)
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
			printf("|  �����  |-|   ����  |-| ���ʱ�� |-|  ʣ��Ʊ�� |\n");
			printf("  %-20s %-22s%-26s%-15d\n", p->flightID, p->planeID, p->time, p->tickets);
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
}

/* ��Ʊ */
void booking(FlightList* f, int amount)
{
	FlightList p = *f;
	p->tickets -= amount;
	char name[MAXSIZE] = { 0 };
	printf("\n�������������֣�");
	scanf("%s", name);
	int rank = 0;
	printf("\n�������λ�ȼ���");
	scanf("%d", &rank);
	clientList c = Creat_clientNode(name, amount, rank);
	if (Insert_clientList(&(p->clist), &c))
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
	scanf("%d", &amount);
	FlightList p = *flight;
	int flag = 0;
	while (p != NULL)
	{
		if (strcmp(flightID, p->flightID) == 0)
		{
			flag = 1;
			if (p->tickets >= amount)
			{
				booking(&p,amount);
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
						if (En_waitQueue(&(p->wqueue), name, amount))
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
						if (En_waitQueue(&(p->wqueue), name, amount))
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
	return flag;
}

/* �����油���� */
void update_queue(FlightList* f, int amount)
{
	FlightList pf = *f;
	waitPtr pw = pf->wqueue.front;
	pw = pw->next;
	while (pw != NULL)
	{
		if (pw->amount <= amount)
		{
			booking(f, amount);
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
			while (p->clist != NULL)
			{
				if (strcmp(p->clist->name, name) == 0)
				{
					p->tickets += amount;
					Delete_clientList(&total, &(p->clist));
					printf("\n��Ʊ�ɹ����˿������Сʱ�ڷ���֧���˻�\n");
					update_queue(&p, amount);
					flag = 1;
					break;
				}
				p->clist = p->clist->next;
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
	printf("\n|    �����     |-|   �յ�վ  |-|      ����      |-|    ���ʱ��   |-|  �ɳ����˿���  |-|  ʣ��Ʊ��  |\n");
	p = p->next;
	while (p != NULL)
	{
		printf("   %-20s%-10s%-22s%-26s%-15d%-5d\n", p->flightID, p->destination, p->planeID, p->time, p->num, p->tickets);
		p = p->next;
	}
	getchar();
	printf("\n���������������һ����......");
	getchar();
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
	scanf("%d", &num);
	printf("\n��������Ʊ������");
	scanf("%d", &tickets);
	FlightList newFlight = Creat_Flight(destination, flightID, planeID, time, num, tickets);
	if (Insert_Flight(flight, &newFlight))
	{
		printf("\n������ӳɹ���\n");
	}
	getchar();
	printf("\n���������������һ����......");
	getchar();
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
		while (cp != NULL)
		{
			printf("\n");
			printf("���ࣺ%s       �����пͻ�����\n", flightID);
			printf("\n�ͻ����֣�%s    ��Ʊ����%d    ��λ�ȼ���%d �Ȳ�", cp->name, cp->amount, cp->rank);
			cp = cp->next;
		}
	}
	else
	{
		printf("\n��ѯ�����ú�����Ϣ����������ȷ�ĺ���ţ�");
	}
	getchar();
	printf("\n���������������һ����......");
	getchar();
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

int judge_int(void)  //��ֹ�û��������������ַ����淶�û���������
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
	printf("*       ��ӭʹ�ú��տ���ϵͳ       *\n");
	printf("*----------------------------------*\n");
	printf("*          0.������һ��            *\n");
	printf("*          1.��Ӻ���              *\n");
	printf("*          2.ɾ������              *\n");
	printf("*          3.�鿴�������ж���      *\n");
	printf("*          4.�鿴���к���          *\n");
	printf("************************************\n");
}
