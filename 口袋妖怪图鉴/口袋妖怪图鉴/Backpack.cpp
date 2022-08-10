#include "Backpack.h"

Monster::Monster(string n)
{
	name = n;
	srand((unsigned)time(0));
	level = rand() % 20;
}

Monster::Monster()
{
	srand((unsigned)time(0));
	level = rand() % 20;
}

Monster::Monster(string n, string x)
{
	name = n, feature = x;
	level = rand() % 20 + 1;
	condition = 'N';
}
