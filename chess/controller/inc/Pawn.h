#ifndef PAWN_GUARD
#define PAWN_GUARD

#include "Piece.h"

class Pawn: public Piece{
	int first_time;
public:
	//Constructor
	Pawn(int _row, int _col, int color, IChessView * _view);
	
	//Destructor
	~Pawn(){}
	
	/**
	 * Called when the piece is selected
	 */
	list<square> selectPiece();
	
	/**
	 * Called after piece is selected
	 * Determines if move is valid
	 */
	 int selectCell(int row, int col);
	
};

#endif
