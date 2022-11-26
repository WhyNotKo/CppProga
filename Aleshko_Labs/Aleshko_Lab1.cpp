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
#include "Gts.h"

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>


using namespace std;

int MPID = 1;
int MCID = 1;

int main()
{
	setlocale(LC_ALL, "");


	unordered_map<int, Pipe> Pipes;
	unordered_map<int, C_stat> Stations;
	unordered_map<int, Gts> webs;
	int menu = 0;
	while (true)
	{
		cout_menu();
		menu = input_menu(); 

		if (!menu)
		{
			cout << "СкОлЬкО вОлкО ОгуРцОм нЕ кОрмИ, оН не сТанЕт кОзОй в ТаЗике!\n";
			break;
		}

		if (menu == 1) 
		{
			Pipe pipe;
			cin >> pipe;
			pipe.setID(MPID);
			//pipe.id = MPID;
			Pipes.emplace(MPID, pipe);
			MPID++;
		}
		if (menu == 2)
		{
			C_stat comp;
			cin >> comp;
			comp.id = MCID;
			Stations.emplace(comp.id, comp);
			MCID++;
		}
		if (menu == 3)
		{
			if(Pipes.size())
			{
				cout << "Трубы\n" << endl;
				for (auto& p : Pipes) cout << p.second << endl;
			}
			else cout << "Труб нет\n" << endl;
			if(Stations.size())
			{
				cout << "Компрессорки" << endl;
				for (auto& c : Stations) cout << c.second << endl;
			}
			else cout << "Компрессорок нет\n" ;
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
			CSmenu(Stations);
		}
		if (menu == 8)
		{
			GtsMenu(Pipes, Stations, MPID, MCID);
		}
	}
	return 0;
}
