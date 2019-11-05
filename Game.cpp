#include "Game.h"
#include <iostream>
#include <conio.h>
#include <random>

void Game::start()
{
	hasStarted = 0;
	hasEnded = 0;
	setupFields();
	//while (!hasEnded)
	//{
	//	step();
	//}
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
				if (s.length() != 2)
				{
					continue;
				}
				if (s[0] >= 48 && s[0] <= 57)
				{
					if ((s[1] < 65 || s[1] > 74) && (s[1] < 97 || s[1] > 106))
					{
						continue;
					}
					y = s[1] - 65;
					x = s[0] - 48;
				}
				else if ((s[0] >= 65 && s[0] <= 74) || (s[0] >= 97 && s[0] <= 106))
				{
					if (s[1] < 48 || s[1] > 57)
					{
						continue;
					}
					y = s[0] - 65;
					x = s[1] - 48;
				}
				if (y > 9) y -= 32;
				correctData = true;
			} while (cout << "Enter correct coordinates:" << endl, !correctData);
			
		} while (cout << "Ships cannot overlap and touch each other!" << endl,
			!myField.AddShip(new Ship(Point(x, y), listOfShips[i], orientation)));
	}
	draw();
	cout << "Waiting for another player to finish setting up his ships..." << endl;
	cout << "Priority: " << priority << endl;
	string tmp;
	connection << to_string(priority);
	connection >> tmp;
	enemyPriority = stoi(tmp);
	cout << "Enemy priority: " << enemyPriority << endl;

}

void Game::step()
{
	draw();
	
}
