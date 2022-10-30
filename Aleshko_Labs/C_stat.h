#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include"pch.h"

class C_stat
{
private:
	std::string name = "";
	int all_count = 0;
	int work_count = 0;
	double efficiency = 0;

public:
	int id = 0;
	friend std::ostream& operator <<(std::ostream& out,const C_stat& comp);

	friend std::ofstream& operator <<(std::ofstream& fout, const C_stat& comp);

	friend std::istream& operator >> (std::istream& in, C_stat& comp);

	friend std::ifstream& operator >> (std::ifstream& fin, C_stat& comp);

	void change_cs();
};

