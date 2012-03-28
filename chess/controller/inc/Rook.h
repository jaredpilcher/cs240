#ifndef ROOK_GUARD
#define ROOK_GUARD

#include "Piece.h"

class Rook: public Piece{
public:
	//Constructor
	Rook(){}
	
	//Destructor
	~Rook(){}
	
	/**
	 * Called when the piece is selected
	 */
	void selectPiece(){}
	
	/**
	 * Called after piece is selected
	 * Determines if move is valid
	 */
	 int selectCell(){}
	 
	 int getRow(){}
	 
	 int getCol(){}
	 
	 int getActive(){}
	 
	 int getSelected(){}
	
};

#endif
