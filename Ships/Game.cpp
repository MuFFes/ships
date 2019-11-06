#include "Game.h"
#include <iostream>
#include <conio.h>
#include <random>
#include "Exception.h"

void Game::start()
{
	hasStarted = 0;
	hasEnded = 0;
	//setupFields();
	cout << "Priority: " << priority << endl;
	string tmp;
	connection << to_string(priority);
	connection >> tmp;
	enemyPriority = stoi(tmp);
	cout << "Enemy priority: " << enemyPriority << endl;
	while (true)
	{
		draw();
		step();
	}
	cout << endl << "END";
	_getch();
}

bool Game::validateCoordinatesInput(string coordinates)
{
	if (coordinates.length() != 2)
	{
		return false;
	}
	if (coordinates[0] >= 48 && coordinates[0] <= 57)
	{
		if ((coordinates[1] < 65 || coordinates[1] > 74) && (coordinates[1] < 97 || coordinates[1] > 106))
		{
			return false;
		}
	}
	else if ((coordinates[0] >= 65 && coordinates[0] <= 74) || (coordinates[0] >= 97 && coordinates[0] <= 106))
	{
		if (coordinates[1] < 48 || coordinates[1] > 57)
		{
			return false;
		}
	}
	return true;
}

void Game::standarizeCoordinatesInput(int *x, int *y)
{
	if (*y < *x)
	{
		swap(x, y);
	}
	while (*y > 10) *y -= 16;
	while (*x > 10) *x -= 16;
}

Game::Game(Connection *connection)
{
	this->connection = connection;
	
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, INT_MAX);
	
	this->priority = dis(gen);
	
	start();
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
				correctData = validateCoordinatesInput(s);
			} while (cout << "Enter correct coordinates:" << endl, !correctData);
			x = s[0];
			y = s[1];
			standarizeCoordinatesInput(&x, &y);
			
		} while (cout << "Ships cannot overlap and touch each other!" << endl,
			!myField.AddShip(new Ship(Point(x, y - 1), listOfShips[i], orientation)));
	}
	draw();
	cout << "Waiting for another player to finish setting up his ships..." << endl;
}

void Game::step()
{
	string msg;
	int x;
	int y;
	if (priority > enemyPriority)
	{
		cout << "Choose a tile to shoot on: ";
		bool correctData = false;
		do
		{
			cin >> msg;
			correctData = validateCoordinatesInput(msg);
			if (correctData)
			{
				x = msg[0];
				y = msg[1];
				standarizeCoordinatesInput(&x, &y);
			}
			if (enemyField.GetState(Point(x, y)) != '.')
			{
				correctData = false;
				cout << "This tile had already been shot!" << endl;
			}
		} while (cout << "Enter correct coordinates:" << endl, !correctData);
		connection << to_string(x) + to_string(y);
	}
	else
	{
		cout << "Waiting for your enemy to shoot...";
		connection >> msg;
		if (msg.length() == 2)
		{
			x = msg[0];
			y = msg[1];
			standarizeCoordinatesInput(&x, &y);
			myField.Shoot(Point(x, y));
		}
		else throw Exception("Error receiving data from connection!");
	}
	
	draw();
}
