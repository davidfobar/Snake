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

	NNClass agent(gameState.getStateSize(),SIGMOID,4,SIGMOID);
	agent.setLearningRate(LEARNING_RATE);

	int gameCount = 0;
	bool updateScreen = true;

	while (window.isOpen())	{
		int nextMove = NO_CHANGE;
		static int timePerRound = INITIAL_TIME_PER_ROUND; 

		if (false) {}
		if (AGENT_PLAYING) {
			game.getState(gameState);
			nextMove = agent.compute( gameState.getState() );
		}
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

		bool snakeKilled = game.moveSnake(nextMove);

		if (AGENT_TRAINING) {
			game.getState(gameState);
		}

		//Only show the first 20 games of training
		if (AGENT_TRAINING && gameCount > 20) updateScreen = false;

		if (snakeKilled) {
			gameCount++;
			cout << "Game " << gameCount << " ended: " << gameState.getScore() << endl;
			if (gameCount > 30000) updateScreen = true;
		}
		
		if(updateScreen){
			this_thread::sleep_for(chrono::milliseconds(int(timePerRound)));
			window.clear();
			game.draw(window);
			window.display();
		}

		if (AGENT_TRAINING) {
			
		}

		if (snakeKilled) {
			game.reset();
		}
	}

	return 0;
}