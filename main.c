#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "FlightBookTicketSystem.h"

#pragma warning(disable:4996) //visual studio安全性问题scanf,getchar
#pragma warning(disable:6031) //visual studio返回值被忽略问题strcmp


int main(void)
{
	FlightList flight = NULL;
	Init_Flight(&flight);

	FlightList f1 = Creat_Flight("广州", "011", "022", "2021-1-7-14:00", 200, 200);
	FlightList f2 = Creat_Flight("广州", "012", "021", "2021-1-8-14:00", 100, 100);
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
					printf("输入有误，请重新输入！");
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
					printf("输入有误，请重新输入！");
					break;
				}
			} while (choice != 0);
			break;
		}
		default:
			printf("输入有误，请重新输入！");
			break;
		}
	} while (choice != 0);

	free(flight);
	free(f1);
	free(f2);
	printf("\n\n\t\t感谢使用航空客运订票系统！\n\n\n");
	printf("\n\n\n\n\t\t班级：19级信安1班\n\n\t\t姓名：徐国涛\n\n\t\t学号：3119005436\n\n\n\n\n\n\n\n\n");
	system("pause");
	return 0;
}
