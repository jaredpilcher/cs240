#include "Rook.h"
#include "Board.h"


//Constructor
Rook::Rook(int _row, int _col, int _color, 
		IChessView * _view, Board* _board):
		Piece(_row,_col,_color,_view,_board){
	if(color == WHITE){
		view->PlacePiece(_row,_col,W_ROOK);
	}else{
		view->PlacePiece(_row,_col,B_ROOK);
	}
}

/**
 * Moves the piece from current location to location given
 */
bool Rook::movePiece(int _row, int _col){
	return true;
}
