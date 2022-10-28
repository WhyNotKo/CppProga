//#include "Pipe.h"
//#include "utils.h"
#include "pch.h"




#include "Pipe.h"
#include "utils.h"


//int Pipe::MaxID;

//void Pipe::MaxIDincr()
//{
//	MaxID++;
//}


std::istream& operator >> (std::istream& in, Pipe& Pp) {
	std::cout << "������� ����� �����: ";
	Pp.len = GetCorrectNumber(0,1000000);
	std::cout << "������� ������� �����: ";
	Pp.diameter = GetCorrectNumber(0,500000);
	std::cout << "����� ��������?(y - ��������, n - �� ��������: ";
	Pp.in_work = input_bool();
	return in;
}



std::ostream& operator << (std::ostream& out, const Pipe& Pp) {
	if (!(Pp.len == 0)) {
		std::cout << "����� �����: " << Pp.len << std::endl;
		std::cout << "������� �����: " << Pp.diameter << std::endl;
		std::string wrok = Pp.in_work ? "����� ��������" : "����� �� ��������";
		std::cout << wrok << std::endl << std::endl;
	}
	return out;
}
void Pipe::EditPipe()
{
	cout << in_work << endl;
	in_work = !in_work;
	cout << in_work << endl;
}
