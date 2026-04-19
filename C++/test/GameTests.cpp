#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Game.h"

TEST_CASE("game becomes playable after two players are added")
{
	Game game;

	CHECK_FALSE(game.isPlayable());
	CHECK(game.add("Chet"));
	CHECK_FALSE(game.isPlayable());
	CHECK(game.add("Pat"));
	CHECK(game.howManyPlayers() == 2);
	CHECK(game.isPlayable());
}

TEST_CASE("rock question text is generated deterministically")
{
	Game game;

	CHECK(game.createRockQuestion(0) == "Rock Question 0");
	CHECK(game.createRockQuestion(17) == "Rock Question 17");
}

TEST_CASE("wrong answers keep the game going")
{
	Game game;
	game.add("Chet");

	CHECK(game.wrongAnswer());
}

TEST_CASE("player wins on sixth correct answer")
{
	Game game;
	game.add("Chet");

	for (int answerCount = 0; answerCount < 5; ++answerCount)
	{
		CHECK(game.wasCorrectlyAnswered());
	}

	CHECK_FALSE(game.wasCorrectlyAnswered());
}

TEST_CASE("player in penalty box does not progress without an odd roll")
{
	Game game;
	game.add("Chet");

	game.wrongAnswer();

	for (int answerCount = 0; answerCount < 10; ++answerCount)
	{
		CHECK(game.wasCorrectlyAnswered());
	}

	CHECK(game.howManyPlayers() == 1);
}

TEST_CASE("player in penalty box can still win after odd rolls")
{
	Game game;
	game.add("Chet");

	game.wrongAnswer();

	for (int answerCount = 0; answerCount < 5; ++answerCount)
	{
		game.roll(1);
		CHECK(game.wasCorrectlyAnswered());
	}

	game.roll(1);
	CHECK_FALSE(game.wasCorrectlyAnswered());
}