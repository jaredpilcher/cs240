#ifndef ROOK_GUARD
#define ROOK_GUARD

#include "Piece.h"

class Rook: public Piece{
public:
	//Constructor
	Rook(int _row, int _col, int color, IChessView * _view, 
				Board* _board, ImageName type);
	
	//Destructor
	~Rook(){}
	
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
	  * appends valid squares in row and column 
	  */
	 void getStraightSquares(list<square>& moves);
	
	 
	
};

#endif
