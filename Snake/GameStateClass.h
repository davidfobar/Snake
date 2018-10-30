#pragma once
#include <vector>
using namespace std;

class GameStateClass{
private:
	vector<double> mapState;
	int score;
public:
	//int posx, posy, negx, negy, fposx, fposy, fnegx, fnegy, score;
	GameStateClass();
	~GameStateClass();
	int getStateSize();
	void updateState(vector<double> inMap, int curScore);
	vector<double> getState();
	int getScore();
};

