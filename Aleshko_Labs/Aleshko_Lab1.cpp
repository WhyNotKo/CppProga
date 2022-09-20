// Aleshko_Lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>


using namespace std;

struct Pipe
{

	int length;
	int diameter;
	string in_work;
	
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

string input_bool()
{
	while (true)
	{
		string str;
		cin >> str;
		bool err = true;
		if ((str[0] != 'y') && (str[0] != 'n')) err = false;

		if (!err)
		{
			cout << "Введите корректное значение..." << endl;
			!err;
			continue;
		}
		return str;
	}
}

int input_int()
{
	while (true)
	{
		string str;
		cin >> str;
		bool err = true;
		for (auto c : str)
		{
			if ((c-48 >0) or (c-48 <10))
			{
				!err;
				break;
			}
		}

		if (!err)
		{
			cout << "Введите корректное число..." << endl;
			!err;
			//cin.clear();
			continue;
		}
		else return stoi(str);
	}

}
int input_menu()
{
	string str;
	while (true)
	{
		
		cin >> str;
		bool err = true;
		for (int i = 0; i < str.length(); i++)
		{
			if ((str.length()!=1) or (str[0]-48>5))
			{
				err = false;
				break;
			}
		}

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
	int menu = 8;


	C_stat comp;
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
			cout << "Введите длину, диаметр и состояние трубы(y/n) через пробел" << endl;
			pipe.length = input_int();
			pipe.diameter = input_int();
			pipe.in_work = input_bool();
			cout_menu();

			//cout << pipe.length << " " << pipe.diameter << " " << pipe.in_work << endl;
		}
		if (menu == 2)
		{
			system("cls");
			cout << "Введите название, кол-во цехов, работающих цехов и эффективность через пробел" << endl;
			
			cin >> comp.name;
			comp.all_count = input_int();
			comp.work_count = input_int(); 
			comp.efficiency = input_int();

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
