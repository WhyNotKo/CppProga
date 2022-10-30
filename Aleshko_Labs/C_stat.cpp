#include "pch.h"
#include "C_stat.h"
#include"utils.h"

//using namespace std;

std::ostream& operator <<(std::ostream& out,const C_stat& comp)
{
	std::cout << "\nID ��: " << comp.id;
	std::cout << "\n�������� ��: " << comp.name
		<< " \n���������� �����: " << comp.all_count
		<< " \n���������� ���������� �����: " << comp.work_count
		<< " \n�������������: " << comp.efficiency << std::endl;
	return out;
}

istream& operator >> (std::istream& in, C_stat& comp)
{

	cout << "������� �������� ��" << endl;

	cin.ignore();
	getline(cin, comp.name);

	cout << "������� ���������� ���� ����� ��" << endl;
	comp.all_count = GetCorrectNumber(1, 100000000);

	cout << "������� ���������� ���������� ����� ��" << endl;

	comp.work_count = GetCorrectNumber(1, comp.all_count);

	cout << "������� ������������� �� (�� 1 �� 10)" << endl;
	comp.efficiency = GetCorrectNumber(1, 10);

	return in;
}

std::ofstream& operator <<(std::ofstream& fout, const C_stat& comp)
{
	fout << comp.name << std::endl
		<< comp.all_count << " "
		<< comp.work_count << " "
		<< comp.efficiency << std::endl;
	return fout;
}

std::ifstream& operator >> (std::ifstream& fin, C_stat& comp)
{
	fin.ignore();
	std::getline(fin,comp.name);
	fin	>> comp.all_count
		>> comp.work_count
		>> comp.efficiency;
	return fin;
}

void C_stat::change_cs()
{
	cout << "������� ���������� ���������� ����� ��, ������ " << work_count << " �� " << all_count << endl;
	work_count = GetCorrectNumber(0, all_count);
}

double C_stat::eff_cs()
{
	return (1.0 * work_count) / (all_count * 1.0);
}
string C_stat::getname()
{
	return name;
}
