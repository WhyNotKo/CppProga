#pragma once
#include "pch.h"
#include"Pipe.h"
#include"C_stat.h"
#include"Network.h"

#include <iostream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <stack>

using namespace std;

template <typename T>
T GetCorrectNumber(T least = 0, T great = 1000000) {
	T val = 0;
	while (true) {
		if (std::cin >> val && (std::cin.peek() == EOF || std::cin.peek() == '\n') && (val >= least) && (val < great)) return val;
		else {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "¬ведите нормальное значение: ";
		}
	}
}

template <typename T>
std::unordered_set<int> input_set(const T& all)
{
	std::unordered_set<int> s;
	int number = 0;
	while (true)
	{
		number = GetCorrectNumber(0, 10000);
		if (number == 0)
			break;
		if (all.contains(number))
			s.insert(number);
	}
	return s;
}
template <typename T>
int input_id(const T& all)
{
	int number = 0;
	while (true)
	{
		number = GetCorrectNumber(0, 10000);
		if (all.contains(number))
			return number;
		else
			cout << "¬ведите другое значение" << endl;
	}
}
bool input_bool();

void cout_menu();

int input_menu();

void save_data(string name, const unordered_map<int, Pipe> Pipes, const unordered_map<int, C_stat> Stations, const unordered_map<int, Network> webs);

void load_data(string name, int &MPID, int&MCID, unordered_map<int, Pipe>& Pipes, unordered_map<int, C_stat>& Stations, unordered_map<int, Network>& webs);


void Pipemenu(unordered_map<int, Pipe>& Pipes, unordered_map<int,Network>& webs);

void ShowPipes(unordered_map<int, Pipe>& Pipes);

void EditPipes(unordered_map<int, Pipe>& Pipes);

void DeletePipes(unordered_map<int, Pipe>& Pipes, unordered_map <int,Network>& webs);


void CSmenu(unordered_map<int, C_stat>& Stations);

void findStat(unordered_map<int, C_stat> Stations);

void EditStat(unordered_map<int, C_stat>& Stations);

void DeleteStat(unordered_map<int, C_stat>& Stations);


void GtsMenu(unordered_map<int, Network>& webs, unordered_map<int, Pipe>& Pipes, unordered_map<int, C_stat>& Stations, int& MPID);

double ford_fulkerson(std::vector<std::vector<double>>& graph, int s, int t);

bool bfs(const std::vector<std::vector<double>>& r_graph, int s, int t, std::vector<int>& parent);

std::vector<double> dijkstra(std::vector<std::vector<double>> graph, int src);

void shortest_path(unordered_map<int, Pipe>& Pipes, unordered_map<int, C_stat>& Stations, std::unordered_map<int, Network>& edges);

int min_dist_node(const std::unordered_set<int>& spt_set, const std::vector<double>& dist);

void get_max_flow(unordered_map<int, Pipe>& Pipes, unordered_map<int, C_stat>& Stations, std::unordered_map<int, Network>& edges);
