#pragma once
#include"Pipe.h"
#include"C_stat.h"
#include "pch.h"

#include <iostream>
#include <string>
#include <tuple>
#include <unordered_map>

using namespace std;

template <typename T>
T GetCorrectNumber(T min = 0, T max = 10000000);

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