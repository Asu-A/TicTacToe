//
//  game.hpp
//  XO
//
//  Created by Frenica Torn on 7/16/21.
//  Copyright © 2021 Frenica Torn. All rights reserved.
//

#ifndef game_hpp
#define game_hpp

#include "TicTacToe.hpp"
#include <SFML/Graphics.hpp>

class Tail;

class Game {
private:
	sf::RenderWindow& _window;
	int _players;
	int _fieldSize;
	char _plX;
	char _plO;
	std::vector<char> _map;
	Sprite _face;
	Sprite _xWins;
	Sprite _oWins;
	Sprite _tie;
	Texture _o;
	Texture _x;
	Texture _empty;
public:
	Game() = delete;
	Game(int& mapSize, int& plNum, sf::RenderWindow& window, t_data* data);
	Game(const Game& src) = delete;
	Game& operator=(const Game& src) = delete;
	~Game();
	void renderScreen();
	std::vector<int> avalibleCells(std::vector<char>& map);
	bool checkWinner(char pl, std::vector<char>& map);
	void congrats(int pl);
	std::pair<int, int> bot(std::vector<char> map, char pl);
	void bigMapBot(char pl);
	int checkEnemyVertical(char enemy, int x, int flag, std::vector<char>& map);
	int checkEnemyHorisontal(char enemy, int y, int flag, std::vector<char>& map);
	int checkEnemyDiagonal(char enemy, int i, int flag, std::vector<char>& map);
	void swapActivePlayer();
	void gameLogic();
	void gameStatusCheck();
};

#endif /* game_hpp */
