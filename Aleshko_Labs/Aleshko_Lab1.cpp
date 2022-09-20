// Aleshko_Lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include<string>


using namespace std;

struct Pipe
{

	int length;
	int diameter;
	bool in_work;
	
};

struct C_stat
{
	string name;
	int all_count;
	int work_count;
	double efficiency;
};
void cout_menu()
{
	system("cls");
	cout << " 1. Добавить трубу\n 2. Добавить КС\n 3. Просмотр всех объектов\n 4. Сохранить\n 5. Загрузить\n 0. Выход\n";
}

//int isitint(string a)
//{
//
//}
int input_menu()
{
	while (true)
	{
		/*int a;
		cin >> a;
		if ((a < 0) or (a > 5) or (!cin))
		{
			cout << "Введите корректное число..." << endl;
		}
		else
		{
			return a;
		}
		cin.clear();
		fflush(stdin);*/
		string str;
		cin >> str;
		bool err = true;
		for (int i = 0; i < 3; i++)
		{
			if ((str.length()!=1) or (str[0]-48>5))
			{
				err = false;
				break;
			}
		}
		//cout << str + " " << (int)str[0]<<" "<<str[0] + 5 << endl;

		if (!err)
		{
			cout << "Введите корректное число..." << endl;
			!err;
			cin.clear();
			continue;
		}
		/*else return str[0]-48;*/
		else return stoi(str);
	}
	
}

int main()
{

	setlocale(LC_ALL, "");

	Pipe pipe;
	pipe.in_work = 0;
	int menu = 8;
	int len, dim;
	bool sost;
	/*pipe.length = 0 ;
	pipe.diameter = 0;
	pipe.in_work = 0;*/


	C_stat comp;
	string name = "";
	double eff = 0;
	int all = 0, work = 0;
	cout_menu();
	while (menu)
	{
		
		menu = input_menu();
		if (menu == 0)
		{
			break;
			cout_menu();
		}
		if (menu == 1)
		{
			system("cls");
			cout << "Введите длину, диаметр и состояние трубы(1/0) через пробел" << endl;
			
			cin >> pipe.length >> pipe.diameter >> pipe.in_work;
			cout_menu();

			//cout << pipe.length << " " << pipe.diameter << " " << pipe.in_work << endl;
		}
		if (menu == 2)
		{
			system("cls");
			cout << "Введите название, кол-во цехов, работающих цехов и эффективность через пробел" << endl;

			cin >> comp.name >> comp.all_count >> comp.work_count >> comp.efficiency;
			/*comp.name = name;
			comp.all_count = all;
			comp.work_count = work;
			comp.efficiency = eff;*/

			cout_menu();
		}
		if (menu == 3)
		{
			system("cls");
			cout << "Длина трубы: " << pipe.length << " км\nДиаметр трубы: " << pipe.diameter << " мм\nСостояние: " << pipe.in_work << endl;
			cout << "\nНазвание КС: " << comp.name << " \nКоличество цехов: " << comp.all_count << " \nКоличество работающих цехов: " << comp.work_count << " \nЭффективность: " << comp.efficiency << endl;

			cout << "\n 1. Добавить трубу\n 2. Добавить КС\n 3. Просмотр всех объектов\n 4. Сохранить\n 5. Загрузить\n 0. Выход\n";
		}
		/*if (menu == 4)
		{
			
		}*/
	}
	return 0;
}
