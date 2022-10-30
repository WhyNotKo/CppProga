#include "pch.h"
#include"C_stat.h"
#include"Pipe.h"
#include "utils.h"

#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>


using namespace std;

template <typename T>
T GetCorrectNumber(T min, T max)
{
	T x{};
	while ((cin >> x).fail() || x<min || x>max)
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Введите корректное число... " << endl;
	}
	return x;
}

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
		cout << psize << " " << csize << endl;
		int id = 0;
		Pipe pipe;
		C_stat comp;
		for (int i = 0; i < psize; ++i)
		{
			fin >> id;
			fin >> pipe;
			pipe.id = id;
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
			Stations.emplace(id, comp);
		}
	}
	else 
	{
		cout << "Файл не открылся!" << endl;
	}
}

void Pipemenu(unordered_map<int, Pipe>& Pipes)
{
	int choise = 8;
	while (true)
	{
		cout << "Введите: " << endl
			<< "1 - Просмотр труб" << endl
			<< "2 - Изменение  труб" << endl
			<< "3 - Удаление труб" << endl
			<< "0 - Выйти в меню" << endl;
		choise = GetCorrectNumber(0, 3);
		if (!choise)
		{
			cout_menu();
			break;
		}
		if (choise == 1) ShowPipes(Pipes);
		if (choise == 2) EditPipes(Pipes);
		if (choise == 3) DeletePipes(Pipes);
	}
}

void ShowPipes(unordered_map<int, Pipe>& Pipes)
{
	Pipe pipe;
	cout << "Работающие трубы: " << endl<<endl;
	for (const auto& p : Pipes)
	{
		pipe = p.second;
		if(pipe.ConditionPipe()) cout<<pipe;
	}

	cout << endl << "НЕ Работающие трубы: " << endl << endl;
	for (const auto& p : Pipes)
	{
		pipe = p.second;
		if (!pipe.ConditionPipe()) cout << pipe;
	}
}
void input_set(unordered_set<int>& s)
{
	s.clear();
	int number = 9;
	while (true)
	{
		number = GetCorrectNumber(-1, 10000);
		if (number < 0) break;
		s.insert(number);
	}
}
void EditPipes(unordered_map<int, Pipe>& Pipes)
{
	unordered_set<int> pp;
	cout << "Введите ID труб, состояние которых нужно изменить(-1 чтобы закончить)"<< endl;
	input_set(pp);
	for (auto& c : pp) if(Pipes.find(c) != Pipes.end())Pipes[c].edit();
}
void DeletePipes(unordered_map<int, Pipe>& Pipes)
{
	unordered_set<int> pp;
	cout << "Введите ID труб, которыe нужно удалить(-1 чтобы закончить)" << endl;
	input_set(pp);
	for (auto& c : pp) if (Pipes.find(c) != Pipes.end())Pipes.erase(c);
}