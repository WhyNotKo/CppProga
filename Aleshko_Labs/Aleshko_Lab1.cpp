// 
// Изменить программу из предыдущей работы:

//1)     добавить работу с несколькими объектами(несколько труб, несколько КС, с возможностью добавления, редактирования, удаления);

//2)     обеспечить уникальную идентификацию объектов;

//3)     поиск объектов по заданному фильтру :

//a)     трубы: по названию, по признаку «в ремонте»;

//b)    КС: по названию, по проценту незадействованных цехов;

//4)     пакетное редактирование труб(т.е.редактирование или всех найденных, или по выбору пользователя)

//UPD: название файлов для сохранения / загрузки задаются пользователем.

//Пакетное редактирование - это отредактировать все элементы во множестве(например, все найденные) или подмножество(пользователь указывает, какие именно).

//Для претендующих на высокий балл : разумное использование ресурсов, грамотная организация кода(убрать излишнее дублирование кода, каждая функция выполняет небольшое, логически законченное действие).Продемонстрировать умение и понимание работы с классами, ссылками, потоками ввода / вывода.
//

#include "pch.h"
#include "Pipe.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <string>


using namespace std;

struct C_stat
{
	string name;
	int all_count;
	int work_count;
	double efficiency;
};

ostream& operator <<(ostream& out, C_stat comp)
{	
	cout << "\nНазвание КС: " << comp.name << " \nКоличество цехов: " << comp.all_count << " \nКоличество работающих цехов: " << comp.work_count << " \nЭффективность: " << comp.efficiency << endl;
}


istream& operator >> (istream& in, C_stat& comp)
{
	
	cout << "Введите название КС" << endl;
	
	cin.ignore();
	getline(cin, comp.name);

	cout << "Введите количество всех цехов КС" << endl;
	comp.all_count = GetCorrectNumber(1,100000000);

	cout << "Введите количество работающих цехов КС" << endl;

	comp.work_count = GetCorrectNumber(1,comp.all_count);

	cout << "Введите эффективность КС (от 1 до 10)" << endl;
	comp.efficiency = GetCorrectNumber(1,10);
}

void save_data(Pipe pipe, C_stat comp)
{
	ofstream fout("basa.txt");
	if (pipe.length) fout << 1 << '\n' << pipe.length << " " << pipe.diameter << " " << pipe.in_work << endl; else fout << 0 << endl;
	if (comp.all_count) fout << 1 << '\n' << comp.name << "\n " << comp.all_count << " " << comp.work_count << " " << comp.efficiency << endl; else fout << 0 << endl;
	fout.close();
	cout << "Данные сохранены." << endl;
}

void load_data(Pipe& pipe, C_stat& comp)
{
	ifstream fin;
	fin.open("basa.txt");
	if (fin.is_open())
	{
		int pcount,cscount;
		fin >> pcount;
		if(pcount) fin >> pipe.length >> pipe.diameter >> pipe.in_work;
		fin >> cscount;
		if (cscount)
		{
			getline(fin, comp.name);
			fin >> comp.all_count >> comp.work_count >> comp.efficiency;
		}
		fin.close();
		cout << "Данные загружены." << endl;
	}
	else
	{
		cout << "Данных для загрузки нет..." << endl;
	}
	fin.close();
}



void change_cs(C_stat& comp)
{
	cout << "Введите количество работающих цехов КС, сейчас " << comp.work_count << " из " << comp.all_count << endl;
	while (true)
	{
		int check = input_int();
		if (check > comp.all_count)
		{
			cout << "Введите меньше цехов, чем их всего..." << endl;
			continue;
		}
		else
		{
			comp.work_count = check;
			break;
		}
	}
	cout_menu();
}

void null(C_stat& comp, Pipe& pipe)
{
	comp.all_count = 0;
	comp.name = '0';
	comp.work_count = 0;
	comp.efficiency = 0;
	pipe.length = 0;
	pipe.diameter = 0;
	pipe.in_work = '0';

}

int main()
{
	setlocale(LC_ALL, "");
	Pipe pipe;	
	C_stat comp;
	null(comp, pipe);
	
	int menu = 8;
	cout_menu();
	while (menu)
	{
		menu = input_menu();
		//if (menu == 0) cout_menu();
		if (menu == 1) cin>>pipe;
		if (menu == 2) cin>>comp;
		if (menu == 3)
		{
			cout << pipe;
			cout << comp;
		}
		if (menu == 4) save_data(pipe, comp);
		if (menu == 5) load_data(pipe, comp);
		if (menu == 6) if (pipe.length) pipe.EditPipe();
		if (menu == 7) if (comp.all_count) change_cs(comp); else cout << "КС не существует" << endl;
	}
	return 0;
}
//template <typename T>