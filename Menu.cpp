#include "Menu.hpp"
#include <functional>

using namespace sf;

Menu::Menu(t_data* data, RenderWindow& window) : _window(window) {
	_3to3.setTexture(data->yesButtonTxt);
	_5to5.setTexture(data->noButtonTxt);
	_zeroPl.setTexture(data->yesButtonTxt);
	_onePl.setTexture(data->noButtonTxt);
	_twoPl.setTexture(data->noButtonTxt);
	_background.setTexture(data->backgroundTxt);
	_playButton.setTexture(data->playButtonTxt);
	_yesButtonTxt = data->yesButtonTxt;
	_noButtonTxt = data->noButtonTxt;
	_3to3.setPosition(87, 80);
	_5to5.setPosition(172, 80);
	_zeroPl.setPosition(87, 160);
	_onePl.setPosition(150, 160);
	_twoPl.setPosition(210, 160);
	_background.setPosition(0, 0);
	_playButton.setPosition(100, 240);
	_currButton = 0;
	_players = 0;
	_fieldSize = 3;
}

Menu::~Menu() {};

void Menu::threeTothree() {
	_5to5.setTexture(_noButtonTxt);
	_3to3.setTexture(_yesButtonTxt);
	_fieldSize = 3;
}

void Menu::fiveTofive() {
	_3to3.setTexture(_noButtonTxt);
	_5to5.setTexture(_yesButtonTxt);
	_fieldSize = 5;
}

void Menu::zeroPlayer() {
	_onePl.setTexture(_noButtonTxt);
	_twoPl.setTexture(_noButtonTxt);
	_zeroPl.setTexture(_yesButtonTxt);
	_players = 0;
}

void Menu::onePlayer() {
	_zeroPl.setTexture(_noButtonTxt);
	_twoPl.setTexture(_noButtonTxt);
	_onePl.setTexture(_yesButtonTxt);
	_players = 1;
}

void Menu::twoPlayer() {
	_zeroPl.setTexture(_noButtonTxt);
	_onePl.setTexture(_noButtonTxt);
	_twoPl.setTexture(_yesButtonTxt);
	_players = 2;
}

std::pair<int, int> Menu::renderScreen(t_data* data) {
	Event event;
	while (_window.isOpen()) {
		while (_window.pollEvent(event))
			if (event.type == Event::Closed) {
				_window.close();
				exit(0);
			}
		_currButton = 0;
		if (IntRect(87, 80, 137, 120).contains(Mouse::getPosition(_window)))
			_currButton = 0; //3x3 button
		if (IntRect(172, 80, 222, 120).contains(Mouse::getPosition(_window)))
			_currButton = 1; //5x5 button
		if (IntRect(87, 160, 137, 210).contains(Mouse::getPosition(_window)))
			_currButton = 2; //0 players button
		if (IntRect(150, 160, 200, 210).contains(Mouse::getPosition(_window)))
			_currButton = 3; //1 player button
		if (IntRect(210, 160, 260, 210).contains(Mouse::getPosition(_window)))
			_currButton = 4; //2 players button
		if (IntRect(100, 240, 200, 290).contains(Mouse::getPosition(_window)))
			_currButton = 5; //play button
		if (Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (_currButton == 5) {
				if (_fieldSize == 3) {
					data->cellO.loadFromFile("images/o.png");
					data->cellX.loadFromFile("images/x.png");
					data->emptyCell.loadFromFile("images/empty.png");
				}
				else {
					data->cellO.loadFromFile("images/60o.png");
					data->cellX.loadFromFile("images/60x.png");
					data->emptyCell.loadFromFile("images/60empty.png");
				}
				return std::pair<int, int>(_fieldSize, _players);
			}
			else {
				if (_currButton == 0)
					threeTothree();
				else if (_currButton == 1)
					fiveTofive();
				else if (_currButton == 2)
					zeroPlayer();
				else if (_currButton == 3)
					onePlayer();
				else if (_currButton == 4)
					twoPlayer();
			}
		}
		_window.draw(_background);
		_window.draw(_playButton);
		_window.draw(_3to3);
		_window.draw(_5to5);
		_window.draw(_zeroPl);
		_window.draw(_onePl);
		_window.draw(_twoPl);
		_window.display();
	}
};