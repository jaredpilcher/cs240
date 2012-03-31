#ifndef BISHOP_GUARD
#define BISHOP_GUARD

#include "Piece.h"

class Bishop: public Piece{
public:
	//Constructor
	Bishop(int _row, int _col, int color, IChessView * _view);
	
	//Destructor
	~Bishop(){}
	
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
