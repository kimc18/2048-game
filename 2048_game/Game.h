#pragma once
#include <queue>

#include "Tiles.h"

using namespace std;

class Game : public Tiles
{
private:
	int m_score;

	Tiles tile[4][4];

public:
	Game() : m_score(0){}

	//getter and setters
	int getScore() { return m_score; }
	void setScore(int s) { m_score = s; }

	//board functions
	void drawBoard();
	pair<int, int> addTile(int toggle = 1);
	
	//menus
	bool movMenu(char mov);

	//Move functions
	void moveLeft();
	void moveUp();
	void moveRight();
	void moveDown();

	//changing index formats for saving and loading
	pair<int,int> oneDtoTwoD(int i);
	int twoDtoOneD(int i, int j);

	//Additional Commands
	void save();
	void load();
	void newGame();

	//lose or win
	int checkEndGame();
	bool fullBoard();
	bool checkPositve();
	bool checkNegative();
};

