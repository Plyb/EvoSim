#ifndef CREATURE_H
#define CREATURE_H

#include "../Shared/Headers/WorldState.h"

class Creature {
public:
	Creature(CreatureState* state, WorldState* worldState);

	void update();
private:
	CreatureState* state;
	WorldState* worldState;

	static const float BASE_ENERGY_CONSUMPTION;
	static const float BASE_ABSORPTION_RATE;
};

#endif // !CREATURE_H
