#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
class Pipe
{
	int id;

public:
	static int MaxPipeID;
	int length;
	int diameter;
	string in_work;


	int GetId() const;
	void SetId();


	void EditPipe();
	friend istream& operator >> (istream& in, Pipe& p);
	friend ostream& operator << (ostream& out, const Pipe& p);
	friend ifstream& operator >> (ifstream& in, Pipe& p);
	friend ofstream& operator << (ofstream& out, const Pipe& p);
};

