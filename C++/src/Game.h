#ifndef GAME_H_
#define GAME_H_

#include <array>
#include <iostream>
#include <list>
#include <vector>
#include "Player.h"
using namespace std;

class Game
{
private:
	enum class Category { Pop, Science, Sports, Rock };

	vector<Player> players;

	array<list<string>, 4> questionDecks;

	unsigned int currentPlayer;
	bool isGettingOutOfPenaltyBox;
public:
	Game();
	string createRockQuestion(int index);
	bool isPlayable();
	bool add(const Player& player);

	int howManyPlayers();
	void roll(int roll);
private:
	void advanceCurrentPlayer();
	void moveCurrentPlayer(int roll);
	bool awardCoinAndAdvance();
	void askQuestion();
	Category currentCategory();
	string categoryName(Category category);
	list<string>& questionsFor(Category category);
public:
	bool wasCorrectlyAnswered();
	bool wrongAnswer();
private:
	bool didPlayerWin();
};

#endif /* GAME_H_ */
