#include "QAgentClass.h"

int QAgentClass::getMove(GameStateClass &s) {
	
	if (s.posx >= MAX_DIST_FOR_STATE) s.posx = MAX_DIST_FOR_STATE-1;
	if (s.posy >= MAX_DIST_FOR_STATE) s.posy = MAX_DIST_FOR_STATE-1;
	if (s.negx >= MAX_DIST_FOR_STATE) s.negx = MAX_DIST_FOR_STATE-1;
	if (s.negy >= MAX_DIST_FOR_STATE) s.negy = MAX_DIST_FOR_STATE-1;
	if (s.fposx >= MAX_DIST_FOR_STATE) s.fposx = MAX_DIST_FOR_STATE - 1;
	if (s.fposy >= MAX_DIST_FOR_STATE) s.fposy = MAX_DIST_FOR_STATE - 1;
	if (s.fnegx >= MAX_DIST_FOR_STATE) s.fnegx = MAX_DIST_FOR_STATE - 1;
	if (s.fnegy >= MAX_DIST_FOR_STATE) s.fnegy = MAX_DIST_FOR_STATE - 1;

	//the previous state is now equal to the current state
	pS = s;

	double maxQ = QValue[s.posx][s.posy][s.negx][s.negy][s.fposx][s.fposy][s.fnegx][s.fnegy][0];
	int move = 0;
	for (int i = 1; i < 4; i++) {
		if (QValue[s.posx][s.posy][s.negx][s.negy][s.fposx][s.fposy][s.fnegx][s.fnegy][i] > maxQ) {
			maxQ = QValue[s.posx][s.posy][s.negx][s.negy][s.fposx][s.fnegy][s.fnegx][s.fnegy][i];
			move = i;
		}
	}

	prevMove = move;
	return move;
}

void QAgentClass::changeDiscountFactor(double val) {
	gamma = val;
}

void QAgentClass::updateMatrix(GameStateClass &s) {

	if (s.posx >= MAX_DIST_FOR_STATE) s.posx = MAX_DIST_FOR_STATE - 1;
	if (s.posy >= MAX_DIST_FOR_STATE) s.posy = MAX_DIST_FOR_STATE - 1;
	if (s.negx >= MAX_DIST_FOR_STATE) s.negx = MAX_DIST_FOR_STATE - 1;
	if (s.negy >= MAX_DIST_FOR_STATE) s.negy = MAX_DIST_FOR_STATE - 1;
	if (s.fposx >= MAX_DIST_FOR_STATE) s.fposx = MAX_DIST_FOR_STATE - 1;
	if (s.fposy >= MAX_DIST_FOR_STATE) s.fposy = MAX_DIST_FOR_STATE - 1;
	if (s.fnegx >= MAX_DIST_FOR_STATE) s.fnegx = MAX_DIST_FOR_STATE - 1;
	if (s.fnegy >= MAX_DIST_FOR_STATE) s.fnegy = MAX_DIST_FOR_STATE - 1;
	
	double maxQ = QValue[s.posx][s.posy][s.negx][s.negy][s.fposx][s.fposy][s.fnegx][s.fnegy][0];
	double oldQ = QValue[pS.posx][pS.posy][pS.negx][pS.negy][pS.fposx][pS.fposy][pS.fnegx][pS.fnegy][prevMove];

	for (int i = 1; i < 4; i++) {
		if (QValue[s.posx][s.posy][s.negx][s.negy][s.fposx][s.fposy][s.fnegx][s.fnegy][i] > maxQ) {
			maxQ = QValue[s.posx][s.posy][s.negx][s.negy][s.fposx][s.fposy][s.fnegx][s.fnegy][i];
		}
	}
	
	double prevQ = QValue[pS.posx][pS.posy][pS.negx][pS.negy][pS.fposx][pS.fposy][pS.fnegx][pS.fnegy][prevMove];
	QValue[pS.posx][pS.posy][pS.negx][pS.negy][pS.fposx][pS.fposy][pS.fnegx][pS.fnegy][prevMove] =
		//prevQ + learningRate * (double(s.score - pS.score) + gamma * maxQ - prevQ);
		(1 - learningRate) * prevQ + learningRate * (double(s.score - pS.score) + gamma * maxQ);
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
	
	QValue = new double********[x];
	for (int posX = 0; posX < x; posX++) {
		QValue[posX] = new double*******[y];
		
		for (int posY = 0; posY < y; posY++) {
			QValue[posX][posY] = new double ******[x];
			
			for (int negX = 0; negX < x; negX++) {
				QValue[posX][posY][negX] = new double *****[y];
				
				for (int negY = 0; negY < y; negY++) {
					QValue[posX][posY][negX][negY] = new double ****[x];
					
					for (int fPosX = 0; fPosX < x; fPosX++) {
						QValue[posX][posY][negX][negY][fPosX] = new double ***[y];
						
						for (int fPosY = 0; fPosY < y; fPosY++) {
							QValue[posX][posY][negX][negY][fPosX][fPosY] = new double **[x];
							
							for (int fNegX = 0; fNegX < x; fNegX++) {
								QValue[posX][posY][negX][negY][fPosX][fPosY][fNegX] = new double *[y];
								
								for (int fNegY = 0; fNegY < y; fNegY++) {
									QValue[posX][posY][negX][negY][fPosX][fPosY][fNegX][fNegY] = new double[4];
									
									for (int i = 0; i < 4; i++) {
										QValue[posX][posY][negX][negY][fPosX][fPosY][fNegX][fNegY][i] = 0;// random();
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