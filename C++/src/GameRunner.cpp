#include <stdlib.h>
#include "Game.h"

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
		result = aGame.takeTurn(rand() % 5 + 1, rand() % 9 != 7);
		if (result.gameWon)
			std::cout << "Game over!" << std::endl;

	} while (!result.gameWon);
}
