#include "pch.h"
#include"C_stat.h"
#include"Pipe.h"
#include "utils.h"

#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>


using namespace std;


bool input_bool()
{
	string str;
	bool err = true;
	while (true)
	{
		cin >> str;
		if ((str[0] != 'y') && (str[0] != 'n')) err = false;

		if (!err)
		{
			cout << "Введите корректное значение..." << endl;
			err = true;
			continue;
		}
		if (str[0] == 'y') return true;
		else str = "n";
		return false;
	}
}

void cout_menu()
{
	//system("cls");
	cout << "\n 1. Добавить трубу"
		<< "\n 2. Добавить КС"
		<< "\n 3. Просмотр всех объектов"
		<< "\n 4. Сохранить"
		<< "\n 5. Загрузить"
		<< "\n 6. Работа с трубами"
		<< "\n 7. Работа с КС"
		<< "\n 0. Выход\n";
}

int input_menu()
{
	while (true)
	{
		int a = GetCorrectNumber(0, 7);
		return a;
	}
}

void save_data(string name,const unordered_map<int, Pipe> Pipes, const unordered_map<int, C_stat> Stations)
{
	name = name + ".txt";
	ofstream fout(name);
	fout << Pipes.size() << " " << Stations.size() << endl;

	for (auto &p : Pipes)
	{
		fout << p.first << endl;
		fout << p.second <<endl;
	}
	
	for (auto& c : Stations)
	{
		fout << c.first << endl;
		fout << c.second << endl;
	}
	cout << endl << "Данные сохранены." << endl;
	fout.close();
}


void load_data(string name,int &MPID,int &MCID,unordered_map<int, Pipe>& Pipes, unordered_map<int, C_stat>& Stations)
{
	name = name + ".txt";
	

	ifstream fin(name);
	if (fin.is_open())
	{
		Pipes.clear();
		Stations.clear();
		int psize = 0, csize = 0;

		fin >> psize >> csize;
		//cout << psize << " " << csize << endl;
		int id = 0;
		Pipe pipe;
		C_stat comp;
		for (int i = 0; i < psize; ++i)
		{
			fin >> id;
			fin >> pipe;
			pipe.setID(id);
			MPID = id + 1;
			Pipes.emplace(id, pipe);
		}
		id = 0;
		for (int i = 0; i < csize; ++i)
		{
			fin >> id;
			MCID = id+1;
			fin >> comp;
			comp.id = id;
			comp.eff_cs();
			Stations.emplace(id, comp);
		}
	}
	else 
	{
		cout << "Файл не открылся!" << endl;
	}
	fin.close();
}

void Pipemenu(unordered_map<int, Pipe>& Pipes)
{
	int choice = 8;
	while (true)
	{
		cout << "Введите: " << endl
			<< "1 - Фильтр труб" << endl
			<< "2 - Изменение  труб" << endl
			<< "3 - Удаление труб" << endl
			<< "0 - Назад" << endl;
		choice = GetCorrectNumber(0, 3);
		if (!choice)
			break;
		if (choice == 1) ShowPipes(Pipes);
		if (choice == 2) EditPipes(Pipes);
		if (choice == 3) DeletePipes(Pipes);
	}
}

void ShowPipes(unordered_map<int, Pipe>& Pipes)
{
	Pipe pipe;
	if (!Pipes.size()) 
	{
		cout << "Труб нет!" << endl << endl;
		exit;
	}
	int choice;
	while(true)
	{
		cout << "Введите: " << endl
			<< "1 - Работающие трубы "<< endl
			<< "2 - Неработающие трубы" << endl
			<< "0 - Назад" << endl;
		choice = GetCorrectNumber(0, 2);

		unordered_set<int> selected;
		if (choice == 1)
		{
			cout << "Работающие трубы: " << endl << endl;

			selected.clear();
			for (const auto& p : Pipes)
			{
				pipe = p.second;
				if (pipe.ConditionPipe())
				{
					selected.insert(p.first);
					cout << pipe;
				}
			}
			cout << "Введите: " << endl
				<< "1 - Изменить состояние всех труб" << endl
				<< "2 - Изменить введённое множество" << endl
				<< "0 - Назад" << endl;
			choice = GetCorrectNumber(0, 2);
			if (choice == 0)
				break;
			if (choice == 2)
			{
				selected = input_set(selected);
			}
			for (const auto& p : selected)
				Pipes[p].edit();
		}
		if(choice == 2)
		{
			selected.clear();
			cout << endl << "НЕ Работающие трубы: " << endl << endl;
			for (const auto& p : Pipes)
			{
				pipe = p.second;
				if (!pipe.ConditionPipe())
				{
					selected.insert(p.first);
					cout << pipe;
				}
			}
			int choice = 8;
			while (true)
			{
				cout << "Введите: " << endl
					<< "1 - Изменить состояние всех труб" << endl
					<< "2 - Изменить состояние выбранных труб" << endl
					<< "0 - Назад" << endl;
				choice = GetCorrectNumber(0, 2);
				if (!choice)
					break;
				if (choice == 2)
				{
					selected = input_set(selected);
				}
				for (const auto& p : selected)
					Pipes[p].edit();
			}
		}
		if (!choice) break;
		
	}
}
void EditPipes(unordered_map<int, Pipe>& Pipes)
{
	cout << "Введите ID труб, состояние которых нужно изменить(0 чтобы закончить)"<< endl;
	unordered_set<int> pp = input_set(Pipes);
	for (auto& c : pp) 
		if(Pipes.find(c) != Pipes.end())
			Pipes[c].edit();
}
void DeletePipes(unordered_map<int, Pipe>& Pipes)
{
	cout << "Введите ID труб, которыe нужно удалить(0 чтобы закончить)" << endl;
	for (auto& c : input_set(Pipes))
		Pipes.erase(c);
}

void CSmenu(unordered_map<int, C_stat>& Stations)
{
	int choice = 8;
	while (true)
	{
		cout << "Введите: " << endl
			<< "1 - Поиск КС" << endl
			<< "2 - Изменение  КС" << endl
			<< "3 - Удаление КС" << endl
			<< "0 - Выйти в меню" << endl;
		choice = GetCorrectNumber(0, 3);
		if (!choice)
		{
			cout_menu();
			break;
		}
		if (choice == 1) findStat(Stations);
		if (choice == 2) EditStat(Stations);
		if (choice == 3) DeleteStat(Stations);
	}
}
void findStat(unordered_map<int, C_stat> Stations)
{
	int choice = 9;
	while (true)
	{
		cout << "Введите: " << endl
			<< "1 - Поиск КС по названию" << endl
			<< "2 - Поиск КС по % задействованных цехов" << endl
			<< "0 - Выйти в меню" << endl;
		choice = GetCorrectNumber(0, 2);
		if (!choice) break;
		if (choice == 1)
		{
			cout << "Введите имя КС: ";
			string pname;
			cin.ignore();
			getline(cin, pname);
			C_stat cs;
			for (const auto& p : Stations)
			{
				cs = p.second;
				if (cs.getname().find(pname) != 0)
					cout << cs;
			}
			break;
		}
		if (choice == 2)
		{
			cout << "Введите min процент работающих КС: ";
			int min = GetCorrectNumber(0, 100);
			cout << "Введите max процент работающих КС: ";
			int max = GetCorrectNumber(min, 100);
			C_stat cs;
			for (const auto& p : Stations)
			{
				cs = p.second;
				if ((cs.eff_cs() * 100 >= min) && (cs.eff_cs() * 100 <=max)) cout << cs;
			}
			break;
		}
	}
}
void EditStat(unordered_map<int,C_stat>& Stations)
{
	cout << "Введите ID станции, которую хотите изменить: ";
	int id = GetCorrectNumber(0, 1000000);
	if (Stations.find(id) != Stations.end()) Stations[id].change_cs();
	else cout << "КС не найдена!" << endl;
}
void DeleteStat(unordered_map<int, C_stat>& Stations)
{
	cout << "Введите ID КС, которыe нужно удалить(0 чтобы закончить)" << endl;

	for (auto& c : input_set(Stations))
		Stations.erase(c);
}
