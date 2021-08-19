#include "../Headers/TimelineSerializer.h"

#include <type_traits>
#include <fstream>
#include <iostream>
#include <errno.h>
#include <filesystem>
#include <Base64/base64.h>

const std::string TimelineSerializer::TIMELINE_DIRECTORY_NAME = "timeline";

void TimelineSerializer::initializeDirectory() {
	const std::string WORLD_FILE_NAME = "world.evo";
	const std::string WORLD_FILEPATH = getPath({ TIMELINE_DIRECTORY_NAME, WORLD_FILE_NAME });

	std::filesystem::create_directories(getPath({ TIMELINE_DIRECTORY_NAME }));
	std::ofstream worldEvoFile;
	worldEvoFile.open(WORLD_FILEPATH, std::ios::out | std::ios::trunc);
	if (!worldEvoFile.is_open()) {
		std::cerr << "Error opening world.evo for edit: errno " << errno << std::endl;
	}

	// creature mind info
	worldEvoFile << CreatureMind::Inputs::NUM_INPUTS << ":"
		<< CreatureMind::HIDDEN_LAYER_COUNT << ":"
		<< CreatureMind::NODES_PER_LAYER << ":"
		<< CreatureMind::Outputs::NUM_OUTPUTS << '\n';

	// world size info
	worldEvoFile << ByteArray(WorldState::WORLD_WIDTH).toBase64() << ':'
		<< ByteArray(64).toBase64(); // TODO magic number: chunk width

	worldEvoFile.close();
}

void TimelineSerializer::serializeWorldState(const WorldState& worldState, unsigned int tick) {

}

void TimelineSerializer::serializeChunk(const WorldState& worldStateChunk, unsigned x, unsigned y) {

}

void TimelineSerializer::serializeCreatures(const std::map<long long, CreatureState>& creatures) {

}

void TimelineSerializer::serializeGround(CellState** ground) {

}

void TimelineSerializer::serializeCreature(const CreatureState& creature) {

}

void TimelineSerializer::serializeGroundCell(const CellState& cell) {

}

std::string TimelineSerializer::getPath(const std::vector<std::string>& steps) {
	std::stringstream ss;
	for (unsigned int i = 0; i < steps.size() - 1; i++) {
		ss << steps[i] << '/';
	}
	ss << steps[steps.size() - 1];
	return ss.str();
}

template <typename T>
TimelineSerializer::ByteArray<T>::ByteArray(T value) : value(value), size(sizeof(T)), rawArray((char*)&this->value) {}

template <typename T>
const std::string TimelineSerializer::ByteArray<T>::toBase64() const {
	const std::string base64full = base64_encode(rawArray, size);
	return base64full.substr(0, base64full.size() - 2);
}