#ifndef CREATURE_H
#define CREATURE_H

#include "../Shared/Headers/WorldState.h"

class Creature {
public:
	Creature(CreatureState* state);

	void update();
private:
	CreatureState* state;
};

#endif // !CREATURE_H
