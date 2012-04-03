#ifndef QUEEN_GUARD
#define QUEEN_GUARD

#include "Piece.h"

#define UP -1
#define DOWN 1
#define LEFT -1
#define RIGHT 1

class Queen: public Piece{
public:
	//Constructor
	Queen(int _row, int _col, int color, IChessView * _view, Board* _board);
	
	//Destructor
	~Queen(){}
	
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
	 //void getStraightSquares(list<square>& moves);
	 
	 /**
	  * determines if a square is a valid move for this piece
	  */
	 bool isValidMove(int _row,int _col);

	 /**
	  * determines if move exists in a list of moves given
	  */
	 bool isMove(list<square>& moves, int _row, int _col);
	 
	 /**
	  * Determines if a move is possible
	  * Either
	  *   1.)not an object
	  *   2.)opponent's piece
	  */
	 bool isPossibleMove(int _row, int _col);
	 
	 /**
	  * collects diagonal squares (in direction specified)
	  */
	 void getDiagonal(list<square>& moves, int row_corner, int col_corner,
		int vertical, int horizontal);
		
	/**
	 * Helper function for getDiagonal function
	 */
	bool diagonalHelper(list<square>& moves, int& row_corner, int& col_corner,
		int& vertical, int& horizontal, int& temp_row, int& temp_col);
	 
	
};

#endif
