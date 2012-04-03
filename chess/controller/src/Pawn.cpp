#include "Pawn.h"
#include "Board.h"


//Constructor
Pawn::Pawn(int _row, int _col, int _color, 
		IChessView * _view, Board* _board):
		Piece(_row,_col,_color,_view,_board), first_move(true){
	if(color == WHITE){
		view->PlacePiece(_row,_col,W_PAWN);
	}else{
		view->PlacePiece(_row,_col,B_PAWN);
	}
}

list<square> Pawn::selectPiece(){
	list<square> moves;
	if(active){
		selected = true;
		getMoves(moves);
	}
	return moves;
}

void Pawn::getMoves(list<square>& moves){
	getDiagonalSquares(moves);
	getStraightSquares(moves);
}

void Pawn::getDiagonalSquares(list<square>& moves){
	if(color==WHITE){
		if(board->canDestroy(row-1, col-1)){
			moves.push_front((square){row-1,col-1});
		}
		if(board->canDestroy(row-1, col+1)){
			moves.push_front((square){row-1,col+1});
		}
	}else{
		if(board->canDestroy(row+1, col+1)){
			moves.push_front((square){row+1,col+1});
		}
		if(board->canDestroy(row+1, col-1)){
			moves.push_front((square){row+1,col-1});
		}
	}
}
	
void Pawn::getStraightSquares(list<square>& moves){
	if(color==WHITE){
		if(first_move){
			if(!board->isObject(row-1,col)){
				moves.push_front((square){row-1,col});
				if(!board->isObject(row-2,col)){
					moves.push_front((square){row-2,col});
				}
			}
		}else{
			if(!board->isObject(row-1,col)){
				moves.push_front((square){row-1,col});
			}
		}
	}else{
		if(first_move){
			if(!board->isObject(row+1,col)){
				moves.push_front((square){row+1,col});
				if(!board->isObject(row+2,col)){
					moves.push_front((square){row+2,col});
				}
			}
		}else{
			if(!board->isObject(row+1,col)){
				moves.push_front((square){row+1,col});
			}
		}
	}
}


/**
 * Called after piece is selected
 * Determines if move is valid
 */
bool Pawn::selectCell(int _row, int _col){
	//change first_time
	if(active && isValidMove(_row,_col)){
		movePiece(_row,_col);
		first_move=0;
		return true;
	}
	return false;

}

bool Pawn::isValidMove(int _row,int _col){
	list<square> moves;
	getMoves(moves);
	return isMove(moves,_row,_col);
}

bool Pawn::isMove(list<square>& moves, int _row, int _col){
	list<square>::iterator it;
	for(it = moves.begin();it!=moves.end();it++){
		if((*it).row==_row && (*it).col==_col){
			return true;
		}
	}
	return false;
}

bool Pawn::movePiece(int _row, int _col){
	Piece* destroyed_piece = board->getPiece(_row, _col);
	if(destroyed_piece != NULL){
		g_debug("Piece Destroyed!");
		destroyed_piece->destroyObject();
	}
	if(color == WHITE){
		view->PlacePiece(_row,_col,W_PAWN);
	}else{
		view->PlacePiece(_row,_col,B_PAWN);
	}
	view->ClearPiece(row,col);
	row = _row;
	col = _col;
}
