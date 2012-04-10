#ifndef PIECE_GUARD
#define PIECE_GUARD

#include "IChessView.h"
#include "ChessGuiDefines.h"
#include "ChessView.h"
#include "UnitTest.h"
#include <list>
#include <iostream>
#include <time.h>

using namespace std;
#define WHITE 0
#define BLACK 1

struct square{
	int row;
	int col;
};

class Board;
class ChessView;

/**
 * Base class for pieces
 */
class Piece{
protected:
	int row;
	int col;
	bool active;
	bool selected;
	int color;
	Board * board;
	IChessView * view;
	ImageName type;
	
public:
	
	Piece(int _row, int _col, int _color, 
			IChessView * _view, Board* _board, ImageName _type);

	/**
	 * Called when the piece is selected
	 */
	virtual list<square> selectPiece()=0;
	
		/**
	 * Called after piece is selected
	 * Determines if move is valid
	 */
	virtual bool selectCell(int _row, int _col);
	
	virtual int getRow();
	 
	 virtual int getCol();
	 
	 virtual ImageName getType();
	 
	 virtual bool isActive();
	 
	 virtual bool isSelected();
	 
	 virtual bool setSelected(bool _selected);
	 
	 virtual bool setActive(bool _active);
	 
	 /**
	  * Sets inactive and places off of board
	  */
	 virtual bool destroyObject();
	 
	 /**
	 * Determines if a given square is a valid move
	 */
	virtual bool isValidMove(int _row,int _col);
	
	/**
	 * Determines if move is possibly valid (without checking for check)
	 */
	bool isValidPossibleMove(int _row,int _col);
	
	/**
	 * Retrieves all possible moves (checking for check)
	 */
	 virtual void getMoves(list<square>& moves)=0;	 
     
	 
protected:

	/**
	 * Determines if the given row and column are on the board
	 */
	 bool inBoard(int _row, int _col);

	   /**
	  * Moves the piece and destroys the object in that square
	  * if necessary
	  */
	 virtual bool movePiece(int _row, int _col);
	 
	 /**
	  * Apends all of the valid moves in the up direction to moves list
	  */
	 virtual void getUpSquares(list<square>& moves);
	 
	 /**
	  * Apends all of the valid moves in the down 
	  * direction to mvoes list
	  */
	 virtual void getDownSquares(list<square>& moves);
	 
	 /**
	  * Apends all of the valid moves in the right 
	  * direction to mvoes list
	  */
	 virtual void getRightSquares(list<square>& moves);
	 
	  /**
	  * Apends all of the valid moves in the left 
	  * direction to mvoes list
	  */
	 virtual void getLeftSquares(list<square>& moves);
	 
	  /**
	  * Apends all of the valid moves in the up-left 
	  * direction to mvoes list
	  */
	 virtual void getUpLeftSquares(list<square>& moves);
	 
	  /**
	  * Apends all of the valid moves in the up-right 
	  * direction to mvoes list
	  */
	 virtual void getUpRightSquares(list<square>& moves);
	 
	  /**
	  * Apends all of the valid moves in the down-left 
	  * direction to mvoes list
	  */
	 virtual void getDownLeftSquares(list<square>& moves);
	 
	  /**
	  * Apends all of the valid moves in the down-right 
	  * direction to mvoes list
	  */
	 virtual void getDownRightSquares(list<square>& moves);
	 
	 /**
	  * Determines if a move is possible
	  * Either
	  *   1.)not an object
	  *   2.)opponent's piece
	  */	 
	 virtual bool isPossibleMove(int _row, int _col);
	
	 
	 /**
	  * Determines if the row and column passed in is a possible move
	  * for the current piece in the moves list<square>
	  */
	 virtual bool isMove(list<square>& moves, int _row, int _col);
	

	 /**
	 * Removes all squares that place King in check
	 */
	 void removeCheck(list<square>& moves);
	 
	 /**
	 * Retrieves all possible moves without checking for check
	 */
	 virtual void getPossibleMoves(list<square>& moves)=0;
	 
	 /**
	  * determines if all of the moves are on the board
	  */
	 bool checkMoves(list<square>& moves);
};

#endif
