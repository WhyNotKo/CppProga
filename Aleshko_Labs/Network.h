#pragma once
#include<tuple>
#include<iostream>
#include<fstream>
class Network
{
private:
	int Pipeid = 0;
	std::pair <int, int> stationsid {0,0};
public:
	
	void create_link(int pipe, int cs1, int cs2);

	std::pair<int,int> get_stations();

	int webPipeid();

	friend std::ifstream& operator >> (std::ifstream& fin, Network& nw);

	friend std::ostream& operator << (std::ostream& out, const Network& nw);

	friend std::ofstream& operator << (std::ofstream& fout, const Network& nw);

};

