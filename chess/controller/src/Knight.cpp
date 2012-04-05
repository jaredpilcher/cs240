#include "Knight.h"
#include "Board.h"


//Constructor
Knight::Knight(int _row, int _col, int _color, 
		IChessView * _view, Board* _board, ImageName _type):
		Piece(_row,_col,_color,_view,_board,_type){//, first_move(true){
	if(color == WHITE){
		view->PlacePiece(_row,_col,W_KNIGHT);
	}else{
		view->PlacePiece(_row,_col,B_KNIGHT);
	}
}

list<square> Knight::selectPiece(){
	list<square> moves;
	if(active){
		selected = true;
		getMoves(moves);
	}
	return moves;
}

void Knight::getMoves(list<square>& moves){
	getPossibleMoves(moves);
	removeCheck(moves);
}

void Knight::getPossibleMoves(list<square>& moves){
	getLSquares(moves);
}

void Knight::getLSquares(list<square>& moves){
	if(row>=2 && col>=1){
		moves.push_front((square){row-2,col-1});
	}
	
	if(row>=2 && col<=6){
		moves.push_front((square){row-2,col+1});
	}
	
	if(row<=5 && col>=1){
		moves.push_front((square){row+2,col-1});
	}
	
	if(row<=5 && col<=6){
		moves.push_front((square){row+2,col+1});
	}
	
	if(row>=1 && col>=2){
		moves.push_front((square){row-1,col-2});
	}
	
	if(row<=6 && col>=2){
		moves.push_front((square){row+1,col-2});
	}
	
	if(row>=1 && col<=5){
		moves.push_front((square){row-1,col+2});
	}
	
	if(row<=6 && col<=5){
		moves.push_front((square){row+1,col+2});
	}
}
