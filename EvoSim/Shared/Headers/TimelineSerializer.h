#ifndef WORLD_STATE_SERIALIZER_H
#define WORLD_STATE_SERIALIZER_H

#include "WorldState.h"
#include "CreatureMind.h"
#include <string>

class TimelineSerializer {
public:
	static void initializeDirectory();
	static void serializeWorldState(const WorldState& worldState, unsigned int tick);
private:
	static void serializeChunk(const WorldState& worldStateChunk, unsigned x, unsigned y);

	static void serializeCreatures(const std::map<long long, CreatureState>& creatures);
	static void serializeGround(CellState** ground);

	static void serializeCreature(const CreatureState& creature);
	static void serializeGroundCell(const CellState& cell);

	static std::string getPath(const std::vector<std::string>& steps);

	static const std::string TIMELINE_DIRECTORY_NAME;

	template <typename T>
	class ByteArray {
	public:
		ByteArray(T value);
		const std::string toBase64() const;
		friend std::ostream& operator<<(std::ostream& os, const ByteArray& byteArray) {
			for (unsigned int i = 0; i < byteArray.size; i++) {
				os << byteArray.rawArray[i];
			}
			return os;
		}
	private:
		T value;
		const unsigned int size;
		const char* rawArray;
	};
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
{mindinputs-base10}:{num hidden layers-base10}:{hidden layer nodes-base10}:{output nodes-base10}\n
{worldwidth-base64}:{chunkwidth-base64}

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