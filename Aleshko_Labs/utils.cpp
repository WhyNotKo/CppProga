#include "pch.h"
#include "utils.h"

#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include<queue>
#include<vector>

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
		<< "\n 8. Газотранспортная сеть"
		<< "\n 0. Выход\n";
}

int input_menu()
{
	while (true)
	{
		int a = GetCorrectNumber(0, 9);
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
	cout << endl << "Данные сохранены." << endl;
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
		cout << "Файл не открылся!" << endl;
	}
	fin.close();
}

void Pipemenu(unordered_map<int, Pipe>& Pipes,unordered_map<int,Network>& webs)
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
		if (choice == 3) DeletePipes(Pipes,webs);
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
void DeletePipes(unordered_map<int, Pipe>& Pipes, unordered_map<int,Network>& webs)
{
	cout << "Введите ID труб, которыe нужно удалить(0 чтобы закончить)" << endl;
	for (auto& c : input_set(Pipes))
	{
		Pipes.erase(c);
		if (webs.contains(c))
			webs.erase(c);
	}

	
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

//Работа с графом(что-то на очень сильно костыльном)-----------------------------------------------------------------------------------------------------

pair<int, int> getpaircs(unordered_map<int, C_stat> Stations)
{
	cout << "Введите ID 1 КС: ";
	int cs1 = input_id(Stations);
	cout << "Введите ID 2 КС: ";
	int cs2 = input_id(Stations);
	while(true) {
		if (cs1 == cs2)
		{
			cout << "Введите отличающееся значение: ";
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

	cout << "Труба не найдена, так что:" << endl;
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
	cout << "Введите диаметр трубы: ";
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
		std::cout << "Нумер " << i << ": "
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
		cout << "Введите число от 0 до 4:" << endl
			<< "1 - Задать газотранспортную сеть" << endl
			<< "2 - Вывести все сети" << endl
			<< "3 - Топологически отсортированное всё" << endl
			<< "4 - Кратчайший путь" << endl
			<< "5 - Максимальный поток" << endl
			<< "0 - Выйти в меню" << endl;
		int menu = GetCorrectNumber(0, 6);

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

		if (menu == 4)
			shortest_path(Pipes, Stations, webs);

		if (menu == 5)
			get_max_flow(Pipes, Stations, webs);

	}
}

bool bfs(const std::vector<std::vector<double>>& r_graph, int s, int t, std::vector<int>& parent) {

	const int V = r_graph.size();
	std::vector<int> visited(V, 0);
	std::queue<int> q;
	int u;

	q.push(s);
	parent[s] = -1;

	while (!q.empty()) {
		u = q.front();
		q.pop();

		for (int v = 0; v < V; v++) {

			if (visited[v] == false && r_graph[u][v] > 0) {

				parent[v] = u;

				if (v == t) {

					return true;
				}

				q.push(v);
				visited[v] = true;

			}
		}
	}

	return false;
}


double ford_fulkerson(std::vector<std::vector<double>>& graph, int s, int t) {

	int u, v;
	int V = graph.size();
	std::vector<std::vector<double>> r_graph = graph;
	std::vector<int> parent(V, 0);
	double max_flow = 0;
	double path_flow;


	while (bfs(r_graph, s, t, parent)) {

		path_flow = std::numeric_limits<double>::max();

		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			path_flow = std::min(path_flow, r_graph[u][v]);
		}

		for (v = t; v != s; v = parent[v]) {
			u = parent[v];

			r_graph[u][v] -= path_flow;
			r_graph[v][u] += path_flow;
		}

		max_flow += path_flow;
	}

	return max_flow;
}

std::vector<double> dijkstra(std::vector<std::vector<double>> graph, int src) {

	std::unordered_set<int> spt_set;
	double Inf = std::numeric_limits<double>::max();
	std::vector<double> dist(graph.size(), Inf);
	dist[src] = 0;

	for (int count(0); count < (graph.size() - 1); ++count) {

		int u = min_dist_node(spt_set, dist);

		spt_set.insert(u);


		for (int v(0); v < graph.size(); ++v) {
			if (!spt_set.contains(v) && graph[u][v] != 0 && dist[u] != Inf)
				dist[v] = std::min(dist[v], dist[u] + graph[u][v]);
		}
	}

	return dist;
}

void shortest_path(unordered_map<int, Pipe>& Pipes, unordered_map<int, C_stat>& Stations, std::unordered_map<int, Network>& edges)
{

	std::unordered_map<int, int> id_idx;
	std::unordered_map<int, int> idx_id;
	std::unordered_set<int> spt_compr_stations;

	std::vector<std::vector<double>> graph(Stations.size(), std::vector<double>(Stations.size(), 0.0));

	int idx = 0;

	for (auto& [Pp_id, edge] : edges) {
		if (!spt_compr_stations.contains(edge.get_stations().first)) {
			id_idx[edge.get_stations().first] = idx;
			idx_id[idx] = edge.get_stations().first;
			spt_compr_stations.insert(edge.get_stations().first);

			idx++;
		}

		if (!spt_compr_stations.contains(edge.get_stations().second)) {
			id_idx[edge.get_stations().second] = idx;
			idx_id[idx] = edge.get_stations().second;
			spt_compr_stations.insert(edge.get_stations().second);

			idx++;
		}
	}

	for (auto& [Pp_id, edge] : edges) {
		if (Pipes[Pp_id].ConditionPipe() == true)
			graph[id_idx[edge.get_stations().first]][id_idx[edge.get_stations().second]] = Pipes[Pp_id].get_len();
	}

	int src;

	while (true) {
		std::cout << "Начальная вершина: ";
		src = GetCorrectNumber(1, std::numeric_limits<int>::max());
		if (id_idx.contains(src)) {
			src = id_idx[src];
			break;
		}
		std::cout << "Нет такого" << std::endl;
	}

	std::vector<double> dist = dijkstra(graph, src);

	for (int i(0); i < dist.size(); ++i) {
		std::cout << "Расстояние вершины " << idx_id[i];
		if (dist[i] == std::numeric_limits<double>::max())
			std::cout << " это Inf" << std::endl;
		else
			std::cout << " это " << dist[i] << std::endl;
	}
}

int min_dist_node(const std::unordered_set<int>&spt_set, const std::vector<double>&dist) {

	double least = std::numeric_limits<double>::max();
	int idx = 0;

	for (int i(0); i < dist.size(); ++i) {
		if (dist[i] < least && !spt_set.contains(i)) {
			least = dist[i];
			idx = i;
		}
	}

	return idx;
}

void get_max_flow(unordered_map<int, Pipe>& Pipes, unordered_map<int, C_stat>& Stations, std::unordered_map<int, Network>& edges) {
	std::unordered_map<int, int> id_idx;
	std::unordered_map<int, int> idx_id;
	std::unordered_set<int> spt_compr_stations;

	std::vector<std::vector<double>> graph(Stations.size(), std::vector<double>(Stations.size(), 0.0));

	int idx = 0;

	for (auto& [Pp_id, edge] : edges) {
		if (!spt_compr_stations.contains(edge.get_stations().first)) {
			id_idx[edge.get_stations().first] = idx;
			idx_id[idx] = edge.get_stations().first;
			spt_compr_stations.insert(edge.get_stations().first);

			idx++;
		}

		if (!spt_compr_stations.contains(edge.get_stations().second)) {
			id_idx[edge.get_stations().second] = idx;
			idx_id[idx] = edge.get_stations().second;
			spt_compr_stations.insert(edge.get_stations().second);

			idx++;
		}
	}

	for (auto& [Pp_id, edge] : edges) {
		if (Pipes[Pp_id].ConditionPipe() == true)
			graph[id_idx[edge.get_stations().first]][id_idx[edge.get_stations().second]] = Pipes[Pp_id].GetPipeDiam();
	}

	int start, finish;

	while (true) {
		std::cout << "Начальная вершина: ";
		start = GetCorrectNumber(1, std::numeric_limits<int>::max());
		if (id_idx.contains(start)) {
			start = id_idx[start];
			break;
		}
		std::cout << "Нет такого" << std::endl;
	}

	while (true) {
		std::cout << "Конечная вершина: ";
		finish = GetCorrectNumber(1, std::numeric_limits<int>::max());
		if (id_idx.contains(finish)) {
			finish = id_idx[finish];
			break;
		}
		std::cout << "Нет такого" << std::endl;
	}

	std::cout << "Максимальный поток " << idx_id[start] << " to " << idx_id[finish] << " is "
		<< ford_fulkerson(graph, start, finish) << std::endl;

}
