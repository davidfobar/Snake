#include "GameStateClass.h"

GameStateClass::GameStateClass(){
	score = 0;
	mapState.clear();
}

int GameStateClass::getStateSize() {
	return mapState.size();
}

void GameStateClass::updateState(vector<double> in) {
	mapState = in;
}

GameStateClass::~GameStateClass(){
}
