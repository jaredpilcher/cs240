#ifndef PIECE_GUARD
#define PIECE_GUARD

enum pieceType { pawn, knight, rook, bishop, queen, king};

class Board;

/**
 * Base class for pieces
 */
class Piece{
	int row;
	int col;
	int type;
	int active;
	int selected;
	Board * board;
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
