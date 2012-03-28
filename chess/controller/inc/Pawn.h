#ifndef PAWN_GUARD
#define PAWN_GUARD

#include "Piece.h"

class Pawn: public Piece{
public:
	//Constructor
	Pawn(){}
	
	//Destructor
	~Pawn(){}
	
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
