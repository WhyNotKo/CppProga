#pragma once
#include "pch.h"
#include"Pipe.h"
#include"C_stat.h"

#include<unordered_set>
#include <tuple>

class Gts
{
private:
	int id1cs = 0, id2cs = 0, idpp = 0, piped = 0;
public:
	void setWeb(std::tuple <int, Pipe> pipe,int cs1, int cs2);


};

