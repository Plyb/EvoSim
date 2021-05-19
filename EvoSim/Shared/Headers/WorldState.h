#ifndef WORLD_STATE_H
#define WORLD_STATE_H

#include <vector>

struct CreatureState {
	float xpos;
	float ypos;
	float rot;
};

struct WorldState {
	std::vector<CreatureState> creatures;
	unsigned int numCreatures;
};

#endif