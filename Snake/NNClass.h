#pragma once

#include "MatrixClass.h"
#include <stdlib.h>
#include <time.h>

const bool AGENT_PLAYING = true;
const bool AGENT_TRAINING = true;
const double LEARNING_RATE = 0.001;

class NNClass
{
private:
	double learningRate;
	int numWeights, numBiases;
	int numHiddenLayers;
	int miniBatchSize;
	int numOutputs;
	MatrixClass<double> inputLayer, outputLayer, *dJdB, *dJdW;
	MatrixClass<double> *hLayer, *weight, *bias, *dJdBc, *dJdWc;
public:
	NNClass();
	NNClass(int layers, int *nodesInLayer);
	int compute(vector<double> input);

	void backPropogate(vector<double> expectedOutput);
	void updateWeightsAndBiases(int miniBatchSize);
	void setLearningRate(double in);
	~NNClass();
};

double random(double x);
double sigmoid(double x);
double sigmoidPrime(double x);

