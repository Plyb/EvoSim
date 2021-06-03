#ifndef WORLD_STATE_H
#define WORLD_STATE_H

#include <vector>

struct CreatureState {
	float xpos;
	float ypos;
	float rot;
};

struct CellState {
	unsigned char food;
	unsigned char numCreatures = 0;
	static const int MAX_CREATURES = 16;
	CreatureState* creatures[CellState::MAX_CREATURES];
};

struct WorldState {
	WorldState();
	WorldState(std::vector<CreatureState> creatures);
	WorldState(WorldState* other);

	std::vector<CreatureState> creatures;
	static const int WORLD_WIDTH = 100;
	CellState ground[WorldState::WORLD_WIDTH][WorldState::WORLD_WIDTH];

	CellState* cellAt(CreatureState& creature);
};

#endif