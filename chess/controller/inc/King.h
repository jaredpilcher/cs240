#ifndef KING_GUARD
#define KING_GUARD

#include "Piece.h"

class King: public Piece{
public:
	//Constructor
	King(int _x, int _y, int color, IChessView * _view);
	
	//Destructor
	~King(){}
	
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
