#include "Game.h"
#include <iostream>
#include <conio.h>
#include <random>
#include "Exception.h"
#include "GameHelper.h"

void Game::Start()
{
	setupFields();
	
	string tmp;
	connection << to_string(priority);
	connection >> tmp;
	enemyPriority = stoi(tmp);

	draw();
	while (true)
	{
		step();
	}
	cout << endl << "END";
	_getch();
}

Game::Game(Connection *connection)
{
	this->connection = connection;
	
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, INT_MAX);
	
	this->priority = dis(gen);
}

void Game::draw()
{
	system("cls");
	cout << endl << "\t     Your field: \t\t\t      Enemy field:" << endl << "\t";
	for (int i = 0; i < 10; i++)
	{
		cout << " " << i;
	}
	cout << "\t\t\t ";
	for (int i = 0; i < 10; i++)
	{
		cout << " " << i;
	};;
	cout << endl << "       |--------------------\t\t\t|--------------------";
	for (int i = 1; i <= 10; i++)
	{
		cout << endl << "     " << (char)(i + 64) << " | ";
		for (int j = 0; j < 10; j++)
		{
			cout << myField.GetState(Point(j, i - 1)) << " ";
		}
		cout << "\t\t" << "      " << (char)(i + 64) << " | ";
		for (int j = 0; j < 10; j++)
		{
			cout << enemyField.GetState(Point(j, i - 1)) << " ";
		}
	}
	cout << endl << endl;
}

Game::~Game()
{
	connection->Close();
}

void Game::setupFields()
{
	const int numOfShips = sizeof(listOfShips) / sizeof(listOfShips[0]);
	for (int i = 0; i < numOfShips; i++)
	{
		draw();

		int x = 0;
		int y = 0;
		int orientation = 0;

		do
		{
			if (listOfShips[i] > 1)
			{
				cout << "Choose orientation of " << listOfShips[i] << "-tiled ship (h-horizontal, v-vertical): ";
				char c = _getch();
				while (c != 'h' && c != 'H' && c != 'v' && c != 'V')
				{
					c = _getch();
				}
				cout << c << endl;
				if (c == 'h' || c == 'H')
					orientation = 0;
				else
					orientation = 1;
			}

			cout << "Select first tile to place " << listOfShips[i] << "-tiled ship on: ";
			string s;
			bool correctData = false;
			do
			{
				cin >> s;
				correctData = GameHelper::ValidateCoordinatesInput(s);
			} while (cout << "Enter correct coordinates:" << endl, !correctData);
			x = s[0];
			y = s[1];
			GameHelper::StandardizeCoordinatesInput(&x, &y);
			
		} while (cout << "Ships cannot overlap and touch each other!" << endl,
			!myField.AddShip(new Ship(Point(x, y), listOfShips[i], orientation)));
	}
	draw();
	cout << "Waiting for another player to finish setting up his ships..." << endl;
}

void Game::step()
{
	if (priority > enemyPriority)
	{
		shoot();
		draw();
		waitForShot();
	}
	else if (priority < enemyPriority)
	{
		waitForShot();
		draw();
		shoot();
	}
	else throw Exception("Wrong seed value. Please restart your game.");
	draw();
}


void Game::shoot()
{
	string msg;
	int x = -1;
	int y = -1;

	cout << "Choose a tile to shoot on: ";
	bool correctData = false;
	do
	{
		cin >> msg;
		correctData = GameHelper::ValidateCoordinatesInput(msg);
		if (correctData)
		{
			x = msg[0];
			y = msg[1];
			GameHelper::StandardizeCoordinatesInput(&x, &y);
		}
		if (enemyField.GetState(Point(x, y)) != '.')
		{
			correctData = false;
			cout << "This tile had already been shot!" << endl;
		}
	} while (cout << "Enter correct coordinates:" << endl, !correctData);
	connection << to_string(x) + to_string(y);
	string state;
	connection >> state;
	enemyField.Shoot(Point(x, y), state);
}

void Game::waitForShot()
{
	string msg;

	cout << "Waiting for your enemy to shoot...";
	connection >> msg;
	if (msg.length() == 2)
	{
		int x = msg[0] - 48;
		int y = msg[1] - 48;
		myField.Shoot(Point(x, y));
		Ship* s = myField.FindShip(Point(x, y));
		string state = "o";
		if (s != nullptr)
		{
			if (myField.GetNumberOfShipRemainingTiles(s) == 0)
				state = "D";
			else state = "*";
		}
		connection << state;
	}
	else throw Exception("Error receiving data from connection!");
}