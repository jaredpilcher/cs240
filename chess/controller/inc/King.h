#ifndef KING_GUARD
#define KING_GUARD

#include "Piece.h"

class King: public Piece{
public:
	//Constructor
	King(int _row, int _col, int color, IChessView * _view, 
				Board* _board, ImageName type);
	
	//Destructor
	~King(){}
	
	/**
	 * Called when the piece is selected
	 */
	list<square> selectPiece();
	 
private:
	 
	 /**
	  * Appends to the list all valid moves
	  */
	 void getMoves(list<square>& moves);
	 
	 /**
	  * Append to the list all squares surrounding piece
	  */
	  void getImmediateSquares(list<square>& moves);
	
	 
	
};

#endif
