#include "HallOfFame.h"
#include "Game.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void HallOfFame::saveHallofFame(int score)
{
	string HallOfFametxt, name;

	HallOfFametxt = "HallOfFame.txt";

	ofstream saveFile(HallOfFametxt, ofstream::out | ofstream::app);

	cout << endl;
	cout << "Please enter your name so that is can be placed in the Hall of Fame." << endl;

	getline(cin >> ws, name);

	string name_colon = name + ":";

	saveFile << name_colon << score << endl;
	saveFile.close();
}

void HallOfFame::displayHall()
{
	string HallOfFametxt = "HallOfFame.txt";
	string scoreLine, score, name;
	int scoreInt, counter = 0;

	priority_queue<PlayerScore> scores;

	ifstream readFile;
	readFile.open(HallOfFametxt);
	if (readFile)
	{
		while (getline(readFile, scoreLine))
		{
			size_t found = scoreLine.find(':');
			name = scoreLine.substr(0, found + 1);
			score = scoreLine.substr(found + 1, scoreLine.length());

			scoreInt = stoi(score);
			setPlayerScore(scoreInt);
			setPlayerName(name);

			scores.push(PlayerScore(getPlayerName(), getPlayerScore()));

			counter++; //counter used to see how many times this loop was used to output the ordered hall of fame
		}
	}

	for (int i = 0; i < counter; i++)
	{
		cout << scores.top().m_name << scores.top().m_score << endl; //m_score and m_name were put public so that they can be used here
		scores.pop();
	}
}