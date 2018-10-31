#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include "SnakeGameClass.h"
#include <iostream>
#include "GameStateClass.h"
#include "constants.h"
#include "NNClass.h"

using namespace std;

const double LEARNING_RATE = 0.001;
const bool AGENT_PLAYING = true;
const bool AGENT_TRAINING = false;
const bool ENABLE_RANDOM = true;

int main(){
	if (ENABLE_RANDOM) srand(time(0));
	else srand(1);

	sf::RenderWindow window(sf::VideoMode(450, 550), "Snake!");
	SnakeGameClass game(window);
	GameStateClass curState;

	curState = game.getState();

	NNClass agent(curState.getStateSize(), RELU, NUM_COMMANDS, SIGMOID);
	agent.addHiddenLayer(20, RELU);
	agent.setLearningRate(LEARNING_RATE);
	agent.init();

	int gameCount = 0;
	bool updateScreen = true;

	while (window.isOpen())	{
		int nextMove = NO_CHANGE;
		static int lastMoveNumber = 0;
		static int timePerRound = INITIAL_TIME_PER_ROUND; 

		if (AGENT_PLAYING) {
			curState = game.getState();
			nextMove = agent.compute(curState, AGENT_TRAINING);
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
		curState = game.getState();
		
		if (snakeKilled && AGENT_TRAINING) {
			agent.PGtrain();
		}

		//Only show the first 20 games of training
		if (AGENT_TRAINING && gameCount > 20) updateScreen = false;

		if (snakeKilled) {
			gameCount++;
			cout << "Game " << gameCount << " ended: " << curState.getScore() << endl;
			if (gameCount > 30000) updateScreen = true;
		}
		
		if(updateScreen){
			this_thread::sleep_for(chrono::milliseconds(int(timePerRound)));
			window.clear();
			game.draw(window);
			window.display();
		}

		if (snakeKilled) {
			game.reset();
		}
	}

	return 0;
}