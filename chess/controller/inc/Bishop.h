#ifndef BISHOP_GUARD
#define BISHOP_GUARD

#include "Piece.h"

class Bishop: public Piece{
public:
	//Constructor
	Bishop(int _row, int _col, int color, IChessView * _view, 
				Board* _board, ImageName type);
	
	//Destructor
	~Bishop(){}
	
	/**
	 * Called when the piece is selected
	 */
	list<square> selectPiece();
	 
private:
	 
	 /**
	  * Returns a list of all valid moves
	  */
	 void getMoves(list<square>& moves);
	 
	 /**
	  * appends valid squares in diagonal direction
	  */
	 void getDiagonalSquares(list<square>& moves);
	
	 
	
};

#endif
