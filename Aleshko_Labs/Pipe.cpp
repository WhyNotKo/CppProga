//#include "Pipe.h"
//#include "utils.h"
#include "pch.h"
#include "Pipe.h"
#include "utils.h"
#include <unordered_map>


std::istream& operator >> (std::istream& in, Pipe& Pp) {
	std::cout << "������� ����� �����: ";
	Pp.len = GetCorrectNumber(0,1000000);
	std::cout << "������� ������� �����: ";
	Pp.diameter = GetCorrectNumber(0,500000);
	std::cout << "����� ��������?(y - ��������, n - �� ��������: ";
	Pp.in_work = input_bool();
	return in;
}


std::ifstream& operator >> (std::ifstream& fin, Pipe& Pp)
{
	fin >> Pp.len
		>> Pp.diameter 
		>> Pp.in_work;
	return fin;
}



std::ostream& operator << (std::ostream& out, const Pipe& Pp) {
	if (!(Pp.len == 0)) {
		std::cout << "ID �����: " << Pp.id << std::endl;
		std::cout << "����� �����: " << Pp.len << std::endl;
		std::cout << "������� �����: " << Pp.diameter << std::endl;
		std::string wrok = Pp.in_work ? "����� ��������" : "����� �� ��������";
		std::cout << wrok << std::endl << std::endl;
	}
	return out;
}

std::ofstream& operator << (std::ofstream& fout, const Pipe& Pp)
{
	fout << Pp.len << " "
		<< Pp.diameter << " "
		<< Pp.in_work << std::endl;
	return fout;
}

bool Pipe::ConditionPipe()
{
	return in_work;
}

void Pipe::edit()
{
	in_work = !in_work;
}
