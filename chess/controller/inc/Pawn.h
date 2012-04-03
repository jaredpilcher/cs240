#ifndef PAWN_GUARD
#define PAWN_GUARD

#include "Piece.h"

class Pawn: public Piece{
	bool first_move;
public:
	//Constructor
	Pawn(int _row, int _col, int color, IChessView * _view, Board* _board);
	
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
	 bool selectCell(int _row, int _col);
	 
private:
	 
	 /**
	  * Moves the piece from current location to location given
	  */
	 bool movePiece(int _row, int _col);
	 
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
	 
	 /**
	  * determines if a square is a valid move for this piece
	  */
	 bool isValidMove(int _row,int _col);

	 /**
	  * determines if move exists in a list of moves given
	  */
	 bool isMove(list<square>& moves, int _row, int _col);
	 
	
};

#endif
