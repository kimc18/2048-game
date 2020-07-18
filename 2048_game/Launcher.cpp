#include "Game.h"
#include "Tiles.h"
#include "HallOfFame.h"

#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <chrono>
#include <thread>

void displayOptions();

using namespace std;

int main()
{
	Game game;
	HallOfFame hall;
	char option, newGame, loadGame, quit;

	srand((unsigned int) time(NULL)); //for add tile function

	game.addTile(0);
	game.addTile(0);

	while (1)
	{
		game.drawBoard();
		cout << endl;
		cout << "Score: " << game.getScore() << endl << endl;
		displayOptions();
		cout << "Enter a letter: ";
		cin >> option;

		switch (option)
		{
		case 'w':
		case 'W':
		case 'x':
		case 'X':
		case 'a':
		case 'A':
		case 'd':
		case 'D':
			game.movMenu(option);
			break;

		case 'n':
		case 'N':
			cout << "Are you sure you want to start a new game? (y/n)" << endl;
			cin >> newGame;
			if (newGame == 'Y' || newGame == 'y')
			{
				game.newGame();
			}
			break;

		case 's':
		case 'S':
			game.save();
			break;

		case 'l':
		case 'L':
			cout << "Are you sure you want to load a game? (y/n)" << endl;
			cin >> loadGame;
			if (loadGame == 'Y' || loadGame == 'y')
			{
				game.newGame();
				game.load();
			}
			break;

		case 'h':
		case 'H':
			hall.displayHall();
			game.movMenu(option);
			cout << "Please wait, your game will resume shortly." << endl;
			chrono::milliseconds timespan(5000); //to display hall for 5 seconds then resumes
			this_thread::sleep_for(timespan);
			break;

		case 'q':
		case 'Q':
			cout << "Are you sure you want to quit? (y/n)" << endl;
			cin >> quit;
			if (quit == 'Y' || quit == 'y')
			{
				exit(0);
			}
			break;

		default:
			if (!game.movMenu(option)) {
				cout << "--INVALID INPUT--" << endl << "Please enter a valid character." << endl;
				chrono::milliseconds timespan(2000); //to display hall for 5 seconds then resumes
				this_thread::sleep_for(timespan);
			}
		}

		switch (game.checkEndGame())
		{
		case 3:
			game.drawBoard();
			cout << endl;
			cout << "Score: " << game.getScore() << endl << endl;
			cout << "--CONGRATULATIONS-- You won!" << endl << endl;
			hall.displayHall();
			hall.saveHallofFame(game.getScore());
			hall.displayHall();
			exit(0);

		case 5:
			game.drawBoard();
			cout << endl;
			cout << "Score: " << game.getScore() << endl << endl;
			cout << "Wow... how did you manage to lose such a simple game..." << endl;
			cout << "Anyways, here is a list of people that actually made it to the end!" << endl << endl;
			hall.displayHall();
			exit(0);

		case 1:
			break;
		}
	}
}

void displayOptions()
{
	cout << "W or w --- Slide Up" << "        " << "N or n --- Start new game" << endl;
	cout << "X or x --- Slide Down" << "      " << "S or s --- Save game" << endl;
	cout << "A or a --- Slide Left" << "      " << "L or l --- Load game" << endl;
	cout << "D or d --- Slide Right" << "     " << "H or h --- Display Hall of Fame" << endl<<endl;
	cout << "                  Q or q --- Quit" << endl;
}