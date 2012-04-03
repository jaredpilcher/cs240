#include "Bishop.h"
#include "Board.h"

//Constructor
Bishop::Bishop(int _row, int _col, int _color, 
		IChessView * _view, Board* _board):
		Piece(_row,_col,_color,_view,_board){
	if(color == WHITE){
		view->PlacePiece(_row,_col,W_BISHOP);
	}else{
		view->PlacePiece(_row,_col,B_BISHOP);
	}
}

/**
 * Moves the piece from current location to location given
 */
bool Bishop::movePiece(int _row, int _col){
	return true;
}
