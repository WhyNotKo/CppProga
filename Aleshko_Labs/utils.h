#pragma once
#include <iostream>
#include <string>
#include <tuple>

using namespace std;

template <typename T>
T GetCorrectNumber(T min = 0, T max = 10000000)
{
	T x;
	while (( cin >> x).fail() || x<min || x>max)
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Введите корректное число... ";
	}
	return x;
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
		if (str[0] == 'y') str = "y";
		else str = "n";
		return str;
	}
}

void cout_menu()
{
	system("cls");
	cout << "\n 1. Добавить трубу\n 2. Добавить КС\n 3. Просмотр всех объектов\n 4. Сохранить\n 5. Загрузить\n 6. Изменить трубу\n 7. Изменить КС\n 0. Выход\n";
}
int input_menu()
{
	while (true)
	{
		int a = GetCorrectNumber(0, 7);
		return a;
	}
}
