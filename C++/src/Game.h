#ifndef GAME_H_
#define GAME_H_

#include <array>
#include <list>
#include <string>
#include <vector>
#include "Player.h"

class Game
{
public:
	struct TurnResult {
		bool gameWon;
		std::vector<std::string> messages;
	};
private:
	enum class Category { Pop, Science, Sports, Rock };

	std::vector<Player> players;

	std::array<std::list<std::string>, 4> questionDecks;

	unsigned int currentPlayer;
public:
	Game();

	bool isPlayable();
	bool add(const Player& player);
	int howManyPlayers();
	TurnResult takeTurn(int roll, bool answerCorrect);
private:
	void advanceCurrentPlayer();
	void moveCurrentPlayer(int roll, std::vector<std::string>& messages);
	void askQuestion(std::vector<std::string>& messages);
	Category currentCategory();
	std::string categoryName(Category category);
	std::list<std::string>& questionsFor(Category category);
	bool didPlayerWin();
};

#endif /* GAME_H_ */
