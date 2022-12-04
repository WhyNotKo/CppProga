#include "pch.h"
#include "Network.h"


using namespace std;
void Network::create_link(int pipe, int cs1, int cs2)
{
	Pipeid = pipe;
	stationsid = {cs1,cs2};
}

pair<int,int> Network::get_stations()
{
	return stationsid;
}

int Network:: webPipeid()
{
	return Pipeid;
}

ifstream& operator >> (ifstream& fin, Network& nw)
{
	fin >> nw.Pipeid
		>> nw.stationsid.first
		>> nw.stationsid.second;
	return fin;
}

ostream& operator << (ostream& out, const Network& nw)
{
	cout << "КС начала (id: " << nw.stationsid.first << ") ->  "
		<< "Труба (id: " << nw.Pipeid << ") ->  "
		<< "КС конца (id: " << nw.stationsid.second << ")" << endl;
	return out;
}

ofstream& operator << (ofstream& fout, const Network& nw)
{
	fout << nw.Pipeid << " "
		<< nw.stationsid.first << " "
		<< nw.stationsid.second << std::endl;
	return fout;
}
