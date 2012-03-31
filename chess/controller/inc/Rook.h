#ifndef ROOK_GUARD
#define ROOK_GUARD

#include "Piece.h"

class Rook: public Piece{
public:
	//Constructor
	Rook(int _row, int _col, int color, IChessView * _view);
	
	//Destructor
	~Rook(){}
	
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
