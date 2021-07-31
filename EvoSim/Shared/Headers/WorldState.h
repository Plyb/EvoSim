#ifndef WORLD_STATE_H
#define WORLD_STATE_H

#include <vector>
#include <map>

struct CreatureState {
	long long id;
	float xpos;
	float ypos;
	float rot;
	float energy;
	unsigned int age = 0;

	float reproductionEnergy = 100;
	int reproduce_count;

	//Color values (for communications)
	double r;
	double g;
	double b;


	std::vector<std::vector<std::vector<double>>> weights;

	float eaten;

	static long long LAST_ID;
};

struct CellState {
	unsigned char food;
};

struct WorldState {
	WorldState();
	WorldState(std::map<long long, CreatureState> creatures);
	WorldState(WorldState* other);

	std::map<long long, CreatureState> creatures;
	static const int WORLD_WIDTH = 100;
	CellState ground[WorldState::WORLD_WIDTH][WorldState::WORLD_WIDTH];
};

#endif