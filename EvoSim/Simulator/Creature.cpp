#include "Creature.h"

#define _USE_MATH_DEFINES

#include <math.h>

Creature::Creature(CreatureState* state) : state(state) {};

void Creature::update() {
	state->rot += 0.1f;
	state->xpos += cos(state->rot * M_PI / 180) / 100.0f;
	state->ypos += sin(state->rot * M_PI / 180) / 100.0f;
}