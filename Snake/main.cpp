#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include "SnakeGameClass.h"
#include <iostream>

using namespace std;

const bool AGENT_TRAINING = false;
const float TIME_STEP_PER_ROUND = .95;
const int INITIAL_TIME_PER_ROUND = 100; //milliseconds

int main()
{
	sf::RenderWindow window(sf::VideoMode(400, 600), "Snake!");
	SnakeGameClass game(window);

	while (window.isOpen())	{
		int nextMove = NO_CHANGE;
		static int timePerRound = INITIAL_TIME_PER_ROUND; 

		if (AGENT_TRAINING) {
			game.getScore();
			//game.getState();
			//agent.process();
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

			game.moveSnake(nextMove);
			this_thread::sleep_for(chrono::milliseconds(int(timePerRound)));
		}
		window.clear();
		game.draw(window);
		window.display();
	}

	return 0;
}