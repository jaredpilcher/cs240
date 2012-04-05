#include "Bishop.h"
#include "Board.h"


//Constructor
Bishop::Bishop(int _row, int _col, int _color, 
		IChessView * _view, Board* _board, ImageName _type):
		Piece(_row,_col,_color,_view,_board,_type){//, first_move(true){
	if(color == WHITE){
		view->PlacePiece(_row,_col,W_BISHOP);
	}else{
		view->PlacePiece(_row,_col,B_BISHOP);
	}
}

list<square> Bishop::selectPiece(){
	list<square> moves;
	if(active){
		selected = true;
		getMoves(moves);
	}
	return moves;
}


void Bishop::getMoves(list<square>& moves){
	getPossibleMoves(moves);
	removeCheck(moves);
}

void Bishop::getPossibleMoves(list<square>& moves){
	getDiagonalSquares(moves);
}

void Bishop::getDiagonalSquares(list<square>& moves){
	getUpLeftSquares(moves);
	getUpRightSquares(moves);
	getDownLeftSquares(moves);
	getDownRightSquares(moves);	
}
