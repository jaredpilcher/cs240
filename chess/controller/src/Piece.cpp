#include "Piece.h"
#include "Board.h"

Piece::Piece(int _row, int _col, int _color, 
			IChessView * _view, Board* _board):
		row(_row),col(_col),color(_color),view(_view),selected(false),
		active(true), board(_board){}

int Piece::getRow(){
	return row;
}

int Piece::getCol(){
	return col;
}

bool Piece::isActive(){
	return active;
}

bool Piece::isSelected(){
	return selected;
}

bool Piece::setSelected(bool _selected){
	selected = _selected;
}

bool Piece::setActive(bool _active){
	active = _active;
}

bool Piece::destroyObject(){
	active = false;
	row = -1;
	col = -1;
}
