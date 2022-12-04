#include "pch.h"
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
		<< "\n 8. ���������������� ����"
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

void save_data(string name,const unordered_map<int, Pipe> Pipes, const unordered_map<int, C_stat> Stations, const unordered_map<int, Network> webs)
{
	name = name + ".txt";
	ofstream fout(name);
	fout << Pipes.size() << " " << Stations.size() << " " << webs.size() << endl;

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
	for (auto& n : webs)
	{
		fout << n.second << endl;
	}
	cout << endl << "������ ���������." << endl;
	fout.close();
}


void load_data(string name,int &MPID,int &MCID,unordered_map<int, Pipe>& Pipes, unordered_map<int, C_stat>& Stations, unordered_map<int, Network>& webs)
{
	name = name + ".txt";
	

	ifstream fin(name);
	if (fin.is_open())
	{
		Pipes.clear();
		Stations.clear();
		webs.clear();
		int psize = 0, csize = 0, websize = 0;

		fin >> psize >> csize >> websize;
		//cout << psize << " " << csize << endl;
		int id = 0;
		Pipe pipe;
		C_stat comp;
		Network web;
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
		for (int i = 0; i < websize; ++i)
		{
			fin >> web;
			webs.emplace(web.webPipeid(), web);
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

//������ � ������(���-�� �� ����� ������ ����������)-----------------------------------------------------------------------------------------------------

pair<int, int> getpaircs(unordered_map<int, C_stat> Stations)
{
	cout << "������� ID 1 ��: ";
	int cs1 = input_id(Stations);
	cout << "������� ID 2 ��: ";
	int cs2 = input_id(Stations);
	while(true) {
		if (cs1 == cs2)
		{
			cout << "������� ������������ ��������: ";
			cs2 = input_id(Stations);
		}
		else
			break;
	}
	return pair<int, int>(cs1, cs2);
}

int getPipe(int diam, unordered_map<int, Pipe>& Pipes, unordered_map<int, Network>& webs, int& MPID)
{
	bool find = false;
	for (auto& p : Pipes)
	{
		if (((p.second).GetPipeDiam() == diam) && (!webs.contains(p.first)))
			return p.first;
	}

	cout << "����� �� �������, ��� ���:" << endl;
	Pipe pipe;
	cin >> pipe;
	pipe.setID(MPID);
	Pipes.emplace(MPID, pipe);
	MPID++;
	return MPID - 1;

}
void AddLink(unordered_map<int,Network> &webs, unordered_map<int, Pipe>& Pipes, unordered_map<int, C_stat>& Stations, int& MPID, vector<vector<bool>>& graph)
{
	pair<int, int> cs = getpaircs(Stations);
	while (true) {
		if (graph[cs.first-1][cs.second-1])
		{
			cs = getpaircs(Stations);
		}
		else
		{
			graph[cs.first-1][cs.second-1] = true;
			break;
		}
	}
	cout << "������� ������� �����: ";
	int diam = GetCorrectNumber(200, 1500);
	int Pid = getPipe(diam, Pipes, webs, MPID);
	Network edge;
	edge.create_link(Pid, cs.first, cs.second);
	webs.emplace(Pid,edge);
}

void topologicalSortUtil(int v, unordered_set<int>& visited, stack<int>& Stack, unordered_map<int, unordered_set<int>>& graph)
{
	visited.insert(v);
	for (auto& adj : graph[v])
	{
		if (!visited.contains(adj))
			topologicalSortUtil(adj, visited, Stack, graph);
	}

	Stack.push(v);
}

void top_sort(unordered_map <int, Network> webs) {
	std::unordered_map<int, std::unordered_set<int>> graph;

	for (auto& [pipe, edges] : webs) {
		graph[edges.get_stations().first].insert(edges.get_stations().second);
	}

	std::vector<int> graphNumeration;
	std::unordered_set<int> visited;
	int N = graph.size();

	std::stack<int> Stack;

	for (auto& [v, neighbours] : graph)
	{
		if (!visited.contains(v))
			topologicalSortUtil(v, visited, Stack, graph);
	}
	int i = 1;
	while (!Stack.empty())
	{
		std::cout << "Number " << i << ": "
			<< Stack.top()
			<< std::endl;

		Stack.pop();
		i++;
	}

}

void GtsMenu(unordered_map<int, Network>& webs,unordered_map<int, Pipe>& Pipes, unordered_map<int, C_stat>& Stations, int &MPID)
{
	vector<vector<bool>> graph;
	for(int i(0); i < Stations.size(); ++i)
	{
		vector<bool> current;
		for (int j(0); j < Stations.size(); ++j)
		{
			bool find = false;
			for (auto p : webs)
			{
				if (p.second.get_stations() == pair<int, int>{i+1, j+1})
					find = true;
			}
			if (find)
			{
				current.push_back(true);
			}
			else
				current.push_back(false);
		}
		graph.push_back(current);
	}
	while (true)
	{
		cout << "������� ����� �� 0 �� 4:" << endl
			<< "1 - ������ ���������������� ����" << endl
			<< "2 - ������� ��� ����" << endl
			<< "3 - ������������� ��������������� ��" << endl
			<< "0 - ����� � ����" << endl;
		int menu = GetCorrectNumber(0, 4);

		if (menu == 0)
			break;

		if (menu == 1)
		{
			AddLink(webs, Pipes, Stations, MPID, graph);
		}

		if (menu == 2)
		{
			for (auto& p : webs)
				cout << p.second;
		}
		if (menu == 3)
			top_sort(webs);

	}
}
