#pragma once

#include "MatrixClass.h"
#include "GameStateClass.h"
#include <stdlib.h>
#include <time.h>

const double DEFAULT_LEARNING_RATE = 3.0;
const double DEFAULT_MINIBATCH_SIZE = 1;
const double DEFAULT_DISCOUNT_FACTOR = 1;

const int SIGMOID = 0;
const int RELU = 1;

class NNClass
{
private:
	double learningRate;
	double momentumFactor;
	double discountFactor;
	int miniBatchSize;
	int curEpisodeNum;
	int numLayers;
	vector< int > nodesInLayer;
	vector< double(*)(double) > activationType, activationTypePrime;
	vector< MatrixClass<double> > nodeLayer, dJdB, dJdW, weight, bias, dJdBc, dJdWc, prev_dJdBc, prev_dJdWc;
	vector<vector< GameStateClass >> prevStates;
	vector<vector< int >> prevMoves;

public:
	NNClass();
	int compute(GameStateClass &curState, bool agentIsTrainging = false);

	void backPropogate(vector<double> expectedOutput);
	void updateWeightsAndBiases();
	void setLearningRate(double in);
	void setMiniBatchSize(int in);
	~NNClass();

	NNClass(int numInputNodes, int inputNodeType, int numOutputNodes, int outputNodeType);
	void addHiddenLayer(int numNodes, int nodeType);
	void init();
	void enableMomentum(double in);
	void PGtrain();
};

double random(double x);
double sigmoid(double x);
double sigmoidPrime(double x);
double relu(double x);
double reluPrime(double x);

