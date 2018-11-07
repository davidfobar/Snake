#pragma once
#include <vector>
using namespace std;

class GameStateClass{
private:
	vector<double> mapState;
	int score;
	int numMoves;
	double foodHeadDist;
public:
	//int posx, posy, negx, negy, fposx, fposy, fnegx, fnegy, score;
	GameStateClass();
	~GameStateClass();
	int getStateSize();
	int getNumMoves() { return numMoves; }
	double getHFDist() { return foodHeadDist; }
	void updateState(vector<double> inMap, int curScore, int numMoves, double dist);
	vector<double> getState();
	int getScore();
};

