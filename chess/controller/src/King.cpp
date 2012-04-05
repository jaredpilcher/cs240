#include "King.h"
#include "Board.h"


//Constructor
King::King(int _row, int _col, int _color, 
		IChessView * _view, Board* _board, ImageName _type):
		Piece(_row,_col,_color,_view,_board,_type){//, first_move(true){
	if(color == WHITE){
		view->PlacePiece(_row,_col,W_KING);
	}else{
		view->PlacePiece(_row,_col,B_KING);
	}
}

list<square> King::selectPiece(){
	list<square> moves;
	if(active){
		selected = true;
		getMoves(moves);
	}
	return moves;
}

void King::getMoves(list<square>& moves){
	getPossibleMoves(moves);
	removeCheck(moves);
}

void King::getPossibleMoves(list<square>& moves){
	getImmediateSquares(moves);
}

void King::getImmediateSquares(list<square>& moves){
	//UP->LEFT
	if(!board->correctPlayer(row-1,col-1)){
			moves.push_front((square){row-1,col-1});
	}
	
	//UP->RIGHT
	if(!board->correctPlayer(row-1,col+1)){
			moves.push_front((square){row-1,col+1});
	}
	
	//DOWN->LEFT
	if(!board->correctPlayer(row+1,col-1)){
			moves.push_front((square){row+1,col-1});
	}
	
	//DOWN->LEFT
	if(!board->correctPlayer(row+1,col+1)){
			moves.push_front((square){row+1,col+1});
	}
	
	//UP
	if(!board->correctPlayer(row-1,col)){
			moves.push_front((square){row-1,col});
	}
	
	//DOWN
	if(!board->correctPlayer(row+1,col)){
			moves.push_front((square){row+1,col});
	}
	
	//LEFT
	if(!board->correctPlayer(row,col-1)){
			moves.push_front((square){row,col-1});
	}
	
	//RIGHT
	if(!board->correctPlayer(row,col+1)){
			moves.push_front((square){row,col+1});
	}
}
