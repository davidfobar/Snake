#pragma once
#include "SnakeGameClass.h"
#include "GameStateClass.h"
#include "constants.h"
#include <vector>
#include <iostream>
using namespace std;

const bool AGENT_TRAINING = true;
const bool UPDATE_SCREEN = false;
const double LEARNING_RATE = 0.9;
const double INITIAL_DISCOUNT_FACTOR = 0.3;
const double MAX_DISCOUNT_FACTOR = 0.6;
const int MAX_DIST_FOR_STATE = 8;
const int MAX_DIST_FOR_FOOD = 4;
const double DISTANCE_REWARD_FACTOR = 0.1;

class QAgentClass
{
	double********* QValue;
	GameStateClass pS;
	int prevMove;
	double learningRate;
	double gamma;
	double distToFood(GameStateClass &s);
	void truncateState(GameStateClass &s);
	double getQat(GameStateClass &s, int i);
	void setQat(GameStateClass &s, int i, double val);
public:
	QAgentClass();
	~QAgentClass();
	int getMove(GameStateClass &s);
	void updateMatrix(GameStateClass &s);
	void reset();
	void changeDiscountFactor(double val);
};

double random();

