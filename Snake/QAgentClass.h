#pragma once
#include "SnakeGameClass.h"
#include "GameStateClass.h"
#include "constants.h"
#include <vector>
#include <iostream>
using namespace std;

const bool AGENT_TRAINING = true;
const bool UPDATE_SCREEN = false;
const double LEARNING_RATE = 0.7;
const double INITIAL_DISCOUNT_FACTOR = 0.1;
const int MAX_DIST_FOR_STATE = 5;

class QAgentClass
{
	double********* QValue;
	GameStateClass pS;
	int prevMove;
	double learningRate;
	double gamma;

public:
	QAgentClass();
	~QAgentClass();
	int getMove(GameStateClass &s);
	void updateMatrix(GameStateClass &s);
	void reset();
	void changeDiscountFactor(double val);
};

double random();

