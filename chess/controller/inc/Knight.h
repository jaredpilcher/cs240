#ifndef KNIGHT_GUARD
#define KNIGHT_GUARD

#include "Piece.h"

class Knight: public Piece{
public:
	//Constructor
	Knight(int _row, int _col, int color, IChessView * _view, 
				Board* _board, ImageName type);
	
	//Destructor
	~Knight(){}
	
	/**
	 * Called when the piece is selected
	 */
	list<square> selectPiece();
	
	 /**
	 * Retrieves all possible moves without checking for check
	 */
	void getPossibleMoves(list<square>& moves);
	 
private:
	 
	 /**
	  * Returns a list of all valid moves
	  */
	 void getMoves(list<square>& moves);
	 
	 /**
	  * appends valid squares in L direction
	  */
	 void getLSquares(list<square>& moves);
	
	 
	
};

#endif
