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
	static constexpr int minimumPlayers = 2;
	static constexpr int questionDeckSize = 50;
	static constexpr size_t categoryCount = 4;
	static constexpr int boardSize = 12;
	static constexpr int penaltyBoxReleaseDivisor = 2;
	static constexpr int oddRollRemainder = 1;
	static constexpr int winningCoinCount = 6;

	enum class Category { Pop, Science, Sports, Rock };

	std::vector<Player> players;

	std::array<std::list<std::string>, categoryCount> questionDecks;

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
