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
#include "C_stat.h"

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>


using namespace std;

int MPID = 0;
int MCID = 0;

int main()
{
	setlocale(LC_ALL, "");
	Pipe pipe;
	C_stat comp;

	unordered_map<int, Pipe> Pipes;
	unordered_map<int, C_stat> Stations;
	
	int menu = 8;
	while (menu)
	{

		cout_menu();
		menu = input_menu();

		if (menu == 1) 
		{
			cin >> pipe;
			pipe.id = MPID;
			Pipes.emplace(MPID, pipe);
			MPID++;
		}
		if (menu == 2)
		{
			cin >> comp;
			comp.id = MCID;
			Stations.emplace(comp.id, comp);
			MCID++;
		}
		if (menu == 3)
		{

			cout << "Трубы\n" << endl;
			for ( auto &p:Pipes) cout << p.second << endl;
			cout <<"Компрессорки" << endl;
			for (auto& c : Stations) cout << c.second << endl;
		}
		string name;
		if (menu == 4) 
		{
			cout << "Введите имя файла: ";
			cin.ignore();
			getline(cin, name);
			save_data(name, Pipes, Stations);
		}
		if (menu == 5) 
		{
			cout << "Введите имя файла: ";
			cin.ignore();
			getline(cin, name);
			load_data(name, MPID, MCID, Pipes, Stations);
		}
		if (menu == 6)
		{
			Pipemenu(Pipes);
		}
		if (menu == 7) 
		{
			comp.change_cs();
			Stations[comp.id] = comp;
		}
	}
	return 0;
}
