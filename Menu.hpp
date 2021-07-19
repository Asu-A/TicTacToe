//
//  TicTacToe.hpp
//  XO
//
//  Created by Frenica Torn on 7/16/21.
//  Copyright © 2021 Frenica Torn. All rights reserved.
//

#ifndef menu_hpp
#define menu_hpp

#include "TicTacToe.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

class Menu {
private:
	RenderWindow& _window;
	Sprite _3to3;
	Sprite _5to5;
	Sprite _zeroPl;
	Sprite _onePl;
	Sprite _twoPl;
	Sprite _playButton;
	Sprite _background;
	Texture _yesButtonTxt;
	Texture _noButtonTxt;
	int _currButton;
	int _players;
	int _fieldSize;
	void threeTothree();
	void fiveTofive();
	void zeroPlayer();
	void onePlayer();
	void twoPlayer();
public:
	Menu(t_data* data, RenderWindow& window);
	Menu(const Menu& src) = delete;
	Menu& operator=(const Menu& src) = delete;
	~Menu();
	std::pair<int, int> renderScreen(t_data* data);
};

#endif /* menu_hpp */