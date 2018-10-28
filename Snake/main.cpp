#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include "SnakeGameClass.h"
#include <iostream>
#include "QAgentClass.h"
#include "GameStateClass.h"
#include "constants.h"

using namespace std;

int main(){
	sf::RenderWindow window(sf::VideoMode(450, 550), "Snake!");
	SnakeGameClass game(window);
	QAgentClass agent;
	GameStateClass gameState;

	int gameCount = 0;
	bool updateScreen = false;

	while (window.isOpen())	{
		int nextMove = NO_CHANGE;
		static int timePerRound = INITIAL_TIME_PER_ROUND; 

		if (AGENT_TRAINING) {
			game.getState(gameState);
			nextMove = agent.getMove(gameState);
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

		if(AGENT_TRAINING) game.getState(gameState);

		if (snakeKilled) {
			gameCount++;
			cout << "Game " << gameCount << " ended: " << gameState.score << endl;
			if (gameCount > 1000000) updateScreen = true;
		}

		if(updateScreen){
			this_thread::sleep_for(chrono::milliseconds(int(timePerRound)));
			window.clear();
			game.draw(window);
			window.display();
		}

		if (AGENT_TRAINING) {
			agent.updateMatrix(gameState);
			//if (gameCount < 3000) agent.changeDiscountFactor((1.0-1.0/gameCount)*.3);
		}

		if (snakeKilled) {
			game.reset();
			agent.reset();
		}
	}

	return 0;
}