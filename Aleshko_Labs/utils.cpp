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
			cout << "������� ���������� ��������..." << endl;
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
	cout << "\n 1. �������� �����"
		<< "\n 2. �������� ��"
		<< "\n 3. �������� ���� ��������"
		<< "\n 4. ���������"
		<< "\n 5. ���������"
		<< "\n 6. ������ � �������"
		<< "\n 7. ������ � ��"
		<< "\n 0. �����\n";
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
	cout << endl << "������ ���������." << endl;
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
		cout << "���� �� ��������!" << endl;
	}
	fin.close();
}

void Pipemenu(unordered_map<int, Pipe>& Pipes)
{
	int choice = 8;
	while (true)
	{
		cout << "�������: " << endl
			<< "1 - ������ ����" << endl
			<< "2 - ���������  ����" << endl
			<< "3 - �������� ����" << endl
			<< "0 - �����" << endl;
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
		cout << "���� ���!" << endl << endl;
		exit;
	}
	int choice;
	while(true)
	{
		cout << "�������: " << endl
			<< "1 - ���������� ����� "<< endl
			<< "2 - ������������ �����" << endl
			<< "0 - �����" << endl;
		choice = GetCorrectNumber(0, 2);

		unordered_set<int> selected;
		if (choice == 1)
		{
			cout << "���������� �����: " << endl << endl;

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
			cout << "�������: " << endl
				<< "1 - �������� ��������� ���� ����" << endl
				<< "2 - �������� �������� ���������" << endl
				<< "0 - �����" << endl;
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
			cout << endl << "�� ���������� �����: " << endl << endl;
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
				cout << "�������: " << endl
					<< "1 - �������� ��������� ���� ����" << endl
					<< "2 - �������� ��������� ��������� ����" << endl
					<< "0 - �����" << endl;
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
	cout << "������� ID ����, ��������� ������� ����� ��������(0 ����� ���������)"<< endl;
	unordered_set<int> pp = input_set(Pipes);
	for (auto& c : pp) 
		if(Pipes.find(c) != Pipes.end())
			Pipes[c].edit();
}
void DeletePipes(unordered_map<int, Pipe>& Pipes)
{
	cout << "������� ID ����, ������e ����� �������(0 ����� ���������)" << endl;
	for (auto& c : input_set(Pipes))
		Pipes.erase(c);
}

void CSmenu(unordered_map<int, C_stat>& Stations)
{
	int choice = 8;
	while (true)
	{
		cout << "�������: " << endl
			<< "1 - ����� ��" << endl
			<< "2 - ���������  ��" << endl
			<< "3 - �������� ��" << endl
			<< "0 - ����� � ����" << endl;
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
		cout << "�������: " << endl
			<< "1 - ����� �� �� ��������" << endl
			<< "2 - ����� �� �� % ��������������� �����" << endl
			<< "0 - ����� � ����" << endl;
		choice = GetCorrectNumber(0, 2);
		if (!choice) break;
		if (choice == 1)
		{
			cout << "������� ��� ��: ";
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
			cout << "������� min ������� ���������� ��: ";
			int min = GetCorrectNumber(0, 100);
			cout << "������� max ������� ���������� ��: ";
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
	cout << "������� ID �������, ������� ������ ��������: ";
	int id = GetCorrectNumber(0, 1000000);
	if (Stations.find(id) != Stations.end()) Stations[id].change_cs();
	else cout << "�� �� �������!" << endl;
}
void DeleteStat(unordered_map<int, C_stat>& Stations)
{
	cout << "������� ID ��, ������e ����� �������(0 ����� ���������)" << endl;

	for (auto& c : input_set(Stations))
		Stations.erase(c);
}
