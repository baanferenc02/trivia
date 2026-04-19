#include <iostream>
#include <list>
#include <vector>
#include "Player.h"
using namespace std;

#ifndef GAME_H_
#define GAME_H_

class Game
{
private:
	vector<Player> players;

	list<string> popQuestions;
	list<string> scienceQuestions;
	list<string> sportsQuestions;
	list<string> rockQuestions;

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
	void askQuestion();
	string currentCategory();
public:
	bool wasCorrectlyAnswered();
	bool wrongAnswer();
private:
	bool didPlayerWin();
};

#endif /* GAME_H_ */
