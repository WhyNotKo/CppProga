//#pragma once
//#include <iostream>
//#include <string>
//#include <fstream>
//#include "pch.h"
//
////using namespace std;
//
//class Pipe
//{
//private:
//	int id = 0;
//	int length = 0;
//	int diameter = 0;
//	std::string in_work = "n";
//
//public:
//	Pipe(int id);
//
//	void EditPipe();
//
//	friend std::istream& operator >> (std::istream& in, Pipe& p);
//	friend std::ostream& operator << (std::ostream& out, const Pipe& p);
//	//friend std::ifstream& operator >> (std::ifstream& in, Pipe& p);
//	//friend std::ofstream& operator << (std::ofstream& out, const Pipe& p);
//};
//
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include"pch.h"


class Pipe
{
private:
	float len = 0;
	float diameter = 0;
	bool in_work = false;
	//static int MaxID;

public:
	int id = 0;
	void EditPipe();


	friend std::istream& operator >> (std::istream& in, Pipe& Pp);
	friend std::ostream& operator << (std::ostream& out, const Pipe& Pp);
};
