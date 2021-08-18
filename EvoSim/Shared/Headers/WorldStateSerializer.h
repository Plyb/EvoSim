#ifndef WORLD_STATE_SERIALIZER_H
#define WORLD_STATE_SERIALIZER_H

#include "WorldState.h"

class WorldStateSerializer {
public:
	static void serialize(const WorldState& worldState);
private:
	static void serializeChunk(const WorldState& worldStateChunk, unsigned x, unsigned y);

	static void serializeCreatures(const std::map<long long, CreatureState>& creatures);
	static void serializeGround(CellState** ground);

	static void serializeCreature(const CreatureState& creature);
	static void serializeGroundCell(const CellState& cell);
};

#endif // !WORLD_STATE_SERIALIZER_H

/*
FOLDER FORMAT:
root
 |-world.evo
 |-{timestamp}
 \-{timestamp}
    |-{chunkx}-{chunky}.chunk
    \-{chunkx}-{chunky}.chunk

WORLD FORMAT:
{mindinputs-base64}:{num hidden layers-base64}:{hidden layer nodes-base64}:{output nodes-base64}\n
{worldwidth x-base64}:{worldwidth y-base64}\n
{chunkwidth x-base64}:{chunkwidth y-base64}

CHUNK FORMAT:
{CREATURE1}\n
{CREATURE2}\n
\n
{GROUNDCELL1,1}{GROUNDCELL2,1}etc\n
{GROUNDCELL1,2}{GROUNDCELL2,2}etc\n
etc

CREATURE FORMAT:
{creature id-base64}:{xpos-raw}{ypos-raw}{rot-raw}{energy-raw}{age-raw}{MATRIX1}{MATRIX2}etc

GROUND CELL FORMAT:
{food-raw}

MATRIX FORMAT:
{x1,y1-raw as float}{x2,y1-raw as float}{x1,y2-raw as float}{x2,y2-raw as float}

*/