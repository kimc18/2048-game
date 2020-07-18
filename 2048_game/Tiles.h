#pragma once

#include <string>

using namespace std;

class Tiles
{
private:
	
	int m_value;

public:

	Tiles() : m_value(0){}

	//getter and setter
	int getValue() { return m_value; }
	void setValue(int val) { m_value = val; }

	//tile functions
	string padding();
	int makeTile(int toggle = 1);
};

