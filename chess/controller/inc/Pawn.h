#ifndef PAWN_GUARD
#define PAWN_GUARD
//START HERE: 3-29-12
//SEG FAULTS
//INCLUDE THESE IN MAKE FILE
#include "Piece.h"
#include "ChessGuiDefines.h"
#include "ChessView.h"

class Pawn: public Piece{
public:
	//Constructor
	Pawn(int _x, int _y, int color, IChessView * _view);
	
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
