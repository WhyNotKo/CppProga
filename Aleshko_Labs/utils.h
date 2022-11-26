#pragma once
#include "pch.h"
#include"Pipe.h"
#include"C_stat.h"

#include <iostream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>

using namespace std;

template <typename T>
T GetCorrectNumber(T min = 0, T max = 10000000)
{
	T x{};
	while (((cin >> x) || x<min || x>max) && (cin.peek() != EOF && cin.peek() != '\n'))
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "¬ведите корректное число... " << endl;
	}
	return x;
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
bool input_bool();

void cout_menu();

int input_menu();

void save_data(string name, const unordered_map<int, Pipe> Pipes, const unordered_map<int, C_stat> Stations);

void load_data(string name, int &MPID, int&MCID, unordered_map<int, Pipe>& Pipes, unordered_map<int, C_stat>& Stations );


void Pipemenu(unordered_map<int, Pipe>& Pipes);

void ShowPipes(unordered_map<int, Pipe>& Pipes);

void EditPipes(unordered_map<int, Pipe>& Pipes);

void DeletePipes(unordered_map<int, Pipe>& Pipes);


void CSmenu(unordered_map<int, C_stat>& Stations);

void findStat(unordered_map<int, C_stat> Stations);

void EditStat(unordered_map<int, C_stat>& Stations);

void DeleteStat(unordered_map<int, C_stat>& Stations);

tuple <int,int,int> getgts(const int MPID, const int MCID);

void GtsMenu(unordered_map<int, Pipe>& Pipes, unordered_map<int, C_stat>& Stations, const int MPID, const int MCID);