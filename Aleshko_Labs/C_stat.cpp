#include "pch.h"
#include "C_stat.h"
#include"utils.h"

using namespace std;

ostream& operator <<(std::ostream& out, C_stat& comp)
{
	cout << "\n�������� ��: " << comp.name
		<< " \n���������� �����: " << comp.all_count
		<< " \n���������� ���������� �����: " << comp.work_count
		<< " \n�������������: " << comp.efficiency << endl;
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
void C_stat::change_cs()
{
	cout << "������� ���������� ���������� ����� ��, ������ " << work_count << " �� " << all_count << endl;
	while (true)
	{
		work_count = GetCorrectNumber(0,all_count);
	}
	cout_menu();
}