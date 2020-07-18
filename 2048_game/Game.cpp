#include "Game.h"
#include "Tiles.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <time.h>
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>
#include <chrono>
#include <thread>

using namespace std;

void Game::drawBoard()
{
	int size = 4;

	system("cls");

	for (int i = 0; i < size; i++)
	{
		cout << "+----+----+----+----+" << endl << "|";

		for (int j = 0; j < size; j++)
		{
			cout << tile[i][j].padding() << "|";
		}
		cout << endl;
	}
	cout << "+----+----+----+----+" << endl << endl;
}

//get a rand num between 0 and 3 then put them as coords and if that element is equal to 0 put a tile, check again if that tile isnt 0, do while?
pair<int, int> Game::addTile(int toggle)
{
	int r1 = rand() % 4;
	int r2 = rand() % 4;

	//todo: ideally check if there is space on the board

	do
	{
		int r1 = rand() % 4;
		int r2 = rand() % 4;

		if (tile[r1][r2].getValue() == 0)
		{
			tile[r1][r2].makeTile(toggle);
			return make_pair(r1, r2); // returns 2 numbers for position of element
		}
	} while (tile[r1][r2].getValue() != 0);

	//this will never happen because the loop above would not have terminated
	return make_pair(-1, -1);
}

void Game::moveLeft() {
	for (int i = 0; i < 4; i++) {
		int lastCombined = -1;

		for (int j = 1; j < 4; j++) {		
			for (int k = j; k > 0; k--) {
				int curVal = tile[i][k].getValue();
				if (curVal == 0) {
					break;
				}

				int adjVal = tile[i][k-1].getValue();

				switch (adjVal) {
				case 0: //empty
					tile[i][k-1].setValue(tile[i][k].getValue());
					tile[i][k].setValue(0);
					break;

				case -1: //mine
					setScore(getScore() - curVal);
					tile[i][k-1].setValue(0);
					tile[i][k].setValue(0);
					break;

				default:  //another value
					if (k - 1 > lastCombined)  {
						if (adjVal == curVal) {
							tile[i][k-1].setValue(curVal + adjVal);
							tile[i][k].setValue(0);
							lastCombined = k - 1;
							setScore(getScore() + tile[i][k - 1].getValue());
						}
						else if (curVal == -1) {
							setScore(getScore() - tile[i][k - 1].getValue());
							tile[i][k-1].setValue(0);
							tile[i][k].setValue(0);
						}
					}
					break;
				}
			}
		}
	}

}

void Game::moveRight() { 
	for (int i = 0; i < 4; i++) {
		int lastCombined = 4;

		for (int j = 3; j >= 0; j--) {
			for (int k = j; k < 3; k++) {
				int curVal = tile[i][k].getValue();
				if (curVal == 0) {
					break;
				}

				int adjVal = tile[i][k + 1].getValue();

				switch (adjVal) {
				case 0: //empty
					tile[i][k + 1].setValue(tile[i][k].getValue());
					tile[i][k].setValue(0);
					break;

				case -1: //mine
					setScore(getScore() - curVal);
					tile[i][k + 1].setValue(0);
					tile[i][k].setValue(0);
					break;

				default:  //another value#
					if (k + 1 < lastCombined) {
						if (adjVal == curVal) {
							tile[i][k + 1].setValue(curVal + adjVal);
							tile[i][k].setValue(0);
							lastCombined = k + 1;
							setScore(getScore() + tile[i][k + 1].getValue());
						}
						else if (curVal == -1) {
							setScore(getScore() - tile[k + 1][j].getValue());
							tile[i][k + 1].setValue(0);
							tile[i][k].setValue(0);
						}
					}
					break;
				}
			}
		}
	}

}

void Game::moveUp() {
	for (int j = 0; j < 4; j++) {
		int lastCombined = -1; // todo: for opposite direction initialise this to 4

		for (int i = 1; i < 4; i++) {

			for (int k = i; k > 0; k--) {
				int curVal = tile[k][j].getValue();
				if (curVal == 0) {
					break;
				}

				int adjVal = tile[k - 1][j].getValue();

				switch (adjVal) {
				case 0: //empty
					tile[k - 1][j].setValue(tile[k][j].getValue());
					tile[k][j].setValue(0);
					break;

				case -1: //mine
					setScore(getScore() - curVal);
					tile[k - 1][j].setValue(0);
					tile[k][j].setValue(0);
					break;

				default:  //another value#
					//todo: to move the other direction this probably needs to be (k + 1 < lastCombined) 
					if (k - 1 > lastCombined) {
						if (adjVal == curVal) {
							tile[k - 1][j].setValue(curVal + adjVal);
							tile[k][j].setValue(0);
							lastCombined = k - 1;
							setScore(getScore() + tile[k - 1][j].getValue());
						}
						else if (curVal == -1) {
							setScore(getScore() - tile[k - 1][j].getValue());
							tile[k - 1][j].setValue(0);
							tile[k][j].setValue(0);
						}
					}
					break;
				}
			}
		}
	}

}

void Game::moveDown() {
	for (int j = 0; j < 4; j++) {
		int lastCombined = 4; // todo: for opposite direction initialise this to 4

		for (int i = 3; i >= 0; i--) {

			for (int k = i; k < 4; k++) {
				int curVal = tile[k][j].getValue();
				if (curVal == 0) {
					break;
				}

				int adjVal = tile[k + 1][j].getValue();

				switch (adjVal) {
				case 0: //empty
					tile[k + 1][j].setValue(tile[k][j].getValue());
					tile[k][j].setValue(0);
					break;

				case -1: //mine
					setScore(getScore() - curVal);
					tile[k + 1][j].setValue(0);
					tile[k][j].setValue(0);
					break;

				default:  //another value#
					//todo: to move the other direction this probably needs to be (k + 1 < lastCombined) 
					if (k + 1 < lastCombined) {
						if (adjVal == curVal) {
							tile[k + 1][j].setValue(curVal + adjVal);
							tile[k][j].setValue(0);
							lastCombined = k + 1;
							setScore(getScore() + tile[k + 1][j].getValue());
						}
						else if (curVal == -1) {
							setScore(getScore() - tile[k + 1][j].getValue());
							tile[k + 1][j].setValue(0);
							tile[k][j].setValue(0);
						}
					}
					break;
				}
			}
		}
	}

}

bool Game::movMenu(char mov)
{

	switch (mov)
	{
		case 'W':
		case 'w':
		{
			moveUp();
			addTile();
			return true;
		}
		
		case 'X':
		case 'x':
		{
			moveDown();
			addTile();
			return true;
		}

		case 'A':
		case 'a':
		{
			moveLeft();
			addTile();
			return true;
		}

		case 'D':
		case 'd':
		{
			moveRight();
			addTile();
			return true;
		}
	}

	return false;
}


pair<int,int> Game::oneDtoTwoD(int i)
{
	int x, y;

	x = i / 4;
	y = i % 4; //4 is num of rows/cols

	return make_pair(x, y);
}

int Game::twoDtoOneD(int i, int j)
{
	int x;

	x = (i * 4) + j; //4 is num of rows

	return x;
}

void Game::save()
{
	string saveFileName;

	cout << "Enter the name under which your score and tile placement shall be saved." << endl;
	cin >> saveFileName;

	string saveFiletxt = saveFileName + ".txt";

	ofstream saveFile(saveFiletxt, ofstream::out | ofstream::trunc);

	if (saveFile) 
	{
		saveFile << "Score:" << getScore() << endl;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (tile[i][j].getValue() != 0)
				{
					stringstream line;
					line << twoDtoOneD(i, j) << ":" << tile[i][j].getValue() << endl;
						
					string lineInput = line.str();
					saveFile << lineInput; 
				}
			}
		}
		saveFile.close();
	}
	else {
		cout << "Error saving to " + saveFiletxt;
	}
}

void Game::load()
{
	string fileName;
	string saveFileTxt, txtLine, oneDposn, value, score;
	ifstream readFile;
	int oneDposnInt, valueInt, scoreInt;

	cout << "Enter file name of saved game: " << endl;
	cin >> fileName;

	saveFileTxt = fileName + ".txt";

	readFile.open(saveFileTxt);

	if (!readFile)
	{
		cout << "--ERROR-- File does not exist or is invalid. Now returning to previous game." << endl;
		chrono::milliseconds timespan(2000); //to display hall for 5 seconds then resumes
		this_thread::sleep_for(timespan);
		//hopefully this goes back to before load was called
	}
	else
	{
		getline(readFile, txtLine);
		size_t found0 = txtLine.find("Score:");
		score = txtLine.substr(found0 + 6, txtLine.length());
		scoreInt = stoi(score);
		setScore(scoreInt);

		while (getline(readFile, txtLine))
		{

			size_t found = txtLine.find(':');
			oneDposn = txtLine.substr(0, found);
			value = txtLine.substr(found + 1, txtLine.length());

			valueInt = stoi(value);

			oneDposnInt = stoi(oneDposn);
			pair<int, int> posn = oneDtoTwoD(oneDposnInt);
			int row = posn.first;
			int col = posn.second;
			
			tile[row][col].setValue(valueInt);
			
		}
	}
}

void Game::newGame()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tile[i][j].setValue(0);
		}
	}

	setScore(0);
}

int Game::checkEndGame()
{
	int counter = 0;

	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				int curVal = tile[i][j].getValue();

				if (curVal == 2048)
				{
					counter++;
				}
				
			}
		}
	}

	if (counter >= 1) { return 3; }
	else if (checkNegative() && checkPositve() == true)
	{
		return 5;
	}
	else
		return 1;
	
	
	return 1;
}

bool Game::checkPositve()
{
	if (fullBoard() == true)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				int curVal = tile[i][j].getValue();
				int downVal = tile[i + 1][j].getValue();
				int rightVal = tile[i][j + 1].getValue();

				if ((curVal != downVal) || (curVal != rightVal) || curVal != 0 || (curVal != -1)) { return true; }
			}
		}
	}
	return false;
}

bool Game::checkNegative() //negative corresponds to the fact that the index is i-1 or j-1
{
	if (fullBoard() == true)
	{
		for (int i = 3; i > 0; i--)
		{
			for (int j = 3; j > 0; j--)
			{
				int curVal = tile[i][j].getValue();
				int upVal = tile[i - 1][j].getValue();
				int leftVal = tile[i][j - 1].getValue();

				if (curVal != upVal || curVal != leftVal || curVal != 0 || curVal != -1) { return true; }
			}
		}
	}
	return false;
}

bool Game::fullBoard()
{
	int counter = 0;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (tile[i][j].getValue() > 0)
			{
				counter++;
			}
		}
	}
	if (counter == 16) { return true; }
	else { return false; }
}


