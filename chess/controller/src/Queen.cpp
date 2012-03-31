#include "Queen.h"
#include "Board.h"


//Constructor
Queen::Queen(int _row, int _col, int _color, IChessView * _view):
		Piece(_row,_col,_color,_view){
	row = _row;
	col = _col;
	color = _color;
	view = _view;
	if(color == WHITE){
		view->PlacePiece(_row,_col,W_QUEEN);
	}else{
		view->PlacePiece(_row,_col,B_QUEEN);
	}
}
