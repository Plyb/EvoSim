#ifndef WORLD_STATE_H
#define WORLD_STATE_H

struct CreatureState {
	float xpos;
	float ypos;
	float rot;
};

struct WorldState {
	CreatureState* creatures;
	unsigned int numCreatures;
};

#endif