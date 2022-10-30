//#include "Pipe.h"
//#include "utils.h"
#include "pch.h"
#include "Pipe.h"
#include "utils.h"
#include <unordered_map>


std::istream& operator >> (std::istream& in, Pipe& Pp) {
	std::cout << "Введите длину трубы: ";
	Pp.len = GetCorrectNumber(0,1000000);
	std::cout << "Введите диаметр трубы: ";
	Pp.diameter = GetCorrectNumber(0,500000);
	std::cout << "Труба работает?(y - работает, n - не работает: ";
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
		std::cout << "ID трубы: " << Pp.id << std::endl;
		std::cout << "Длина трубы: " << Pp.len << std::endl;
		std::cout << "Диаметр трубы: " << Pp.diameter << std::endl;
		std::string wrok = Pp.in_work ? "Труба работает" : "Труба не работает";
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
