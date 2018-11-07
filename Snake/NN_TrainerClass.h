#pragma once
#include "NNClass.h"
#include "GameStateClass.h"
#include "MatrixClass.h"

const double DEFAULT_LEARNING_RATE = 3.0;
const int DEFAULT_MINIBATCH_SIZE = 10;
const double DEFAULT_DISCOUNT_FACTOR = .99;
const double CORRECT_DIRECTION_REWARD = 1.0;

class NN_TrainerClass {
private:
	double learningRate;
	double momentumFactor;
	double discountFactor;
	int miniBatchSize;
	int curEpisodeNum;

	NNClass *nn;
	vector< MatrixClass > dJdB, dJdW, dJdBc, dJdWc, prev_dJdBc, prev_dJdWc;
	vector<GameStateClass> prevStates;
	vector<int> prevMoves;

	vector<double> computeRewards(vector<GameStateClass> &states);
	double getExpectedReward(vector<double> &rewards, int idx);
	void backPropogate(double reward, double p, int move);

public:
	NN_TrainerClass() {};
	NN_TrainerClass(NNClass &inNN);
	
	void updateWeightsAndBiases();
	void setLearningRate(double in);
	void setDiscountFactor(double in);
	void setMiniBatchSize(int in);
	void enableMomentum(double in);
	void log(GameStateClass &state, int move);
	void train(GameStateClass &state);
};

double _log(double x);

