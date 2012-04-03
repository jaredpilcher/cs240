#include "King.h"
#include "Board.h"

//Constructor
King::King(int _row, int _col, int _color, 
		IChessView * _view, Board* _board):
		Piece(_row,_col,_color,_view,_board){
	if(color == WHITE){
		view->PlacePiece(_row,_col,W_KING);
	}else{
		view->PlacePiece(_row,_col,B_KING);
	}
}

/**
 * Moves the piece from current location to location given
 */
bool King::movePiece(int _row, int _col){
	return true;
}
