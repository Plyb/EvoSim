#ifndef CREATURE_H
#define CREATURE_H

#include "../Shared/Headers/WorldState.h"
#include "Cell.h"
#include <vector>

class Creature {
public:
	Creature(CreatureState* state);

	void update(Cell ground[WorldState::WORLD_WIDTH][WorldState::WORLD_WIDTH]);
	void remapCell(Cell ground[WorldState::WORLD_WIDTH][WorldState::WORLD_WIDTH]);
	Creature* reproduce() const;
	bool isDying() const;
	bool isReproducing(Cell ground[WorldState::WORLD_WIDTH][WorldState::WORLD_WIDTH]) const;

	CreatureState* getState() const;
private:
	CreatureState* state;

	Cell* getCurrentCell(Cell ground[WorldState::WORLD_WIDTH][WorldState::WORLD_WIDTH]) const;
	const CellState* getCurrentCellState(Cell ground[WorldState::WORLD_WIDTH][WorldState::WORLD_WIDTH]) const;

	static const float BASE_ENERGY_CONSUMPTION;
	static const float BASE_ABSORPTION_RATE;
};

#endif // !CREATURE_H
