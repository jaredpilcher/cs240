#ifndef KING_GUARD
#define KING_GUARD

#include "Piece.h"

class King: public Piece{
public:
	//Constructor
	King(int _row, int _col, int color, IChessView * _view);
	
	//Destructor
	~King(){}
	
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
