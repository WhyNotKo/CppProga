// Aleshko_Lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <fstream>


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

int check_menu(int a)
{
	if ((a < 0) or (a > 5))
	{
		cout << "Введите корректное число..." << endl;
		return 1;
	}
	else return 0;
}

int main()
{

	setlocale(LC_ALL, "");

	Pipe pipe;
	pipe.in_work = 0;
	int menu;
	int len, dim;
	bool sost;
	/*pipe.length = 0 ;
	pipe.diameter = 0;
	pipe.in_work = 0;*/


	C_stat comp;
	string name = "";
	double eff = 0;
	int all = 0, work = 0;
	cout << " 1. Добавить трубу\n 2. Добавить КС\n 3. Просмотр всех объектов\n 4. Сохранить\n 5. Загрузить\n 0. Выход\n";
	while (true)
	{
		
		cin >> menu;
		if (check_menu(menu) != 0)
		{
			continue;
		}
		if (menu == 0)
		{
			break;
			system("cls");
			cout << " 1. Добавить трубу\n 2. Добавить КС\n 3. Просмотр всех объектов\n 4. Сохранить\n 5. Загрузить\n 0. Выход\n";
		}
		if (menu == 1)
		{
			system("cls");
			cout << "Введите длину, диаметр и состояние трубы(1/0)" << endl;
			
			cin >> len >> dim >> sost;
			pipe.length = len;
			pipe.diameter = dim;
			pipe.in_work = sost;

			system("cls");
			cout << " 1. Добавить трубу\n 2. Добавить КС\n 3. Просмотр всех объектов\n 4. Сохранить\n 5. Загрузить\n 0. Выход\n";

			//cout << pipe.length << " " << pipe.diameter << " " << pipe.in_work << endl;
		}
		if (menu == 2)
		{
			system("cls");
			cout << "Введите название, кол-во цехов, кол-во работающих цехов и эффективность" << endl;

			cin >> name >> all >> work >> eff;
			comp.name = name;
			comp.all_count = all;
			comp.work_count = work;
			comp.efficiency = eff;

			system("cls");
			cout << " 1. Добавить трубу\n 2. Добавить КС\n 3. Просмотр всех объектов\n 4. Сохранить\n 5. Загрузить\n 0. Выход\n";
		}
		if (menu == 3)
		{
			cout << pipe.length << " " << pipe.diameter << " " << pipe.in_work << endl;
			cout << " " << comp.name << " " << comp.all_count << " " << comp.work_count << " " << comp.efficiency << endl;
		}
		/*if (menu == 4)
		{
			
		}*/
	}
	return 0;
}
