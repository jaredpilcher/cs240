#include "Move.h"
#include "Piece.h"


Move::Move():valid_move(true){}

Move::~Move(){}

void Move::setPrevPiece(PieceStruct _prev_piece){
	prev_piece = _prev_piece;
}

void Move::setAfterPiece(PieceStruct _after_piece){
	after_piece= _after_piece;
}

void Move::setDestroyedPiece(PieceStruct _destroyed_piece){
	destroyed_piece = _destroyed_piece;
}

PieceStruct Move::getPrevPiece(){
	return prev_piece;
}

PieceStruct Move::getAfterPiece(){
	return after_piece;
}

PieceStruct Move::getDestroyedPiece(){
	return destroyed_piece;
}

void Move::setInvalidMove(){
	valid_move = false;
}

bool Move::isValidMove(){
	return valid_move;
}

void Move::setValidMove(){
	valid_move = true;
}

void Move::clear(){
	clearPiece(prev_piece);
	clearPiece(after_piece);
	clearPiece(destroyed_piece);
}

void Move::clearPiece(PieceStruct& piece){
	piece.row = -1;
	piece.col = -1;
	piece.active = false;
	piece.selected = false;
	piece.color = 0;
	piece.type = NO_IMAGE;
}

void Move::clearDestroyed(){
	clearPiece(destroyed_piece);
}

void Move::print(){
	cout << "Prev_Piece: row: " << prev_piece.row << " col: " << prev_piece.col
		<< " active: " << prev_piece.active << " selected: " << prev_piece.selected	
		<< " color: " << prev_piece.color << endl;
		
	cout << "After_Piece: row: " << after_piece.row << " col: " << after_piece.col
		<< " active: " << after_piece.active << " selected: " << after_piece.selected	
		<< " color: " << after_piece.color << endl;
		
	cout << "Destroyed_Piece: row: " << destroyed_piece.row << " col: " << destroyed_piece.col
		<< " active: " << destroyed_piece.active << " selected: " << destroyed_piece.selected	
		<< " color: " << destroyed_piece.color << endl;
}
