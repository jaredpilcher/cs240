#include "Bishop.h"
#include "Board.h"

//Constructor
Bishop::Bishop(int _row, int _col, int _color, IChessView * _view):
		Piece(_row,_col,_color,_view){
	if(color == WHITE){
		view->PlacePiece(_row,_col,W_BISHOP);
	}else{
		view->PlacePiece(_row,_col,B_BISHOP);
	}
}
