#ifndef BISHOP_GUARD
#define BISHOP_GUARD

#include "Piece.h"

class Bishop: public Piece{
public:
	//Constructor
	Bishop(){}
	
	//Destructor
	~Bishop(){}
	
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
