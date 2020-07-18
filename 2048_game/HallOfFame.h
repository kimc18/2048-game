#pragma once

#include "Game.h"
#include "PlayerScore.h"

class HallOfFame : public Game, PlayerScore
{
public:
	HallOfFame() : Game(), PlayerScore(" ", 0){}
	void saveHallofFame(int score);
	void displayHall();
};

