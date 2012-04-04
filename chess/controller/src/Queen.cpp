#include "Queen.h"
#include "Board.h"


//Constructor
Queen::Queen(int _row, int _col, int _color, 
		IChessView * _view, Board* _board):
		Piece(_row,_col,_color,_view,_board){//, first_move(true){
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
	//getStraightSquares(moves);
}

void Queen::getDiagonalSquares(list<square>& moves){
	//UP->LEFT
	int temp_row=row-1;
	int temp_col=col-1;
	while(temp_row>=0 && temp_col>=0){
		if(isPossibleMove(temp_row,temp_col)){
			moves.push_front((square){temp_row,temp_col});
			if(board->canDestroy(temp_row,temp_col)){
				break;
			}
		}else{
			break;
		}
		temp_row-=1;
		temp_col-=1;
	}
	
	//UP->RIGHT
	temp_row=row-1;
	temp_col=col+1;
	while(temp_row>=0 && temp_col<=7){
		if(isPossibleMove(temp_row,temp_col)){
			moves.push_front((square){temp_row,temp_col});
			if(board->canDestroy(temp_row,temp_col)){
				break;
			}
		}else{
			break;
		}
		temp_row-=1;
		temp_col+=1;
	}
		
	//getDiagonal(moves,1,1,UP,LEFT);
	//getDiagonal(moves,1,6,UP,RIGHT);

	/*if(board->canDestroy(row-1, col-1)){
		moves.push_front((square){row-1,col-1});
	}
	if(board->canDestroy(row-1, col+1)){
		moves.push_front((square){row-1,col+1});
	}*/
}

bool Queen::isPossibleMove(int _row, int _col){
	return(!board->isObject(_row,_col) || board->canDestroy(_row,_col));
}
	
/*void Queen::getStraightSquares(list<square>& moves){
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
}*/


/**
 * Called after piece is selected
 * Determines if move is valid
 */
bool Queen::selectCell(int _row, int _col){
	//change first_time
	if(active && isValidMove(_row,_col)){
		movePiece(_row,_col);
		//first_move=0;
		return true;
	}
	return false;

}

bool Queen::isValidMove(int _row,int _col){
	list<square> moves;
	getMoves(moves);
	return isMove(moves,_row,_col);
}

bool Queen::isMove(list<square>& moves, int _row, int _col){
	list<square>::iterator it;
	for(it = moves.begin();it!=moves.end();it++){
		if((*it).row==_row && (*it).col==_col){
			return true;
		}
	}
	return false;
}

bool Queen::movePiece(int _row, int _col){
	Piece* destroyed_piece = board->getPiece(_row, _col);
	if(destroyed_piece != NULL){
		g_debug("Piece Destroyed!");
		destroyed_piece->destroyObject();
	}
	if(color == WHITE){
		view->PlacePiece(_row,_col,W_QUEEN);
	}else{
		view->PlacePiece(_row,_col,B_QUEEN);
	}
	view->ClearPiece(row,col);
	row = _row;
	col = _col;
}
