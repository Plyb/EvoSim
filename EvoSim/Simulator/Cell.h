#ifndef CELL_H
#define CELL_H

#include "../Shared/Headers/WorldState.h"

class Cell {
public:
	Cell();

	void update();

	void clearVisitingCreatures();
	void pushVisitingCreature(CreatureState* creature);

	const CellState* getState() const;
private:
	CellState state;
	std::vector<CreatureState*> visitingCreatures;

	static const float FOOD_BOOST_CHANCE;
	static const unsigned int FOOD_BOOST = 1;
};

#endif // !CELL_H

