#include "Game.h"
#include <iostream>

Game::Game(ServerConnection *connection)
{
	this->connection = connection;
	hasEnded = 0;
	isServer = true;
	setupFields();
	while (!hasEnded)
	{
		step();
	}
}

Game::Game(ClientConnection *connection)
{
	setupFields();
	isServer = false;
	this->connection = connection;
	draw();
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
}

Game::~Game()
{
	connection->Close();
}

void Game::setupFields()
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

void Game::step()
{
	
}
