#include <ctime>
#include <iostream>
#include <stdlib.h>
#include "Game.h"

namespace {
constexpr int minimumRoll = 1;
constexpr int rollRange = 5;
constexpr int wrongAnswerDivisor = 9;
constexpr int wrongAnswerValue = 7;
} // namespace

static Game::TurnResult result;

int main()
{

	srand(time(NULL));
	Game aGame;

	aGame.add({"Chet"});
	aGame.add({"Pat"});
	aGame.add({"Sue"});

	do
	{
		result =
			aGame.takeTurn(rand() % rollRange + minimumRoll,
						   rand() % wrongAnswerDivisor != wrongAnswerValue);
		for (const auto& message : result.messages)
			std::cout << message << std::endl;

		if (result.gameWon)
			std::cout << "Game over!" << std::endl;

	} while (!result.gameWon);
}
