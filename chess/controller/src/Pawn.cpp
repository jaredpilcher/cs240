#include "Pawn.h"
#include "Board.h"


//Constructor
Pawn::Pawn(int _row, int _col, int _color, 
		IChessView * _view, Board* _board, ImageName _type):
		Piece(_row,_col,_color,_view,_board,_type){
	if(_view!=NULL){
		if(color == WHITE){
			view->PlacePiece(_row,_col,W_PAWN);
		}else{
			view->PlacePiece(_row,_col,B_PAWN);
		}
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
	getPossibleMoves(moves);
	removeCheck(moves);
}

void Pawn::getPossibleMoves(list<square>& moves){
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
			if(!board->isObject(row-1,col) && inBoard(row-1,col)){
				moves.push_front((square){row-1,col});
				if(!board->isObject(row-2,col)){
					moves.push_front((square){row-2,col});
				}
			}
		}else{
			if(!board->isObject(row-1,col) && inBoard(row-1,col)){
				moves.push_front((square){row-1,col});
			}
		}
	}else{
		if(first_move){
			if(!board->isObject(row+1,col) && inBoard(row+1,col)){
				moves.push_front((square){row+1,col});
				if(!board->isObject(row+2,col)){
					moves.push_front((square){row+2,col});
				}
			}
		}else{
			if(!board->isObject(row+1,col) && inBoard(row+1,col)){
				moves.push_front((square){row+1,col});
			}
		}
	}
}

//bool Pawn::movePiece(int _row, int _col){
	//Piece* destroyed_piece = board->getPiece(_row, _col);
	//if(destroyed_piece != NULL){
		//g_debug("Piece Destroyed!");
		//destroyed_piece->destroyObject();
	//}
	//if(color == WHITE){
		//view->PlacePiece(_row,_col,type);
	//}else{
		//view->PlacePiece(_row,_col,type);
	//}
	//view->ClearPiece(row,col);
	//row = _row;
	//col = _col;
	//first_move=false;
	//return true;
//}

/**
* Test function for Pawn
*/
bool Pawn::test(ostream& os){
	list<square> moves;
	bool success = true;
	for(int i=0;i<=7;++i){
			for(int j=0;j<=7;++j){
				row = i;
				col = j;
				getMoves(moves);
				TEST(checkMoves(moves));
				moves.clear();
			}
	}
	return success;
}

//~ void Pawn::setFirstMove(){
	//~ cout << "here" << endl;
	//~ first_move=true;
//~ }
