//
//  game.cpp
//  XO
//
//  Created by Frenica Torn on 7/16/21.
//  Copyright © 2021 Frenica Torn. All rights reserved.
//

#include "Game.hpp"

Game::Game(int& mapSize, int& plNum, sf::RenderWindow& window, t_data* data) : _window(window), _players(plNum), _fieldSize(mapSize) {
	_plO = 'O';
	_plX = 'X';
	for (auto i = 0; i < mapSize * mapSize; i++)
		_map.push_back('e');
	_face.setTexture(data->emptyCell);
	_oWins.setTexture(data->oWins);
	_xWins.setTexture(data->xWins);
	_tie.setTexture(data->tie);
	_oWins.setPosition(0.0, 0.0);
	_xWins.setPosition(0.0, 0.0);
	_tie.setPosition(0.0, 0.0);
	_o = data->cellO;
	_x = data->cellX;
	_empty = data->emptyCell;
}

Game::~Game() {};

void Game::renderScreen() {
	for (size_t i = 0; i < _map.size(); i++) {
		if (_map[i] == 'X')
			_face.setTexture(_x);
		else if (_map[i] == 'O')
			_face.setTexture(_o);
		else
			_face.setTexture(_empty);
		_face.setPosition((float)((i % _fieldSize) * (300 / _fieldSize)), (float)((i / _fieldSize) * (300 / _fieldSize)));
		_window.draw(_face);
	}
}

std::vector<int> Game::avalibleCells(std::vector<char>& map) {
	std::vector<int> res;
	for (size_t i = 0; i < map.size(); i++)
		if (map[i] == 'e')
			res.push_back(i);
	return res;
}

bool Game::checkWinner(char pl, std::vector<char>& map) {
	for (int i = 0; i < _fieldSize; i++)
		if (checkEnemyHorisontal(pl, i, 0, map) == _fieldSize || checkEnemyVertical(pl, i, 0, map) == _fieldSize)
			return true;
	if (checkEnemyDiagonal(pl, 1, 0, map) == _fieldSize || checkEnemyDiagonal(pl, 2, 0, map) == _fieldSize)
		return true;
	return false;
}

void Game::congrats(int pl) {
	while (_window.isOpen()) {
		sf::Event event;
		while (_window.pollEvent(event))
			if (event.type == sf::Event::Closed) {
				_window.close();
				exit(0);
			}
		_window.clear();
		if (pl == 'X')
			_window.draw(_xWins);
		else if (pl == 'O')
			_window.draw(_oWins);
		else
			_window.draw(_tie);
		_window.display();
	}
}

std::pair<int, int> Game::bot(std::vector<char> map, char pl) {
	std::vector<int> avalible = avalibleCells(map);
	std::vector<std::pair<int, int> > moves;
	int best = 0;
	if (checkWinner(_plX, map))
		return std::pair<int, int>(0, -1);
	else if (checkWinner(_plO, map))
		return std::pair<int, int>(0, 1);
	else if (avalible.size() == 0)
		return std::pair<int, int>(0, 0);
	for (size_t i = 0; i < avalible.size(); i++) {
		std::pair<int, int> move;
		move.first = avalible[i];
		map[avalible[i]] = pl;
		if (pl == _plO)
			move.second = bot(map, _plX).second;
		else
			move.second = bot(map, _plO).second;
		map[avalible[i]] = 'e';
		moves.push_back(move);
	}
	int max;
	if (pl == 'O') {
		max = -100;
		for (size_t i = 0; i < moves.size(); i++) {
			if (moves[i].second > max) {
				max = moves[i].second;
				best = i;
			}
		}
	}
	else {
		max = 100;
		for (size_t i = 0; i < moves.size(); i++) {
			if (moves[i].second < max) {
				max = moves[i].second;
				best = i;
			}
		}
	}
	return moves[best];
}

void Game::bigMapBot(char pl) {
	int diagonalOne = 0;
	int diagonalTwo = 0;
	int MaxEnemyIVert = 0;
	int MaxEnemyIHori = 0;
	int absoluteMax = 0;
	char enemy = 'X';
	if (pl == 'X')
		enemy = 'O';
	std::vector<int> horisontal;
	std::vector<int> vertical;
	diagonalOne = checkEnemyDiagonal(enemy, 1, 1, _map);
	diagonalTwo = checkEnemyDiagonal(enemy, 2, 1, _map);
	for (int i = 0; i < _fieldSize; i++)
		horisontal.push_back(checkEnemyHorisontal(enemy, i, 1, _map));
	for (int i = 0; i < _fieldSize; i++)
		vertical.push_back(checkEnemyVertical(enemy, i, 1, _map));
	MaxEnemyIHori = distance(horisontal.begin(), max_element(horisontal.begin(), horisontal.end()));
	MaxEnemyIVert = distance(vertical.begin(), max_element(vertical.begin(), vertical.end()));
	if (diagonalOne == 0 && diagonalTwo == 0 && horisontal[MaxEnemyIHori] == 0
		&& vertical[MaxEnemyIVert] == 0) {
		_map[(_fieldSize * _fieldSize - 1) / 2] = pl;
		return;
	}
	absoluteMax = std::max({ diagonalOne, diagonalTwo, horisontal[MaxEnemyIHori], vertical[MaxEnemyIVert] });
	if (absoluteMax == diagonalOne) {
		for (int i = 0; i < _fieldSize; i++)
			if (_map[i * _fieldSize + i] == 'e') {
				_map[i * _fieldSize + i] = pl;
				break;
			}
	}
	else if (absoluteMax == diagonalTwo) {
		int l = _fieldSize - 1;
		for (int i = 0; i < _fieldSize; i++) {
			if (_map[i * _fieldSize + l] == 'e') {
				_map[i * _fieldSize + l] = pl;
				break;
			}
			l--;
		}
	}
	else if (absoluteMax == horisontal[MaxEnemyIHori]) {
		for (int i = 0; i < _fieldSize; i++)
			if (_map[MaxEnemyIHori * _fieldSize + i] == 'e') {
				_map[MaxEnemyIHori * _fieldSize + i] = pl;
				break;
			}
	}
	else {
		for (int i = 0; i < _fieldSize; i++)
			if (_map[i * _fieldSize + MaxEnemyIVert] == 'e') {
				_map[i * _fieldSize + MaxEnemyIVert] = pl;
				break;
			}
	}
}

void Game::swapActivePlayer() {
	char tmp = _plX;
	_plX = _plO;
	_plO = tmp;
}

int Game::checkEnemyVertical(char enemy, int x, int flag, std::vector<char>& map) {
	int res = 0;
	int empty = 0;
	for (int i = 0; i < _fieldSize; i++) {
		if (map[i * _fieldSize + x] == enemy)
			res++;
		if (map[i * _fieldSize + x] == 'e')
			empty++;
	}
	if (empty == 0 && flag == 1)
		res = 0;
	return res;
}

int Game::checkEnemyHorisontal(char enemy, int y, int flag, std::vector<char>& map) {
	int res = 0;
	int empty = 0;
	for (int i = 0; i < _fieldSize; i++) {
		if (map[y * _fieldSize + i] == enemy)
			res++;
		if (map[y * _fieldSize + i] == 'e')
			empty++;
	}
	if (empty == 0 && flag == 1)
		res = 0;
	return res;
}

int Game::checkEnemyDiagonal(char enemy, int i, int flag, std::vector<char>& map) {
	int res = 0;
	int empty = 0;
	if (i == 1) {
		for (int j = 0; j < _fieldSize; j++) {
			if (map[j * _fieldSize + j] == enemy)
				res++;
			if (map[j * _fieldSize + j] == 'e')
				empty++;
		}
	}
	else {
		int l = _fieldSize - 1;
		for (int j = 0; j < _fieldSize; j++) {
			if (map[j * _fieldSize + l] == enemy)
				res++;
			if (map[j * _fieldSize + l] == 'e')
				empty++;
			l--;
		}
	}
	if (empty == 0 && flag == 1)
		res = 0;
	return res;
}

void Game::gameStatusCheck() {
	if (checkWinner(_plX, _map))
		return congrats(_plX);
	if (checkWinner(_plO, _map))
		return congrats(_plO);
	if (avalibleCells(_map).size() == 0)
		return congrats('e');
}

void Game::gameLogic() {
	int botHit = 0;
	int currCellNum = -1;
	int cellSize = 300 / _fieldSize; // 300 - screen size
	if (_players == 0) {
		if (_fieldSize == 3)
			_map[bot(_map, _plX).first] = _plX;
		else
			bigMapBot(_plX);
		gameStatusCheck();
		if (_fieldSize == 3)
			_map[bot(_map, _plO).first] = _plO;
		else
			bigMapBot(_plO);
		gameStatusCheck();
	}
	else {
		for (auto y = 0; y < _fieldSize; y++) {
			for (auto x = 0; x < _fieldSize; x++) {
				if (sf::IntRect(cellSize * x, cellSize * y, cellSize * (x + 1), cellSize * (y + 1)).contains(sf::Mouse::getPosition(_window)))
					currCellNum = y * _fieldSize + x;
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _map[currCellNum] == 'e') {
			_map[currCellNum] = _plX;
			gameStatusCheck();
			if (_players == 1) {
				if (_fieldSize == 3)
					_map[bot(_map, _plO).first] = _plO;
				else
					bigMapBot(_plO);
				gameStatusCheck();
			}
			else
				swapActivePlayer();
		}
	}
}
