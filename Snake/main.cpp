#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include "SnakeGameClass.h"
#include <iostream>
#include "GameStateClass.h"
#include "constants.h"
#include "NNClass.h"

using namespace std;

int main(){
	sf::RenderWindow window(sf::VideoMode(450, 550), "Snake!");
	SnakeGameClass game(window);
	GameStateClass gameState;

	game.getState(gameState);

	int numberLayers = 3;
	int nodesPerLayer[] = {gameState.getStateSize(), 300 , 4};
	NNClass agent;

	int gameCount = 0;
	bool updateScreen = true;

	while (window.isOpen())	{
		int nextMove = NO_CHANGE;
		static int timePerRound = INITIAL_TIME_PER_ROUND; 

		if (false) {}
		/*if (AGENT_TRAINING) {
			game.getState(gameState);
			nextMove = agent.getMove(gameState);
		}*/
		else {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) window.close();
				else if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Left) {
						nextMove = LEFT;
					}
					else if (event.key.code == sf::Keyboard::Right) {
						nextMove = RIGHT;
					}
					else if (event.key.code == sf::Keyboard::Up) {
						nextMove = UP;
					}
					else if (event.key.code == sf::Keyboard::Down) {
						nextMove = DOWN;
					}
				}
			}
		}
		cout << nextMove << endl;

		bool snakeKilled = game.moveSnake(nextMove);

		//if(AGENT_TRAINING) game.getState(gameState);


		//if (gameCount > 20) updateScreen = false;

		if (snakeKilled) {
			gameCount++;
			//cout << "Game " << gameCount << " ended: " << gameState.score << endl;
			//if (gameCount > 30000) updateScreen = true;
		}
		
		if(updateScreen){
			this_thread::sleep_for(chrono::milliseconds(int(timePerRound)));
			window.clear();
			game.draw(window);
			window.display();
		}
/*
		if (AGENT_TRAINING) {
			agent.updateMatrix(gameState);
			if (gameCount > INITIAL_TRAINING) {
				double newDiscountFactor = INITIAL_DISCOUNT_FACTOR + 
					(gameCount - INITIAL_TRAINING)*(MAX_DISCOUNT_FACTOR - INITIAL_DISCOUNT_FACTOR) / (TRAINING_GAMES - gameCount);
				agent.changeDiscountFactor(newDiscountFactor);
			}
		}*/

		if (snakeKilled) {
			game.reset();
			//agent.reset();
		}
	}

	return 0;
}