#include "Piece.h"
#include "Board.h"

Piece::Piece(int _row, int _col, int _color, 
			IChessView * _view, Board* _board, ImageName _type):
		row(_row),col(_col),color(_color),view(_view),selected(false),
		active(true), board(_board), type(_type){}

int Piece::getRow(){
	return row;
}

int Piece::getCol(){
	return col;
}

bool Piece::isActive(){
	return active;
}

bool Piece::isSelected(){
	return selected;
}

bool Piece::setSelected(bool _selected){
	selected = _selected;
}

bool Piece::setActive(bool _active){
	active = _active;
}

bool Piece::destroyObject(){
	active = false;
	row = -1;
	col = -1;
}

void Piece::getUpSquares(list<square>& moves){
	int temp_row=row-1;
	while(temp_row>=0){
		if(isPossibleMove(temp_row,col)){
			moves.push_front((square){temp_row,col});
			if(board->canDestroy(temp_row,col)){
				break;
			}
		}else{
			break;
		}
		temp_row-=1;
	}
}

/**
* Apends all of the valid moves in the down 
* direction to mvoes list
*/
void Piece::getDownSquares(list<square>& moves){
	int temp_row=row+1;
	while(temp_row<=7){
		if(isPossibleMove(temp_row,col)){
			moves.push_front((square){temp_row,col});
			if(board->canDestroy(temp_row,col)){
				break;
			}
		}else{
			break;
		}
		temp_row+=1;
	}
}
 
/**
* Apends all of the valid moves in the right 
* direction to mvoes list
*/
void Piece::getRightSquares(list<square>& moves){
	int temp_col=col-1;
	while(temp_col>=0){
		if(isPossibleMove(row,temp_col)){
			moves.push_front((square){row,temp_col});
			if(board->canDestroy(row,temp_col)){
				break;
			}
		}else{
			break;
		}
		temp_col-=1;
	}
}

/**
* Apends all of the valid moves in the left 
* direction to mvoes list
*/
void Piece::getLeftSquares(list<square>& moves){
	int temp_col=col+1;
	while(temp_col<=7){
		if(isPossibleMove(row,temp_col)){
			moves.push_front((square){row,temp_col});
			if(board->canDestroy(row,temp_col)){
				break;
			}
		}else{
			break;
		}
		temp_col+=1;
	}
}

/**
* Apends all of the valid moves in the up-left 
* direction to mvoes list
*/
void Piece::getUpLeftSquares(list<square>& moves){
	int temp_row=row-1;
	int temp_col=col-1;
	while(temp_row>=0 && temp_col>=0){
		if(isPossibleMove(temp_row,temp_col) ){
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
}

/**
* Apends all of the valid moves in the up-right 
* direction to mvoes list
*/
void Piece::getUpRightSquares(list<square>& moves){
	int temp_row=row-1;
	int temp_col=col+1;
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
}

/**
* Apends all of the valid moves in the down-left 
* direction to mvoes list
*/
void Piece::getDownLeftSquares(list<square>& moves){
	int temp_row=row+1;
	int temp_col=col-1;
	while(temp_row<=7 && temp_col>=0){
		if(isPossibleMove(temp_row,temp_col)){
			moves.push_front((square){temp_row,temp_col});
			if(board->canDestroy(temp_row,temp_col)){
				break;
			}
		}else{
			break;
		}
		temp_row+=1;
		temp_col-=1;
	}
}

/**
* Apends all of the valid moves in the down-right 
* direction to mvoes list
*/
void Piece::getDownRightSquares(list<square>& moves){
	int temp_row=row+1;
	int temp_col=col+1;
	while(temp_row<=7 && temp_col<=7){
		if(isPossibleMove(temp_row,temp_col)){
			moves.push_front((square){temp_row,temp_col});
			if(board->canDestroy(temp_row,temp_col)){
				break;
			}
		}else{
			break;
		}
		temp_row+=1;
		temp_col+=1;
	}
}


bool Piece::isPossibleMove(int _row, int _col){
	return(!board->isObject(_row,_col) || board->canDestroy(_row,_col));
}


bool Piece::movePiece(int _row, int _col){
	Piece* destroyed_piece = board->getPiece(_row, _col);
	if(destroyed_piece != NULL){
		g_debug("Piece Destroyed!");
		destroyed_piece->destroyObject();
	}
	if(color == WHITE){
		view->PlacePiece(_row,_col,type);
	}else{
		view->PlacePiece(_row,_col,type);
	}
	view->ClearPiece(row,col);
	row = _row;
	col = _col;
}

bool Piece::isMove(list<square>& moves, int _row, int _col){
	list<square>::iterator it;
	for(it = moves.begin();it!=moves.end();it++){
		//std::cout << "Possible move: row: " << (*it).row << " col: " << (*it).col << std::endl;
		if((*it).row==_row && (*it).col==_col){
			return true;
		}
	}
	//std::cout << "Finish searching moves of piece" << std::endl;
	return false;
}

/**
 * Called after piece is selected
 * Determines if move is valid
 */
bool Piece::selectCell(int _row, int _col){
	//change first_time
	if(active && isValidMove(_row,_col)){
		movePiece(_row,_col);
		//first_move=0;
		return true;
	}
	return false;

}

bool Piece::isValidMove(int _row,int _col){
	list<square> moves;
	getMoves(moves);
	return isMove(moves,_row,_col);
}

bool Piece::isValidPossibleMove(int _row,int _col){
	list<square> moves;
	getPossibleMoves(moves);
	if(type == W_QUEEN || type==B_QUEEN){
		//std::cout << "Determining Queen moves" << std::endl;
	}
	return isMove(moves,_row,_col);
}

/**
* Removes all squares that place King in check
*/
void Piece::removeCheck(list<square>& moves){
	//std::cout << "moves size begin: " << moves.size() << std::endl;
	int temp_row = row;
	int temp_col = col;
	Piece* destroyed_piece = NULL;
	board->switchTurns();
	list<square> temp_moves;
	list<square>::iterator it;
	for(it = moves.begin();it!=moves.end();++it){
		//if(board->isObject((*it).row,(*it).col)){
			//destroyed_piece = board->getPiece((*it).row, (*it).col);
			//if(destroyed_piece!=NULL){
			////std::cout << "destroyed piece: row: " << (*it).row << " col: " << (*it).col << std::endl;
				////destroyed_piece->destroyObject();
				//destroyed_piece->row =-1;
				//destroyed_piece->col=-1;
				//destroyed_piece->active =false;
			//}
		//}
		row = (*it).row;
		col = (*it).col;
		//std::cout << "Placing Piece at: row: " << row << " col: " << col << std::endl;
		if(!(board->inCheck())){
			//std::cout << "move doesn't cause check" << std::endl;
			temp_moves.push_front(*it);
		}
		//if(destroyed_piece!=NULL){
			//destroyed_piece->row =(*it).row;
			//destroyed_piece->col=(*it).col;
			//destroyed_piece->active =true;
		//}
	}
	moves.clear();
	moves = temp_moves;
	//std::cout << "moves size end: " << moves.size() << std::endl;
	row = temp_row;
	col = temp_col;
	board->switchTurns();
}


ImageName Piece::getType(){
	return type;
}
