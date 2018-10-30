#pragma once

#include "MatrixClass.h"
#include <stdlib.h>
#include <time.h>

const bool AGENT_PLAYING = true;
const bool AGENT_TRAINING = true;
const double LEARNING_RATE = 0.001;

const int SIGMOID = 0;
const int RELU = 1;

class NNClass
{
private:
	double learningRate;
	int numWeights, numBiases;
	int numHiddenLayers;
	int miniBatchSize;
	int numOutputs;
	MatrixClass<double> inputLayer, outputLayer;
	vector< MatrixClass<double> > dJdB, dJdW, hLayer, weight, bias, dJdBc, dJdWc;
public:
	NNClass();
	NNClass(int layers, int *nodesInLayer);
	int compute(vector<double> input);

	void backPropogate(vector<double> expectedOutput);
	void updateWeightsAndBiases(int miniBatchSize);
	void setLearningRate(double in);
	~NNClass();

	NNClass(int numInputNodes, int inputNodeType, int numOutputNodes, int outputNodeType);
	void addHiddenLayer(int numNodes, int nodeType);
};

double random(double x);
double sigmoid(double x);
double sigmoidPrime(double x);
double relu(double x);
double reluPrime(double x);

