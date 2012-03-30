#ifndef PIECE_GUARD
#define PIECE_GUARD

#include "IChessView.h"
#include "ChessGuiDefines.h"
#include "ChessView.h"
#define WHITE 0
#define BLACK 1

//Enum for subclasses to keep track of which type they are
//Unsure if needed. Add if necessary
enum pieceType { pawn, knight, rook, bishop, queen, king};

class Board;
class ChessView;

/**
 * Base class for pieces
 */
class Piece{
protected:
	int x;
	int y;
	int active;
	int selected;
	int color;
	Board * board;
	IChessView * view;
public:
	

	/**
	 * Called when the piece is selected
	 */
	virtual void selectPiece() = 0;
	
	/**
	 * Called after piece is selected
	 * Determines if move is valid
	 */
	 virtual int selectCell() = 0;
	 
	 virtual int getRow() = 0;
	 
	 virtual int getCol() = 0;
	 
	 virtual int getActive() = 0;
	 
	 virtual int getSelected() = 0;
};

#endif
