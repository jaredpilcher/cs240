#ifndef MOVE_GUARD
#define MOVE_GUARD

#include "ChessGuiDefines.h"
#include <iostream>
using namespace std;

struct PieceStruct{
	int row;
	int col;
	bool active;
	bool selected;
	int color;
	ImageName type;
};

class Move{
	PieceStruct prev_piece;
	PieceStruct after_piece;
	PieceStruct destroyed_piece;
	bool valid_move;
public:

	Move();
	
	~Move();

	void setPrevPiece(PieceStruct prev_piece);
	
	void setAfterPiece(PieceStruct after_piece);
	
	void setDestroyedPiece(PieceStruct destroyed_piece);
	
	PieceStruct getPrevPiece();
	
	PieceStruct getAfterPiece();
	
	PieceStruct getDestroyedPiece();
	
	void setInvalidMove();
	
	bool isValidMove();
	
	void setValidMove();
	
	void clear();
	
	void clearDestroyed();
	
	void clearPiece(PieceStruct& piece);
	
	void print();
	
};

#endif
