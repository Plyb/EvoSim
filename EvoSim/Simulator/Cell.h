#ifndef CELL_H
#define CELL_H

#include "../Shared/Headers/WorldState.h"

class Cell {
public:
	Cell();

	void update();

	void clearVisitingCreatures();
	void pushVisitingCreature(CreatureState* creature);
	
	const std::vector<CreatureState*> getVisitingCreatures();

	double get_color_r(); // Get the average 'red' color value for the creatures in the cell.
	double get_color_g(); // Get the average 'green' color value for the creatures in the cell.
	double get_color_b(); // Get the average 'blue' color value for the creatures in the cell.

	const CellState* getState() const;
private:
	CellState state;
	std::vector<CreatureState*> visitingCreatures;

	static const float FOOD_BOOST_CHANCE;
	static const unsigned int FOOD_BOOST = 1;
};

#endif // !CELL_H

