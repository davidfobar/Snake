#pragma once

const float TIME_STEP_PER_ROUND = .95;
const int INITIAL_TIME_PER_ROUND = 50; //milliseconds

//for box class
const int BOX_SIZE = 25;
const int BLACK = 0;
const int WHITE = 1;
const int BLUE = 2;
const int RED = 3;

const int INITIAL_SCORE = 100;
const int SCOREBOARD_HEIGHT = 100;

const int GAME_OVER = 99;
const int EAT_FOOD = 10;
const int CLEAR = 11;
const int FOOD_REWARD = 30;
const int MOVE_PENALTY = -1;
const int CHANGE_DIR_PENALTY = 0;
const int COLLISION_PENALTY = -200;

const int NO_CHANGE = -99;
const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;
const int NUM_COMMANDS = 4;

