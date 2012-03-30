#ifndef KNIGHT_GUARD
#define KNIGHT_GUARD

#include "Piece.h"

class Knight: public Piece{
public:
	//Constructor
	Knight(int _x, int _y, int color, IChessView * _view);
	
	//Destructor
	~Knight(){}
	
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
