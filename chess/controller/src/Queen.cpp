#include "Queen.h"
#include "Board.h"


//Constructor
Queen::Queen(int _row, int _col, int _color, 
		IChessView * _view, Board* _board, ImageName _type):
		Piece(_row,_col,_color,_view,_board,_type){//, first_move(true){
	if(color == WHITE){
		view->PlacePiece(_row,_col,W_QUEEN);
	}else{
		view->PlacePiece(_row,_col,B_QUEEN);
	}
}

list<square> Queen::selectPiece(){
	list<square> moves;
	if(active){
		selected = true;
		getMoves(moves);
	}
	return moves;
}

void Queen::getMoves(list<square>& moves){
	getDiagonalSquares(moves);
	getStraightSquares(moves);
}

void Queen::getDiagonalSquares(list<square>& moves){
	getUpLeftSquares(moves);
	getUpRightSquares(moves);
	getDownLeftSquares(moves);
	getDownRightSquares(moves);	
}
	
void Queen::getStraightSquares(list<square>& moves){
	getUpSquares(moves);
	getDownSquares(moves);
	getRightSquares(moves);
	getLeftSquares(moves);
}
