#include "Game.h"
#include <iostream>
#include <conio.h>

void Game::start()
{
	hasStarted = 0;
	hasEnded = 0;
	clearFields();
	setupFields();
	//while (!hasEnded)
	//{
	//	step();
	//}
}

Game::Game(ServerConnection *connection)
{
	this->connection = connection;
	isServer = true;
	start();
}

Game::Game(ClientConnection *connection)
{
	this->connection = connection;
	isServer = false;
	start();
}

void Game::draw()
{
	system("cls");
	cout << "\t     Your field: \t\t\t      Enemy field:" << endl << "\t";
	for (int i = 0; i < 10; i++)
	{
		cout << " " << i;
	}
	cout << "\t\t\t ";
	for (int i = 0; i < 10; i++)
	{
		cout << " " << i;
	}
	cout << endl << "       |--------------------\t\t\t|--------------------";
	for (int i = 1; i <= 10; i++)
	{
		cout << endl << "     " << (char)(i + 64) << " | ";
		for (int j = 0; j < 10; j++)
		{
			cout << myField[i - 1][j] << " ";
		}
		cout << "\t\t" << "      " << (char)(i + 64) << " | ";
		for (int j = 0; j < 10; j++)
		{
			cout << enemyField[i - 1][j] << " ";
		}
	}
	cout << endl << endl;
}

Game::~Game()
{
	connection->Close();
}

void Game::clearFields()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			myField[i][j] = '.';
			enemyField[i][j] = '.';
		}
	}
}

void Game::setupFields()
{
	const int numOfShips = sizeof(listOfShips) / sizeof(listOfShips[0]);
	int orientation = 0;
	for (int i = 0; i < numOfShips; i++)
	{
		draw();
		
		if (listOfShips[i] > 1)
		{
			cout << "Choose orientation of " << listOfShips[i] << "-tiled ship (h-horizontally, v-vertically): ";
			char c = _getch();
			while (c != 'h' && c != 'H' && c != 'v' && c != 'V')
			{
				c = _getch();
			}
			if (c == 'h' || c == 'H')
				orientation = 0;
			else
				orientation = 1;
			cout << c << endl;
		}

		cout << "Select first tile to place " << listOfShips[i] << "-tiled ship on: ";
		string s;
		cin >> s;
		while (s.length() != 2 || 
			(s[1] < 48 || s[1] > 57) && (s[1] < 65 || s[1] > 74) && (s[1] < 97 || s[1] > 106) ||
			(s[0] < 48 || s[0] > 57) && (s[0] < 65 || s[0] > 74) && (s[0] < 97 || s[0] > 106))
		{
			cout << "Enter correct coordinates:" << endl;
			cin >> s;
		} 
	}
	cout << "Waiting for another player to finish setting up his ships...";
	connection->Send("1");
	connection->Receive();
}


void Game::step()
{
	draw();
	
}
