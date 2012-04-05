#ifndef PAWN_GUARD
#define PAWN_GUARD

#include "Piece.h"

class Pawn: public Piece{
	bool first_move;
public:
	//Constructor
	Pawn(int _row, int _col, int color, IChessView * _view, 
				Board* _board, ImageName type);
	
	//Destructor
	~Pawn(){}
	
	/**
	 * Called when the piece is selected
	 */
	list<square> selectPiece();
	
	/**
	 * Retrieves all possible moves without checking for check
	 */
	void getPossibleMoves(list<square>& moves);

	 
private:
	 
	 /**
	  * Returns a list of all valid moves
	  */
	 void getMoves(list<square>& moves);
	 
	 /**
	  * appends valid squares in diagonal direction
	  */
	 void getDiagonalSquares(list<square>& moves);
	 
	 /**
	  * appends valid squares in row and column 
	  */
	 void getStraightSquares(list<square>& moves);
	 
	 bool movePiece(int _row, int _col);

	 
	
};

#endif
