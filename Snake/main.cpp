#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include "MapClass.h"
#include "FoodClass.h"
#include "SnakeClass.h"

const bool ENABLE_RANDOM = false;
const float TIME_STEP_PER_ROUND = .95;
const int INITIAL_TIME_PER_ROUND = 100; //milliseconds

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 600), "Snake!");

	MapClass map(window.getSize(), ENABLE_RANDOM);
	SnakeClass snake(map);
	FoodClass food;
	food.createNew(map);

	while (window.isOpen())
	{
		static int nextMove = UP;
		static bool inputAccepted = false;
		static int timePerRound = INITIAL_TIME_PER_ROUND; 

		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed) window.close();
			else if (event.type == sf::Event::KeyPressed && !inputAccepted) {
				if (event.key.code == sf::Keyboard::Left && nextMove != RIGHT) {
					nextMove = LEFT; 
					inputAccepted = true;
				}
				else if (event.key.code == sf::Keyboard::Right && nextMove != LEFT) {
					nextMove = RIGHT;
					inputAccepted = true;
				}
				else if (event.key.code == sf::Keyboard::Up && nextMove != DOWN) {
					nextMove = UP;
					inputAccepted = true;
				}
				else if (event.key.code == sf::Keyboard::Down && nextMove != UP) {
					nextMove = DOWN;
					inputAccepted = true;
				}
			}
		}
		int moveResult = snake.move(map, nextMove);
		inputAccepted = false;
		std::this_thread::sleep_for(std::chrono::milliseconds(int(timePerRound)));

		if (moveResult != GAME_OVER) {
			if (moveResult == EAT_FOOD) {
				food.createNew(map);
				timePerRound *= TIME_STEP_PER_ROUND;
			}
		}
		else if (moveResult == GAME_OVER) window.close();
		
		window.clear();
		map.draw(window);
		window.display();
	}

	return 0;
}