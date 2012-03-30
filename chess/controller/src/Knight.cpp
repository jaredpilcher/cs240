#include "Knight.h"

//Constructor
Knight::Knight(int _x, int _y, int _color, IChessView * _view){
	x = _x;
	y = _y;
	color = _color;
	view = _view;
	if(color == WHITE){
		view->PlacePiece(_x,_y,W_KNIGHT);
	}else{
		view->PlacePiece(_x,_y,B_KNIGHT);
	}
}
