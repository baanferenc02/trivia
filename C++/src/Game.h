#ifndef GAME_H_
#define GAME_H_

#include <array>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "Player.h"

class Game
{
private:
	enum class Category { Pop, Science, Sports, Rock };

	std::vector<Player> players;

	std::array<std::list<std::string>, 4> questionDecks;

	unsigned int currentPlayer;
	bool isGettingOutOfPenaltyBox;
public:
	Game();

	bool isPlayable();
	bool add(const Player& player);
	int howManyPlayers();
	void roll(int roll);
	bool wasCorrectlyAnswered();
	bool wrongAnswer();
private:
	void advanceCurrentPlayer();
	void moveCurrentPlayer(int roll);
	bool awardCoinAndAdvance();
	void askQuestion();
	Category currentCategory();
	std::string categoryName(Category category);
	std::list<std::string>& questionsFor(Category category);
	bool didPlayerWin();
};

#endif /* GAME_H_ */
