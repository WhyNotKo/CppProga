#include "pch.h"
#include "C_stat.h"
#include"utils.h"

using namespace std;

ostream& operator <<(std::ostream& out, C_stat& comp)
{
	cout << "\nНазвание КС: " << comp.name
		<< " \nКоличество цехов: " << comp.all_count
		<< " \nКоличество работающих цехов: " << comp.work_count
		<< " \nЭффективность: " << comp.efficiency << endl;
	return out;
}

istream& operator >> (std::istream& in, C_stat& comp)
{

	cout << "Введите название КС" << endl;

	cin.ignore();
	getline(cin, comp.name);

	cout << "Введите количество всех цехов КС" << endl;
	comp.all_count = GetCorrectNumber(1, 100000000);

	cout << "Введите количество работающих цехов КС" << endl;

	comp.work_count = GetCorrectNumber(1, comp.all_count);

	cout << "Введите эффективность КС (от 1 до 10)" << endl;
	comp.efficiency = GetCorrectNumber(1, 10);
	return in;
}
void C_stat::change_cs()
{
	cout << "Введите количество работающих цехов КС, сейчас " << work_count << " из " << all_count << endl;
	while (true)
	{
		work_count = GetCorrectNumber(0,all_count);
	}
	cout_menu();
}