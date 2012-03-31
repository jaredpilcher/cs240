#ifndef QUEEN_GUARD
#define QUEEN_GUARD

#include "Piece.h"

class Queen: public Piece{
public:
	//Constructor
	Queen(int _row, int _col, int color, IChessView * _view);
	
	//Destructor
	~Queen(){}
	
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
