#include "GameStateClass.h"

GameStateClass::GameStateClass(){
	score = 0;
	mapState.clear();
}

int GameStateClass::getStateSize() {
	return mapState.size();
}

int GameStateClass::getScore() {
	return score;
}

void GameStateClass::updateState(vector<double> inMap, int curScore) {
	mapState = inMap;
	score = curScore;
}

vector<double> GameStateClass::getState() {
	return mapState;
}

GameStateClass::~GameStateClass(){
}
