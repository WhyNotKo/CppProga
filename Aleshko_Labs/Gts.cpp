#include "pch.h"
#include "Gts.h"

using namespace std;

void Gts::setWeb(tuple <int, Pipe> pipe, int cs1, int cs2)
{
	idpp = get<int>(pipe);
	id1cs = cs1;
	id2cs = cs2;
	auto pp = get<Pipe>(pipe);
	piped = pp.GetPipeDiam();
}