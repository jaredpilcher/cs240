#include "Pawn.h"
#include "Board.h"


//Constructor
Pawn::Pawn(int _row, int _col, int _color, IChessView * _view):
		Piece(_row,_col,_color,_view), first_time(1){
	if(color == WHITE){
		view->PlacePiece(_row,_col,W_PAWN);
	}else{
		view->PlacePiece(_row,_col,B_PAWN);
	}
}

list<square> Pawn::selectPiece(){
	selected = 1;
	list<square> temp_list;
	if(color==WHITE){
		if(first_time){
			temp_list.push_front((square){row-2,col});
		}else{
			temp_list.push_front((square){row-1,col});
		}
	}else{
		if(first_time){
			temp_list.push_front((square){row+2,col});
		}else{
			temp_list.push_front((square){row+1,col});
		}
	}
	return temp_list;
}

/**
 * Called after piece is selected
 * Determines if move is valid
 */
int Pawn::selectCell(int row, int col){
	//change first_time
	
	

}
