#include "pch.h"
#include"C_stat.h"
#include"Pipe.h"

#include<string>
#include<iostream>
#include<unordered_map>


using namespace std;

template <typename T>
T GetCorrectNumber(T min = 0, T max = 10000000)
{
	T x{};
	while ((cin >> x).fail() || x<min || x>max)
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "������� ���������� �����... " << endl;
	}
	return x;
}

bool input_bool()
{
	string str;
	bool err = true;
	while (true)
	{
		cin >> str;
		if ((str[0] != 'y') && (str[0] != 'n')) err = false;

		if (!err)
		{
			cout << "������� ���������� ��������..." << endl;
			err = true;
			continue;
		}
		if (str[0] == 'y') return true;
		else str = "n";
		return false;
	}
}

void cout_menu()
{
	system("cls");
	cout << "\n 1. �������� �����\n 2. �������� ��\n 3. �������� ���� ��������\n 4. ���������\n 5. ���������\n 6. �������� �����\n 7. �������� ��\n 0. �����\n";
}

int input_menu()
{
	while (true)
	{
		int a = GetCorrectNumber(0, 7);
		return a;
	}
}
