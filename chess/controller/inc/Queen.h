#ifndef QUEEN_GUARD
#define QUEEN_GUARD

#include "Piece.h"

class Queen: public Piece{
public:
	//Constructor
	Queen(){}
	
	//Destructor
	~Queen(){}
	
	/**
	 * Called when the piece is selected
	 */
	void selectPiece(){}
	
	/**
	 * Called after piece is selected
	 * Determines if move is valid
	 */
	 int selectCell(){return 1;}
	 
	 int getRow(){return 1;}
	 
	 int getCol(){return 1;}
	 
	 int getActive(){return 1;}
	 
	 int getSelected(){return 1;}
	
};

#endif
