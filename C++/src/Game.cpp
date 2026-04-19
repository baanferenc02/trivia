#include "Game.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>

using namespace std;

Game::Game() : currentPlayer(0), isGettingOutOfPenaltyBox(false)
{
	for (int i = 0; i < 50; i++)
	{
		ostringstream oss(ostringstream::out);
		oss << "Pop Question " << i;

		popQuestions.push_back(oss.str());

		char str[255];
		sprintf(str, "Science Question %d", i);
		scienceQuestions.push_back(str);

		char str1[255];
		sprintf(str1, "Sports Question %d", i);
		sportsQuestions.push_back(str1);

		rockQuestions.push_back(createRockQuestion(i));
	}
}

string Game::createRockQuestion(int index)
{
	char indexStr[127];
	sprintf(indexStr, "Rock Question %d", index);
	return indexStr;
}

bool Game::isPlayable()
{
	return (howManyPlayers() >= 2);
}

bool Game::add(const Player& player)
{
	players.push_back(player);

	cout << player.name << " was added" << endl;
	cout << "They are player number " << players.size() << endl;
	return true;
}

int Game::howManyPlayers()
{
	return players.size();
}

void Game::advanceCurrentPlayer()
{
	currentPlayer++;
	if (currentPlayer == players.size())
		currentPlayer = 0;
}

void Game::moveCurrentPlayer(int roll)
{
	players[currentPlayer].place = players[currentPlayer].place + roll;
	if (players[currentPlayer].place > 11)
		players[currentPlayer].place = players[currentPlayer].place - 12;

	cout << players[currentPlayer].name << "'s new location is "
		 << players[currentPlayer].place << endl;
	cout << "The category is " << currentCategory() << endl;
	askQuestion();
}

bool Game::awardCoinAndAdvance()
{
	cout << "Answer was correct!!!!" << endl;
	players[currentPlayer].purse++;
	cout << players[currentPlayer].name << " now has "
		 << players[currentPlayer].purse << " Gold Coins." << endl;

	bool winner = didPlayerWin();
	advanceCurrentPlayer();
	return winner;
}

void Game::roll(int roll)
{
	cout << players[currentPlayer].name << " is the current player" << endl;
	cout << "They have rolled a " << roll << endl;

	if (players[currentPlayer].inPenaltyBox)
	{
		if (roll % 2 != 0)
		{
			isGettingOutOfPenaltyBox = true;

			cout << players[currentPlayer].name
				 << " is getting out of the penalty box" << endl;
			moveCurrentPlayer(roll);
		}
		else
		{
			cout << players[currentPlayer].name
				 << " is not getting out of the penalty box" << endl;
			isGettingOutOfPenaltyBox = false;
		}
	}
	else
	{
		moveCurrentPlayer(roll);
	}
}

void Game::askQuestion()
{
	if (currentCategory() == "Pop")
	{
		cout << popQuestions.front() << endl;
		popQuestions.pop_front();
	}
	if (currentCategory() == "Science")
	{
		cout << scienceQuestions.front() << endl;
		scienceQuestions.pop_front();
	}
	if (currentCategory() == "Sports")
	{
		cout << sportsQuestions.front() << endl;
		sportsQuestions.pop_front();
	}
	if (currentCategory() == "Rock")
	{
		cout << rockQuestions.front() << endl;
		rockQuestions.pop_front();
	}
}

string Game::currentCategory()
{
	if (players[currentPlayer].place == 0)
		return "Pop";
	if (players[currentPlayer].place == 4)
		return "Pop";
	if (players[currentPlayer].place == 8)
		return "Pop";
	if (players[currentPlayer].place == 1)
		return "Science";
	if (players[currentPlayer].place == 5)
		return "Science";
	if (players[currentPlayer].place == 9)
		return "Science";
	if (players[currentPlayer].place == 2)
		return "Sports";
	if (players[currentPlayer].place == 6)
		return "Sports";
	if (players[currentPlayer].place == 10)
		return "Sports";
	return "Rock";
}

bool Game::wasCorrectlyAnswered()
{
	if (players[currentPlayer].inPenaltyBox)
	{
		if (isGettingOutOfPenaltyBox)
		{
			return awardCoinAndAdvance();
		}
		else
		{
			advanceCurrentPlayer();
			return true;
		}
	}
	else
	{
		return awardCoinAndAdvance();
	}
}

bool Game::wrongAnswer()
{
	cout << "Question was incorrectly answered" << endl;
	cout << players[currentPlayer].name << " was sent to the penalty box"
		 << endl;
	players[currentPlayer].inPenaltyBox = true;

	advanceCurrentPlayer();
	return true;
}

bool Game::didPlayerWin()
{
	return !(players[currentPlayer].purse == 6);
}
