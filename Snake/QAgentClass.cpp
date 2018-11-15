#include "QAgentClass.h"

int QAgentClass::getMove(GameStateClass &s) {
	//the previous state is now equal to the current state
	pS = s;
	
	truncateState(s);

	double maxQ = getQat(s,0);
	int move = 0;
	for (int i = 1; i < 4; i++) {
		if (getQat(s,i) > maxQ) {
			maxQ = getQat(s, i);
			move = i;
		}
	}

	prevMove = move;
	return move;
}

void QAgentClass::changeDiscountFactor(double val) {
	if (val < 0) val = 0;
	if (val > 1) val = 1;
	gamma = val;
}

void QAgentClass::updateMatrix(GameStateClass &s) {
	double reward = double(s.score - pS.score) + DISTANCE_REWARD_FACTOR *(distToFood(pS) - distToFood(s));

	truncateState(s);
	truncateState(pS);
	
	double maxQ = getQat(s, 0);
	for (int i = 1; i < 4; i++) {
		if (getQat(s, i) > maxQ) {
			maxQ = getQat(s, i);
		}
	}

	double prevQ = getQat(pS, prevMove);
	double newQ = (1 - learningRate) * prevQ + learningRate * (reward + gamma * maxQ);
	setQat(pS, prevMove, newQ);
}

double QAgentClass::getQat(GameStateClass &s, int i) {
	return QValue[s.posx][s.posy][s.negx][s.negy][s.fposx][s.fposy][s.fnegx][s.fnegy][i];
}

void QAgentClass::setQat(GameStateClass &s, int i, double val) {
	QValue[s.posx][s.posy][s.negx][s.negy][s.fposx][s.fposy][s.fnegx][s.fnegy][i] = val;
}

double QAgentClass::distToFood(GameStateClass &s) {
	return sqrt((s.fposx + s.fnegx)*(s.fposx + s.fnegx) + (s.fposy + s.fnegy)*(s.fposy + s.fnegy));
}

void QAgentClass::truncateState(GameStateClass &s) {
	if (s.posx >= MAX_DIST_FOR_STATE) s.posx = MAX_DIST_FOR_STATE - 1;
	if (s.posy >= MAX_DIST_FOR_STATE) s.posy = MAX_DIST_FOR_STATE - 1;
	if (s.negx >= MAX_DIST_FOR_STATE) s.negx = MAX_DIST_FOR_STATE - 1;
	if (s.negy >= MAX_DIST_FOR_STATE) s.negy = MAX_DIST_FOR_STATE - 1;
	if (s.fposx >= MAX_DIST_FOR_FOOD) s.fposx = MAX_DIST_FOR_FOOD - 1;
	if (s.fposy >= MAX_DIST_FOR_FOOD) s.fposy = MAX_DIST_FOR_FOOD - 1;
	if (s.fnegx >= MAX_DIST_FOR_FOOD) s.fnegx = MAX_DIST_FOR_FOOD - 1;
	if (s.fnegy >= MAX_DIST_FOR_FOOD) s.fnegy = MAX_DIST_FOR_FOOD - 1;
}

void QAgentClass::reset() {
	prevMove = 0;
	pS.score = INITIAL_SCORE;
}

QAgentClass::QAgentClass() {
	learningRate = LEARNING_RATE;
	gamma = INITIAL_DISCOUNT_FACTOR;

	int x = MAX_DIST_FOR_STATE;
	int y = MAX_DIST_FOR_STATE;
	int fx = MAX_DIST_FOR_FOOD;
	int fy = MAX_DIST_FOR_FOOD;
	
	QValue = new double********[x];
	for (int posX = 0; posX < x; posX++) {
		QValue[posX] = new double*******[y];
		
		for (int posY = 0; posY < y; posY++) {
			QValue[posX][posY] = new double ******[x];
			
			for (int negX = 0; negX < x; negX++) {
				QValue[posX][posY][negX] = new double *****[y];
				
				for (int negY = 0; negY < y; negY++) {
					QValue[posX][posY][negX][negY] = new double ****[fx];
					
					for (int fPosX = 0; fPosX < fx; fPosX++) {
						QValue[posX][posY][negX][negY][fPosX] = new double ***[fy];
						
						for (int fPosY = 0; fPosY < fy; fPosY++) {
							QValue[posX][posY][negX][negY][fPosX][fPosY] = new double **[fx];
							
							for (int fNegX = 0; fNegX < fx; fNegX++) {
								QValue[posX][posY][negX][negY][fPosX][fPosY][fNegX] = new double *[fy];
								
								for (int fNegY = 0; fNegY < fy; fNegY++) {
									QValue[posX][posY][negX][negY][fPosX][fPosY][fNegX][fNegY] = new double[4];
									
									for (int i = 0; i < 4; i++) {
										QValue[posX][posY][negX][negY][fPosX][fPosY][fNegX][fNegY][i] = 0;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	reset();
}

QAgentClass::~QAgentClass(){
}

double random(){
	return ((double)(rand() % 10000 + 1) / 10000 - 0.5);
}