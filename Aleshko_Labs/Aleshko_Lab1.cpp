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
#include <iostream>
#include <fstream>
#include <string>


using namespace std;

struct Pipe
{

	int length;
	int diameter;
	string in_work;
	
};

struct C_stat
{
	string name;
	int all_count;
	int work_count;
	double efficiency;
};

void cout_menu()
{
	system("cls");
	cout << "\n 1. Добавить трубу\n 2. Добавить КС\n 3. Просмотр всех объектов\n 4. Сохранить\n 5. Загрузить\n 6. Изменить трубу\n 7. Изменить КС\n 0. Выход\n";
}

string input_bool()
{
	string str;
	bool err = true;
	while (true)
	{
		cin >> str;
		if ((str[0] != 'y') && (str[0] != 'n')) err = false;

		if (!err)
		{
			cout << "Введите корректное значение..." << endl;
			err = true;
			continue;
		}
		if (str[0] == 'y') str = "Работает";
		else str = "Ремонтируется";
		return str;
	}
}

int input_int()
{
	/*string str;
	bool err = true;
	while (true)
	{
		cin >> str;
		for (int i = 0; i < str.length();++i)
		{
			if (!isdigit(str[i]))
			{
				err = false;
				break;
			}
		}

		if ((!err) or (stoi(str) == 0))
		{
			cout << "Введите корректное число..." << endl;
			err = true;
			cin.clear();
		}
		else return stoi(str);
	}*/
	while (true)
	{
		int a;
		cin >> a;
		if (cin.fail())
		{
			cout << "Введите корректное число..." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
		}
		else return a;
	}
}

int input_menu()
{
	//string str;
	//while (true)
	//{
	//	
	//	cin >> str;
	//	bool err = true;
	//	for (int i = 0; i < str.length(); i++)
	//	{
	//		if ((str.length()!=1) or (str[0]-48>7))
	//		{
	//			err = false;
	//			break;
	//		}
	//	}

	//	if (!err)
	//	{
	//		cout << "Введите корректное число..." << endl;
	//		!err;
	//		cin.clear();
	//		continue;
	//	}
	//	/*else return str[0]-48;*/
	//	else return stoi(str); //
	//}
	while (true)
	{
		int a = input_int();
		if (a<0 or a>7)
		{
			cout << "Введите корректное число..." << endl;
			a = input_int();
		}
		else return a;
	}
	
}

void cout_obj(Pipe pipe, C_stat comp)
{
	system("cls");
	if (pipe.length) cout << "Длина трубы: " << pipe.length << " км\nДиаметр трубы: " << pipe.diameter << " мм\nСостояние: " << pipe.in_work << "\n" << endl;
	else cout << "Труб нет! \n" << endl;
	
	if (comp.all_count) cout << "\nНазвание КС: " << comp.name << " \nКоличество цехов: " << comp.all_count << " \nКоличество работающих цехов: " << comp.work_count << " \nЭффективность: " << comp.efficiency << endl;
	else cout << "Компрессорки нет!" << endl;
	cout << "\n 1. Добавить трубу\n 2. Добавить КС\n 3. Просмотр всех объектов\n 4. Сохранить\n 5. Загрузить\n 6. Изменить трубу\n 7. Изменить КС\n 0. Выход\n";
	//cout << "Нажмите 0, чтобы выйти в меню" << endl;
}

void input_pipe(Pipe& pipe)
{
	system("cls");
	cout << "Введите длину трубы" << endl;
	pipe.length = input_int();

	cout << "Введите диаметр трубы" << endl;
	pipe.diameter = input_int();

	cout << "Введите состояние трубы(y/n) (у если работает, n если в ремонте)" << endl;
	pipe.in_work = input_bool();
	cout_menu();
}
int minmax(int a)
{
	int b = input_int();
	if (a >= b) return b;
	else
	{
		cout << "Введите число меньше!" << endl;
		minmax(a);
	}
}

void input_cp(C_stat& comp)
{
	system("cls");
	//int check;
	cout << "Введите название КС" << endl;
	
	cin.ignore();
	getline(cin, comp.name);

	cout << "Введите количество всех цехов КС" << endl;
	comp.all_count = input_int();

	cout << "Введите количество работающих цехов КС" << endl;

	comp.work_count = minmax(comp.all_count);

	cout << "Введите эффективность КС (от 1 до 10)" << endl;
	comp.efficiency = minmax(10);
	cout_menu();
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

void change_pipe(Pipe& pipe)
{
	cout << "Введите состояние трубы(y/n) (у если работает, n если в ремонте)" << endl;
	pipe.in_work = input_bool();
	cout_menu();
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
		if (menu == 1) if (!pipe.length) input_pipe(pipe); else cout << "Труба уже существует" << endl;
		if (menu == 2) if (!comp.all_count) input_cp(comp); else cout << "КС уже существует" << endl;
		if (menu == 3) cout_obj(pipe, comp);
		if (menu == 4) save_data(pipe, comp);
		if (menu == 5) load_data(pipe, comp);
		if (menu == 6) if (pipe.length) change_pipe(pipe); else cout << "Труба не существует" << endl;
		if (menu == 7) if (comp.all_count) change_cs(comp); else cout << "КС не существует" << endl;
	}
	return 0;
}
//template <typename T>