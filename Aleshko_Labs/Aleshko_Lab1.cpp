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
	cout << "\n 1. Добавить трубу\n 2. Добавить КС\n 3. Просмотр всех объектов\n 4. Сохранить\n 5. Загрузить\n 6. Изменить трубу\n 7. Изменить КС\n 0. Выход\n";
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
		if (str[0] == 'y') str = "Работает";
		else str = "Ремонтируется";
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
		for (int i = 0; i < str.length();++i)
		{
			if (!isdigit(str[i]))
			{
				err = false;
				break;
			}
		}

		if (!err)
		{
			cout << "Введите корректное число..." << endl;
			err = true;
			cin.clear();
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
			if ((str.length()!=1) or (str[0]-48>7))
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

void cout_obj(Pipe pipe, C_stat comp)
{
	system("cls");
	cout << "Длина трубы: " << pipe.length << " км\nДиаметр трубы: " << pipe.diameter << " мм\nСостояние: " << pipe.in_work << endl;
	cout << "\nНазвание КС: " << comp.name << " \nКоличество цехов: " << comp.all_count << " \nКоличество работающих цехов: " << comp.work_count << " \nЭффективность: " << comp.efficiency << endl;

	cout << "\n 1. Добавить трубу\n 2. Добавить КС\n 3. Просмотр всех объектов\n 4. Сохранить\n 5. Загрузить\n 6. Изменить трубу\n 7. Изменить КС\n 0. Выход\n";
}

void input_pipe(Pipe& pipe)
{
	system("cls");
	cout << "Введите длину трубы" << endl;
	pipe.length = input_int();

	cout << "Введите диаметр трубы" << endl;
	pipe.diameter = input_int();

	cout << "Введите состояние трубы(y/n) (у если работает, n если в ремонте)" << endl;
	pipe.in_work = input_bool();
	cout_menu();
}

void input_cp(C_stat& comp)
{
	system("cls");
	cout << "Введите название КС" << endl;

	cin >> comp.name;

	cout << "Введите количество всех цехов КС" << endl;
	comp.all_count = input_int();

	cout << "Введите количество работающих цехов КС" << endl;
	while (true)
	{
		int check = input_int();
		if (check > comp.all_count)
		{
			cout << "Введите меньше цехов, чем их всего..." << endl;
			continue;
		}
		else
		{
			comp.work_count = check;
			break;
		}
	}
		cout << "Введите эффективность КС" << endl;
		comp.efficiency = input_int();

		cout_menu();
}

void save_data(Pipe pipe, C_stat comp)
{
	ofstream fout("basa.txt");
	fout << pipe.length << " " << pipe.diameter << " " << pipe.in_work << endl;
	fout << comp.name << " " << comp.all_count << " "  << comp.work_count << " "  << comp.efficiency << endl;
	fout.close();
	cout << "Данные сохранены." << endl;
}

void load_data(Pipe& pipe, C_stat& comp)
{
	ifstream fin("basa.txt");
	if (!fin.eof())
	{
		fin >> pipe.length >> pipe.diameter >> pipe.in_work;
		fin >> comp.name >> comp.all_count >> comp.work_count >> comp.efficiency;
		fin.close();
		cout << "Данные загружены." << endl;
	}
	else
	{
		cout << "Данных для загрузки нет..." << endl;
	}
}

void change_pipe(Pipe& pipe)
{
	cout << "Введите состояние трубы(y/n) (у если работает, n если в ремонте)" << endl;
	pipe.in_work = input_bool();
	cout_menu();
}

void change_cs(C_stat& comp)
{
	cout << "Введите количество работающих цехов КС, сейчас " << comp.work_count << " из " << comp.all_count << endl;
	while (true)
	{
		int check = input_int();
		if (check > comp.all_count)
		{
			cout << "Введите меньше цехов, чем их всего..." << endl;
			continue;
		}
		else
		{
			comp.work_count = check;
			break;
		}
	}
	cout_menu();
}

int main()
{
	setlocale(LC_ALL, "");

	Pipe pipe;
	pipe.length = 0;
	C_stat comp;
	comp.all_count = 0;
	int menu ;
	cout_menu();
	while (true)
	{
		
		menu = input_menu();
		if (menu == 0)
		{
			cout_menu();
			continue;
			
		}
		if (menu == 1) if (!pipe.length) input_pipe(pipe); else cout << "Труба уже существует" << endl;
		if (menu == 2) if (!comp.all_count) input_cp(comp); else cout << "КС уже существует" << endl;
		if (menu == 3) cout_obj(pipe, comp);
		if (menu == 4) save_data(pipe, comp);
		if (menu == 5) load_data(pipe, comp);
		if (menu == 6) if (pipe.length) change_pipe(pipe); else cout << "Труба не существует" << endl;
		if (menu == 7) if (comp.all_count) change_cs(comp); else cout << "КС не существует" << endl;
	}
	return 0;
}
