#include "Tiles.h"

#include <string>
#include <time.h>


//case statement, checks if num is between 1 and 9 then add three spaces before, check if it is between 10 and 99 add 2 spaces etc.
//use getValue
string Tiles::padding()
{
	if (getValue() == 0)
	{
		string str = "    ";
		return str;
	}
	else if (getValue() > 0 && getValue() < 10)
	{
		string s_getValue = to_string(getValue());
		string str = "   " + s_getValue;
		return str;
	}
	else if (getValue() > 9 && getValue() < 100)
	{
		string s_getValue = to_string(getValue());
		string str = "  " + s_getValue;
		return str;
	}
	else if (getValue() > 99 && getValue() < 1000)
	{
		string s_getValue = to_string(getValue());
		string str = " " + s_getValue;
		return str;
	}
	else if (getValue() > 999 && getValue() < 10000)
	{
		string s_getValue = to_string(getValue());
		string str = s_getValue;
		return str;
	}
	else if (getValue() == -1) //-1 is used to represent mine tile
	{
		string mine_tile = "*";
		string s_mine = "   " + mine_tile;
		return s_mine;
	}
}

int Tiles::makeTile(int toggle)
{
	int val1 = 2;
	int val2 = 4;
	int val3 = -1; //used to represent mine tile

	int prob_val3 = 20;

	int r = rand() % 100 + 1; //range is 1 till 100
	if (toggle == 1)
	{
		if (r > 20 && r <= 60) // 40%, this is so it doesn't clash with prob below
		{
			setValue(val1);
			return getValue();
		}
		else if (r <= prob_val3)
		{
			setValue(val3);
			return getValue();
		}
		else
		{
			setValue(val2);
			return getValue();
		}
	}

	if (toggle == 0)
	{
		if (r < 50) //there is 50 50 chance of either
		{
			setValue(val1);
			return getValue();
		}
		else
		{
			setValue(val2);
			return getValue();
		}
	}
}
