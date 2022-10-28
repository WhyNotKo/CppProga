#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include"pch.h"

class C_stat
{
private:
	std::string name;
	int all_count;
	int work_count;
	double efficiency;

public:
	int id = 0;
	friend std::ostream& operator <<(std::ostream& out, C_stat& comp);

	friend std::istream& operator >> (std::istream& in, C_stat& comp);

	void change_cs();
};

