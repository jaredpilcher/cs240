#ifndef KING_GUARD
#define KING_GUARD

#include "Piece.h"

class King: public Piece{
public:
	//Constructor
	King(int _row, int _col, int color, IChessView * _view, Board* _board);
	
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
	 bool selectCell(int row, int col){return 1;}
	
	/**
	  * Moves the piece from current location to location given
	  */
	 virtual bool movePiece(int _row, int _col);
	
};

#endif
