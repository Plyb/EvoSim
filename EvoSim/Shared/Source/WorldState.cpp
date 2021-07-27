#include "../Headers/WorldState.h"

// TODO for both constructors, create something more permanent
WorldState::WorldState() : creatures(std::map<long long, CreatureState>()) {
	for (unsigned int i = 0; i < WORLD_WIDTH; i++) {
		for (unsigned int j = 0; j < WORLD_WIDTH; j++) {
			ground[i][j].food = 100;
		}
	}
}

WorldState::WorldState(std::map<long long, CreatureState> creatures) : creatures(creatures) {
	for (unsigned int i = 0; i < WORLD_WIDTH; i++) {
		for (unsigned int j = 0; j < WORLD_WIDTH; j++) {
			ground[i][j].food = 100;
		}
	}
}

WorldState::WorldState(WorldState* other) {
	creatures = other->creatures;
	for (unsigned int i = 0; i < WORLD_WIDTH; i++) {
		for (unsigned int j = 0; j < WORLD_WIDTH; j++) {
			ground[i][j] = other->ground[i][j];
		}
	}
}

long long CreatureState::LAST_ID = -1;