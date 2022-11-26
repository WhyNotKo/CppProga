#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include"pch.h"


class Pipe
{
private:
	float len = 0;
	float diameter = 0;
	bool in_work = false;
	int id = 0;

public:
	
	void edit();

	void setID(int id);

	bool ConditionPipe();

	int GetPipeDiam();

	friend std::istream& operator >> (std::istream& in, Pipe& Pp);

	friend std::ifstream& operator >> (std::ifstream& fin, Pipe& Pp);

	friend std::ostream& operator << (std::ostream& out, const Pipe& Pp);

	friend std::ofstream& operator << (std::ofstream& fout, const Pipe& Pp);
};
