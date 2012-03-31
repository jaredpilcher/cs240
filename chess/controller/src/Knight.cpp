#include "Knight.h"
#include "Board.h"

//Constructor
Knight::Knight(int _row, int _col, int _color, IChessView * _view):
		Piece(_row,_col,_color,_view){
	if(color == WHITE){
		view->PlacePiece(_row,_col,W_KNIGHT);
	}else{
		view->PlacePiece(_row,_col,B_KNIGHT);
	}
}
