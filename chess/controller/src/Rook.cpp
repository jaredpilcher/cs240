#include "Rook.h"
#include "Board.h"


//Constructor
Rook::Rook(int _row, int _col, int _color, 
		IChessView * _view, Board* _board, ImageName _type):
		Piece(_row,_col,_color,_view,_board,_type){//, first_move(true){
	if(color == WHITE){
		view->PlacePiece(_row,_col,W_ROOK);
	}else{
		view->PlacePiece(_row,_col,B_ROOK);
	}
}

list<square> Rook::selectPiece(){
	list<square> moves;
	if(active){
		selected = true;
		getMoves(moves);
	}
	return moves;
}

void Rook::getMoves(list<square>& moves){
	getPossibleMoves(moves);
	removeCheck(moves);
}

void Rook::getPossibleMoves(list<square>& moves){
	getStraightSquares(moves);
}
	
void Rook::getStraightSquares(list<square>& moves){
	getUpSquares(moves);
	getDownSquares(moves);
	getRightSquares(moves);
	getLeftSquares(moves);
}
