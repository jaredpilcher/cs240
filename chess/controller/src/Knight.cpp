#include "Knight.h"
#include "Board.h"

//Constructor
Knight::Knight(int _row, int _col, int _color, 
		IChessView * _view, Board* _board):
		Piece(_row,_col,_color,_view,_board){
	if(color == WHITE){
		view->PlacePiece(_row,_col,W_KNIGHT);
	}else{
		view->PlacePiece(_row,_col,B_KNIGHT);
	}
}

/**
 * Moves the piece from current location to location given
 */
bool Knight::movePiece(int _row, int _col){
	return true;
}
