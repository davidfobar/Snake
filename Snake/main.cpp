#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include "SnakeGameClass.h"
#include <iostream>
#include "GameStateClass.h"
#include "constants.h"
#include "NNClass.h"
#include "NN_TrainerClass.h"

using namespace std;

const double LEARNING_RATE = 0.001;
const double MOMENTUM_RATE = 0.01;
const double DISCOUNT_FACTOR = 0.2;
const int GAMES_IN_BATCH = 20;
const bool AGENT_PLAYING = false;
const bool AGENT_TRAINING = false;
const bool ENABLE_RANDOM = true;
const bool WATCH_TRAINING = true;

int main(){
	if (ENABLE_RANDOM) srand(unsigned int(time(0)));
	else srand(1);

	sf::RenderWindow window(sf::VideoMode(550, 650), "Snake!");
	SnakeGameClass game(window);
	GameStateClass curState;

	curState = game.getState();

	NNClass agent(curState.getStateSize(), RELU, NUM_COMMANDS, SIGMOID);
	//agent.addHiddenLayer(50, SIGMOID);
	agent.addHiddenLayer(20, SIGMOID);
	agent.init();

	NN_TrainerClass trainer(agent);
	trainer.setLearningRate(LEARNING_RATE);
	trainer.setMiniBatchSize(GAMES_IN_BATCH);
	trainer.setDiscountFactor(DISCOUNT_FACTOR);
	trainer.enableMomentum(MOMENTUM_RATE);

	int gameCount = 0;
	bool updateScreen = WATCH_TRAINING;

	while (window.isOpen())	{
		int nextMove = NO_CHANGE;
		static int lastMoveNumber = 0;
		static int timePerRound = INITIAL_TIME_PER_ROUND; 

		
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
				else if (event.key.code == sf::Keyboard::V) {
					if (updateScreen) updateScreen = false;
					else updateScreen = true;
				}
			}
		}
		if (AGENT_PLAYING) {
			curState = game.getState();
			nextMove = agent.compute(curState);
			if (AGENT_TRAINING) trainer.log(curState, nextMove);
		}

		bool snakeKilled = game.moveSnake(nextMove);
		curState = game.getState();
		
		if (snakeKilled && AGENT_TRAINING) {
			trainer.train(curState);
		}

		//Only show the first 200 games of training
		//if (AGENT_TRAINING && gameCount > 20) updateScreen = false;

		if (snakeKilled) {
			gameCount++;
			cout << "Game " << gameCount << " ended, score: " << curState.getScore() << " moves: " << curState.getNumMoves() << endl;
			if (gameCount > 1000000) updateScreen = true;
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