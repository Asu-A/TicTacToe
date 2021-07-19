//
//  TicTacToe.cpp
//  XO
//
//  Created by Frenica Torn on 7/14/21.
//  Copyright © 2021 Frenica Torn. All rights reserved.
//

#include "TicTacToe.hpp"
#include "Menu.hpp"
#include "Game.hpp"

using namespace sf;

void loadSprites(t_data *data) {
	data->backgroundTxt.loadFromFile("images/menuBG.png");
	data->playButtonTxt.loadFromFile("images/playButton.png");
	data->yesButtonTxt.loadFromFile("images/yesButton.png");
	data->noButtonTxt.loadFromFile("images/noButton.png");
	data->oWins.loadFromFile("images/0wins.png");
	data->xWins.loadFromFile("images/Xwins.png");
	data->tie.loadFromFile("images/tie.png");
}

int main() {
	t_data data;
	int movesNumber = 1;
	RenderWindow window(VideoMode(300, 300), "XO");
	loadSprites(&data);
	Menu myMenu(&data, window);
	std::pair<int, int> params(myMenu.renderScreen(&data));
	Game myGame(params.first, params.second, window, &data);
	sleep(1);
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event))
			if (event.type == Event::Closed) {
				window.close();
				exit(0);
			}
		window.clear(Color(80, 80, 100));
		myGame.renderScreen();
		myGame.gameLogic();
		window.display();
	}
	return 0;
}
