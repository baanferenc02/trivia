#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>

struct Player {
	std::string name;
	int place = 0;
	int purse = 0;
	bool inPenaltyBox = false;
};

#endif /* PLAYER_H_ */