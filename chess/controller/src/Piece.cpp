#include "Piece.h"
#include "Board.h"

Piece::Piece(int _row, int _col, int _color, IChessView * _view):
		row(_row),col(_col),color(_color),view(_view),selected(0){}

int Piece::getRow(){
	return row;
}

int Piece::getCol(){
	return col;
}

int Piece::getActive(){
	return active;
}

int Piece::getSelected(){
	return selected;
}
