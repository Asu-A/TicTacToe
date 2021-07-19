//
//  TicTacToe.hpp
//  XO
//
//  Created by Frenica Torn on 7/16/21.
//  Copyright � 2021 Frenica Torn. All rights reserved.
//

#ifndef tictactoe_hpp
#define tictactoe_hpp
#define NOMINMAX

#include <vector>
#include <unistd.h>
//#include <windows.h>
#include <SFML/Graphics.hpp>

using namespace sf;

typedef struct  s_data {
	Texture yesButtonTxt;
	Texture noButtonTxt;
	Texture backgroundTxt;
	Texture playButtonTxt;
	Texture cellX;
	Texture cellO;
	Texture emptyCell;
	Texture oWins;
	Texture xWins;
	Texture tie;
}				t_data;

#endif /* tictactoe_hpp */