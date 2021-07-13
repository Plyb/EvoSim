#ifndef WORLD_STATE_H
#define WORLD_STATE_H

#include <vector>

struct CreatureState {
	float xpos;
	float ypos;
	float rot;
	float energy;

	float reproductionEnergy = 100;
	int reproduce_count;

	//Color values (for communications)
	double r;
	double g;
	double b;


	std::vector<std::vector<std::vector<double>>> weights;

	float eaten;
};

struct CellState {
	unsigned char food;
};

struct WorldState {
	WorldState();
	WorldState(std::vector<CreatureState> creatures);
	WorldState(WorldState* other);

	std::vector<CreatureState> creatures;
	static const int WORLD_WIDTH = 100;
	CellState ground[WorldState::WORLD_WIDTH][WorldState::WORLD_WIDTH];
};

#endif