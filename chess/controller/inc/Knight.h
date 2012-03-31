#ifndef KNIGHT_GUARD
#define KNIGHT_GUARD

#include "Piece.h"

class Knight: public Piece{
public:
	//Constructor
	Knight(int _row, int _col, int color, IChessView * _view);
	
	//Destructor
	~Knight(){}
	
	/**
	 * Called when the piece is selected
	 */
	list<square> selectPiece(){}
	
	/**
	 * Called after piece is selected
	 * Determines if move is valid
	 */
	 int selectCell(int row, int col){return 1;}
	 
	
};

#endif
