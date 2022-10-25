#include "Pipe.h"
#include "utils.h"

using namespace std;

int Pipe::MaxPipeID = 0;


int Pipe::GetId() const
{
	return id;
}

void Pipe::SetId()
{
	id = ++MaxPipeID;
}

istream& operator >> (istream& in, Pipe& p)
{
	p.SetId();
	cout << "������� �������: ";
	p.diameter = GetCorrectNumber(1, 10000000);
	cout << "������� �����: ";
	p.length = GetCorrectNumber(1, 10000000);
	cout << "����� ��������? (y - �������� ,�  n - �� ��������) ";
	p.in_work = input_bool();
	return in;
}

ostream& operator << (ostream& out, const Pipe& p)
{
	if (p.diameter != 0)
	{
		out << "Pipe's identificator: " << p.id << "\n����� �����: " << p.length << " ��\n������� �����: " << p.diameter << endl;
		if (p.in_work == "n")
		{
			out << "����� �� ��������!" << endl;
		}
		if (p.in_work == "y")
		{
			out << "����� ��������!" << endl;
		}
	}
	return out;
}

ifstream& operator >> (ifstream& in, Pipe& p)
{
	in >> p.id;
	in >> p.diameter;
	in >> p.length;
	in >> p.in_work;
	return in;
}

ofstream& operator << (ofstream& out, const Pipe& p)
{
	out << p.GetId() << endl
		<< p.diameter << endl
		<< p.length << endl
		<< p.in_work << endl;
	return out;
}

void Pipe::EditPipe()
{
	if (in_work == "y") in_work = "n";
	else in_work = "y";
}
