#include "Game.h"
#include <iostream>
#include <string>

using namespace std;

Game::Game() : currentPlayer(0)
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

void Game::moveCurrentPlayer(int roll, vector<string>& messages)
{
	players[currentPlayer].place = players[currentPlayer].place + roll;
	if (players[currentPlayer].place > 11)
		players[currentPlayer].place = players[currentPlayer].place - 12;

	messages.push_back(players[currentPlayer].name + "'s new location is " +
					   to_string(players[currentPlayer].place));
	messages.push_back("The category is " + categoryName(currentCategory()));
	askQuestion(messages);
}

Game::TurnResult Game::takeTurn(int roll, bool answerCorrect)
{
	TurnResult result{false, {}};
	result.messages.push_back(players[currentPlayer].name +
							  " is the current player");
	result.messages.push_back("They have rolled a " + to_string(roll));

	if (players[currentPlayer].inPenaltyBox)
	{
		if (roll % 2 != 0)
		{
			result.messages.push_back(players[currentPlayer].name +
									  " is getting out of the penalty box");
			moveCurrentPlayer(roll, result.messages);
		}
		else
		{
			result.messages.push_back(players[currentPlayer].name +
									  " is not getting out of the penalty box");
			advanceCurrentPlayer();
			return result;
		}
	}
	else
	{
		moveCurrentPlayer(roll, result.messages);
	}

	if (!answerCorrect)
	{
		result.messages.push_back("Question was incorrectly answered");
		result.messages.push_back(players[currentPlayer].name +
								  " was sent to the penalty box");
		players[currentPlayer].inPenaltyBox = true;
		advanceCurrentPlayer();
		return result;
	}

	result.messages.push_back("Answer was correct!!!!");
	players[currentPlayer].purse++;
	result.messages.push_back(players[currentPlayer].name + " now has " +
							  to_string(players[currentPlayer].purse) +
							  " Gold Coins.");

	result.gameWon = didPlayerWin();
	advanceCurrentPlayer();
	return result;
}

void Game::askQuestion(vector<string>& messages)
{
	list<string>& categoryQuestions = questionsFor(currentCategory());
	messages.push_back(categoryQuestions.front());
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

bool Game::didPlayerWin()
{
	return players[currentPlayer].purse == 6;
}
