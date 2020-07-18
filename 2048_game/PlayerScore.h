#pragma once

#include <string>

using namespace std;

class PlayerScore 
{
public:
	string m_name;
	int m_score;

	PlayerScore(string name, int score) : m_name(name), m_score(score){}

	string getPlayerName() { return m_name; }
	int getPlayerScore() { return m_score; }
	void setPlayerName(string name) { m_name = name; }
	void setPlayerScore(int score) { m_score = score; }

	bool operator< (const PlayerScore& ps) const { return m_score < ps.m_score; }
};

