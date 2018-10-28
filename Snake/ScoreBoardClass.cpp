#include "ScoreBoardClass.h"

ScoreBoardClass::ScoreBoardClass(){
	curScore = INITIAL_SCORE;
}

ScoreBoardClass::~ScoreBoardClass(){
}

int ScoreBoardClass::getScore() {
	return curScore;
}

void ScoreBoardClass::updateScore(int val) {
	if (val == GAME_OVER) curScore = 0;
	else curScore += val;
}

void ScoreBoardClass::reset() {
	curScore = INITIAL_SCORE;
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