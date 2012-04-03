#ifndef PIECE_GUARD
#define PIECE_GUARD

#include "IChessView.h"
#include "ChessGuiDefines.h"
#include "ChessView.h"
#include <list>
#include <iostream>
using namespace std;
#define WHITE 0
#define BLACK 1

struct square{
	int row;
	int col;
};

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
	int row;
	int col;
	bool active;
	bool selected;
	int color;
	Board * board;
	IChessView * view;
	
public:
	
	Piece(int _row, int _col, int _color, 
			IChessView * _view, Board* _board);

	/**
	 * Called when the piece is selected
	 */
	virtual list<square> selectPiece()=0;
	
	/**
	 * Called after piece is selected
	 * Determines if move is valid
	 */
	 virtual bool selectCell(int _row, int _col)=0;
	 
	 /**
	  * Moves the piece from current location to location given
	  */
	 virtual bool movePiece(int _row, int _col)=0;
	 
	 virtual int getRow();
	 
	 virtual int getCol();
	 
	 virtual bool isActive();
	 
	 virtual bool isSelected();
	 
	 virtual bool setSelected(bool _selected);
	 
	 virtual bool setActive(bool _active);
	 
	 virtual bool destroyObject();
	 
};

#endif
