#include "ScoreBoardClass.h"

ScoreBoardClass::ScoreBoardClass(){
	//sf::Text scoreText;
	//sf::Font font;
	//font.loadFromFile("arial.ttf");
	curScore = INITIAL_SCORE;
	//scoreText.setFillColor(sf::Color::Red);
	//scoreText.setPosition(sf::Vector2f(0., 500.));
	//scoreText.setCharacterSize(80);
}

ScoreBoardClass::~ScoreBoardClass(){
}

int ScoreBoardClass::getScore() {
	return curScore;
}

void ScoreBoardClass::updateScore(int val) {
	curScore += val;
}

void ScoreBoardClass::reset() {
	curScore = 100;
}

void ScoreBoardClass::draw(sf::RenderWindow &window) {
	std::stringstream ss;
	ss << curScore;
	sf::Text scoreText;
	sf::Font font;

	scoreText.setString(ss.str());
	font.loadFromFile("arial.ttf");
	scoreText.setFont(font); // font is a sf::Font
	scoreText.setCharacterSize(80); // in pixels, not points!
	scoreText.setFillColor(sf::Color::White);
	window.draw(scoreText);

}