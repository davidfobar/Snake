#include "QAgentClass.h"

QAgentClass::QAgentClass(){}

QAgentClass::QAgentClass(SnakeGameClass game) {
	int x = game.getMapWidth();
	int y = game.getMapHeight();
	
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
									if (fNegY > 10 || fNegX > 10 || fPosX > 10 || fPosY > 10) {
										cout << fPosX << " " << fPosY << " " << fNegX << " " << fNegY << endl;
									}

									else QValue[posX][posY][negX][negY][fPosX][fPosY][fNegX][fNegY] = new double[4];
									
									for (int i = 0; i < 4; i++) {
										//QValue[posX][posY][negX][negY][fPosX][fPosY][fNegX][fNegY][i] = random();
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

QAgentClass::~QAgentClass(){
}

double random(){
	return (double)(rand() % 10000 + 1) / 10000 - 0.5;
}