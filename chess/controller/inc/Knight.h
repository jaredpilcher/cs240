#ifndef KNIGHT_GUARD
#define KNIGHT_GUARD

#include "Piece.h"

class Knight: public Piece{
public:
	//Constructor
	Knight(int _row, int _col, int color, IChessView * _view, Board* _board);
	
	//Destructor
	~Knight(){}
	
	/**
	 * Called when the piece is selected
	 */
	list<square> selectPiece(){}
	
	/**
	 * Called after piece is selected
	 * Determines if move is valid
	 */
	 bool selectCell(int row, int col){return 1;}
	 
	/**
	  * Moves the piece from current location to location given
	  */
	 virtual bool movePiece(int _row, int _col);
	
};

#endif
