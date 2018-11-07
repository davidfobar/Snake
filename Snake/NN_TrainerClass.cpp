#include "NN_TrainerClass.h"

NN_TrainerClass::NN_TrainerClass(NNClass &inNN) {
	nn = &inNN;

	momentumFactor = 0;
	curEpisodeNum = 0;
	learningRate = DEFAULT_LEARNING_RATE;
	miniBatchSize = DEFAULT_MINIBATCH_SIZE;
	discountFactor = DEFAULT_DISCOUNT_FACTOR;

	dJdW = nn->weight;
	dJdWc = nn->weight;
	prev_dJdWc = dJdWc;

	dJdB = nn->bias;
	dJdBc = nn->bias;
	prev_dJdBc = dJdBc;
}

void NN_TrainerClass::log(GameStateClass &state, int move) {
	prevStates.push_back(state);
	prevMoves.push_back(move);
}

void NN_TrainerClass::train(GameStateClass &state) {

	//log the last state
	prevStates.push_back(state);

	//conduct the policy gradient training.
	//for each game in the batch
	int numMoves = prevMoves.size();
	vector<double> rewards = computeRewards(prevStates);

	//for each move of the game
	for (int j = 0; j < numMoves; j++) {
		double discountReward = getExpectedReward(rewards, j);
		MatrixClass tempResult = nn->computeT(prevStates[j]);
		vector<double> softmax = tempResult.getSoftmax();
		//cout << discountReward << endl;
		backPropogate(discountReward, softmax[prevMoves[j]], prevMoves[j]);
	}


	curEpisodeNum++;
	if (curEpisodeNum == miniBatchSize) {
		//learn from previous minibatch
		updateWeightsAndBiases();
		//reset the trainer history
		curEpisodeNum = 0;

		prevStates.clear();
		prevMoves.clear();
	}
	else {
		//prepare for next game
		prevStates.clear();
		prevMoves.clear();
	}
}

void NN_TrainerClass::backPropogate(double reward, double p, int move) {
	//for a matrix with 2 hidden layers, i would expect to have 3 bias vectors.
	//I subtract by one due to the zero based system.
	int numB = nn->bias.size() - 1;

	//cout << ((nn->nodeLayer[numB].dot(nn->weight[numB])) + nn->bias[numB]).applyFunction(nn->activationTypePrime[numB + 1]);
	//cout << reward * _log(p) << endl;

	MatrixClass temp = nn->nodeLayer[numB];
	//temp.isolateNode(move);

	//for numB = 2
	//dJdB[2] =  ((nodeLayer[2]       .dot(weight[2]))        + bias[2])       .applyFunction(activationTypePrime[3]);
	dJdB[numB] = ((temp.dot(nn->weight[numB])) + nn->bias[numB]).applyFunction(nn->activationTypePrime[numB + 1]) * reward * _log(p);

	for (int i = numB - 1; i >= 0; i--) {
		//for numB = 1
		//dJdB[1] = dJdB[2].dot(weight[2].transpose())   * (nodeLayer[1].dot(weight[1])   + bias[1]).applyFunction(activationTypePrime[2]);
		dJdB[i] = dJdB[i + 1].dot(nn->weight[i + 1].transpose()) * (nn->nodeLayer[i].dot(nn->weight[i]) + nn->bias[i]).applyFunction(nn->activationTypePrime[i + 1]);
	}

	for (int i = 0; i < numB; i++) {
		//compute the change in the weight matrix
		dJdW[i] = (nn->nodeLayer[i]).transpose().dot(dJdB[i]);

		//add cummulative adjuestments for future updates to the weights and biases.
		dJdBc[i] = dJdBc[i] + dJdB[i];
		dJdWc[i] = dJdWc[i] + dJdW[i];
	}
}

void NN_TrainerClass::updateWeightsAndBiases() {
	
	for (int i = 0; i < nn->numLayers - 1; i++) {
		nn->weight[i] = nn->weight[i] - ((dJdWc[i] * (learningRate / miniBatchSize)) + prev_dJdWc[i] * momentumFactor);
	}
	
	for (int i = 0; i < nn->numLayers - 1; i++) {
		nn->bias[i] = nn->bias[i] - ((dJdBc[i] * (learningRate / miniBatchSize)) + prev_dJdBc[i] * momentumFactor);
	}

	prev_dJdWc = dJdWc;
	prev_dJdBc = dJdBc;

	for (int i = 0; i < nn->numLayers - 1; i++) {
		dJdWc[i]*0;
		dJdBc[i]*0;
	}
}

vector<double> NN_TrainerClass::computeRewards(vector<GameStateClass> &states) {
	vector<double> result;
	
	for (unsigned int i = 0; i < states.size()-1; i++) {
		double reward = states[i + 1].getScore() - states[i].getScore() + CORRECT_DIRECTION_REWARD * (states[i + 1].getHFDist() - states[i].getHFDist());
		result.push_back(reward);
	}

	return result;
}

double NN_TrainerClass::getExpectedReward(vector<double> &rewards, int startIdx) {
	double result = 0;

	for (unsigned int i = startIdx; i < rewards.size(); i++) {
		result += rewards[i] * pow(discountFactor, i);
	}
	
	return result;
}

void NN_TrainerClass::setLearningRate(double in) {
	learningRate = in;
}

void NN_TrainerClass::setDiscountFactor(double in) {
	discountFactor = in;
}

void NN_TrainerClass::setMiniBatchSize(int in) {
	miniBatchSize = in;
}

void NN_TrainerClass::enableMomentum(double in) {
	momentumFactor = in;
}

double _log(double x) {
	return log(x);
}
