#include "Game.h"
#include <iostream>
#include <string>

using namespace std;

Game::Game() : currentPlayer(0), isGettingOutOfPenaltyBox(false)
{
	for (int questionIndex = 0; questionIndex < 50; ++questionIndex)
	{
		questionsFor(Category::Pop)
			.push_back("Pop Question " + to_string(questionIndex));
		questionsFor(Category::Science)
			.push_back("Science Question " + to_string(questionIndex));
		questionsFor(Category::Sports)
			.push_back("Sports Question " + to_string(questionIndex));
		questionsFor(Category::Rock)
			.push_back("Rock Question " + to_string(questionIndex));
	}
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
	cout << "The category is " << categoryName(currentCategory()) << endl;
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
	list<string>& categoryQuestions = questionsFor(currentCategory());
	cout << categoryQuestions.front() << endl;
	categoryQuestions.pop_front();
}

Game::Category Game::currentCategory()
{
	switch (players[currentPlayer].place % 4)
	{
	case 0:
		return Category::Pop;
	case 1:
		return Category::Science;
	case 2:
		return Category::Sports;
	default:
		return Category::Rock;
	}
}

string Game::categoryName(Category category)
{
	switch (category)
	{
	case Category::Pop:
		return "Pop";
	case Category::Science:
		return "Science";
	case Category::Sports:
		return "Sports";
	default:
		return "Rock";
	}
}

list<string>& Game::questionsFor(Category category)
{
	return questionDecks[static_cast<size_t>(category)];
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
