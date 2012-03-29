#include "Board.h"


//Default Constructor
Board::Board(): turn(PLAYER1), view(NULL){
	initializePieces();
}

//Destructor
Board::~Board(){
	
}
	
//Determines if the selected square is valid:
//Either:
// 1.)Square contains the current player's piece
//Or:
// 2.)Square selected after 1.) is complete
//Notifies piece that it has been selected
//Asks piece for possible moves and updates highlighting accordingly
//On next cell selection, asks piece if this move is valid
//updates highlighting after move
//Updates player's turn
//Notifies controller if move is made (and which one)
	//Creates a move object and passes it back
	//includes pieces destroyed
void Board::handleSelect(int row, int col){

}

//Uses the passed in Move object to move the pieces back
//Activates pieces if necessary
void Board::undoMove(Move move){
	
}

//Resets all pieces to original positions
void Board::resetBoard(){
	
}

//Highlights the given square
void Board::lightSquare(int row, int col){
	
}

//Unhighlight all squares
void Board::unlightSquares(){
	
}

//Checks Checkmate or stalemate
void Board::checkEOG(){
	
}

//Checks validity of move (Checkmate)
void Board::checkMoveValid(Piece* piece, int from_row, int from_col,
					int to_row, int to_col){
						
}

//Initializes the positions of all pieces on board
void Board::initializePieces(){
	initializeSide(pieces1, WHITE);
	initializeSide(pieces2, BLACK);
}

/**
 * Initializes the pieces passed in
 */
void Board::initializeSide(Piece** pieces, int color){
	int i = 0;
	for(;i<8;++i){
		if(color==WHITE){
			pieces[i] = new Pawn(i,1,WHITE, view);
		}else{
			pieces[i] = new Pawn(i,1,BLACK, view);
		}
	}
	
}

//Sets the view that we are working with
void Board::setView(IChessView * _view){
	this->view= _view;
}
