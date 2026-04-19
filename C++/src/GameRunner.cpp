#include <stdlib.h>
#include "Game.h"

static bool notAWinner;

int main()
{

	srand(time(NULL));
	Game aGame;

	aGame.add({"Chet"});
	aGame.add({"Pat"});
	aGame.add({"Sue"});

	do
	{
		bool canAnswer = aGame.roll(rand() % 5 + 1);

		if (canAnswer)
		{
			if (rand() % 9 == 7)
			{
				notAWinner = aGame.wrongAnswer();
			}
			else
			{
				notAWinner = aGame.wasCorrectlyAnswered();
			}
		}
	} while (notAWinner);
}
