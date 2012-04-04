#include "Board.h"
#include <iostream>


//Default Constructor
Board::Board(IChessView* _view): turn(PLAYER1), view(_view), 
		prev_row(-1), prev_col(-1), prev_piece(NULL){
	this->view= _view;
	initializePieces();
}

//Destructor
Board::~Board(){
	for(int i = 0; i<PIECES_PER_SIDE; ++i){
		delete pieces1[i];
		delete pieces2[i];
	}
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
	highlightSquares(row, col);
}

void Board::highlightSquares(int row, int col){
	int temp_row = row;
	int temp_col = col;
	if(isObject(row, col)){
		g_debug("Found Piece!");
		if(sameAsLast(row, col)){
			g_debug("Same as Last!");
			unselectObjects();
			unlightSquares();
			temp_row = -1;
			temp_col = -1;
		}
		else if(correctPlayer(row, col)){
			g_debug("Correct Player!");
			Piece * temp_piece = getPiece(row, col);
			//std::cout << "temp_piece " << temp_piece << std::endl;
			unlightSquares();
			unselectObjects();
			list<square> temp_squares = temp_piece->selectPiece();
			//std::cout << "temp_squares: " << temp_squares.size() << std::endl;
			highlightList(temp_squares);
		}else{
			g_debug("Not an Object of Current Player!");
			if(isObjectSelected()){
				g_debug("Piece was selected!");
				Piece* destroyed_piece = getPiece(row, col);
				bool success_select = notifyObject(row,col);
				std::cout << "success_select: " << success_select << endl;
				if(success_select){
					switchTurns();
					if(destroyed_piece != NULL){
						destroyed_piece->destroyObject();
					}
				}
				unselectObjects();
				unlightSquares();
				temp_row = -1;
				temp_col = -1;
			}else{
				g_debug("Piece was not selected!");
				unselectObjects();
				unlightSquares();
			}
		}
	}else{
		g_debug("Not an Object!");
		if(isObjectSelected()){
			g_debug("Piece was selected!");
			bool success_select = notifyObject(row,col);
			std::cout << "success_select: " << success_select << endl;
			if(success_select){
				switchTurns();
			}
			unselectObjects();
			unlightSquares();
			temp_row = -1;
			temp_col = -1;
		}else{
			g_debug("Piece was not selected!");
			unselectObjects();
			unlightSquares();
		}
		
	}
	
	prev_row = temp_row;
	prev_col = temp_col;
	//if(isLit(row,col)){
		//g_debug("Square is lit");
		//unlightSquares();
	//}else{
		//lightSquare(row,col);
		//square temp_square;
		//temp_square.row = row;
		//temp_square.col = col;
		//lit_squares.push_front(temp_square);
	//}
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
	 view->HighlightSquare(row, col, 65535);
	 lit_squares.push_front((square){row,col});
}

//Unhighlight all squares
void Board::unlightSquares(){
	list<square>::iterator it;
	for(it = lit_squares.begin();it!=lit_squares.end();it++){
		view->UnHighlightSquare((*it).row,(*it).col);
	}
	lit_squares.clear();
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
	if(color==WHITE){
		for(;i<8;++i){
			pieces[i] = new Pawn(6,i,WHITE, view, this);
		}
	}else{
		for(;i<8;++i){
			pieces[i] = new Pawn(1,i,BLACK, view, this);
		}
	}
	
	if(color==WHITE){
		pieces[i++] = new Rook(7,0,WHITE, view, this);
		pieces[i++] = new Rook(7,7,WHITE, view, this);
	}else{
		pieces[i++] = new Rook(0,0,BLACK, view, this);
		pieces[i++] = new Rook(0,7,BLACK, view, this);
	}
	
	if(color==WHITE){
		pieces[i++] = new Knight(7,1,WHITE, view, this);
		pieces[i++] = new Knight(7,6,WHITE, view, this);
	}else{
		pieces[i++] = new Knight(0,1,BLACK, view, this);
		pieces[i++] = new Knight(0,6,BLACK, view, this);
	}
	
	if(color==WHITE){
		pieces[i++] = new Bishop(7,2,WHITE, view, this);
		pieces[i++] = new Bishop(7,5,WHITE, view, this);
	}else{
		pieces[i++] = new Bishop(0,2,BLACK, view, this);
		pieces[i++] = new Bishop(0,5,BLACK, view, this);
	}
	
	if(color==WHITE){
		pieces[i++] = new Queen(7,3,WHITE, view, this);
	}else{
		pieces[i++] = new Queen(0,3,BLACK, view, this);
	}
	
	if(color==WHITE){
		pieces[i++] = new King(7,4,WHITE, view, this);
	}else{
		pieces[i++] = new King(0,4,BLACK, view, this);
	}
	
	
	
}

bool Board::isLit(int row, int col){
	list<square>::iterator it;
	for(it = lit_squares.begin();it!=lit_squares.end();it++){
		if(((*it).row == row) && ((*it).col == col)){
			return true;
		}
	}
	return false;
}

bool Board::isObject(int row, int col){
	for(int i=0; i<PIECES_PER_SIDE;++i){
		if(pieces1[i]->getRow() == row && pieces1[i]->getCol() == col){
				return true;
		}
		if(pieces2[i]->getRow() == row && pieces2[i]->getCol() == col){
				return true;
		}
	}
	return false;
}

bool Board::sameAsLast(int row, int col){
	return row==prev_row && col==prev_col;
}

bool Board::correctPlayer(int row, int col){
	 Piece ** pieces;
	if(turn==PLAYER1){
		pieces=pieces1;
	}else{
		pieces=pieces2;
	}
	for(int i=0; i<PIECES_PER_SIDE;++i){
		if(pieces[i]->getRow() == row && pieces[i]->getCol() == col){
				return true;
		}
	}
	return false;
}

bool Board::canDestroy(int row, int col){
	 Piece ** pieces;
	if(turn==PLAYER1){
		pieces=pieces2;
	}else{
		pieces=pieces1;
	}
	for(int i=0; i<PIECES_PER_SIDE;++i){
		if(pieces[i]->getRow() == row && pieces[i]->getCol() == col){
				return true;
		}
	}
	return false;
}

Piece* Board::getPiece(int row, int col){
	for(int i=0; i<PIECES_PER_SIDE;++i){
		if(pieces1[i]->getRow() == row && pieces1[i]->getCol() == col){
				return pieces1[i];
		}
		if(pieces2[i]->getRow() == row && pieces2[i]->getCol() == col){
				return pieces2[i];
		}
	}
	return NULL;
}

bool Board::highlightList(list<square>& squares){
	list<square>::iterator it;
	for(it = squares.begin();it!=squares.end();it++){
		lightSquare((*it).row, (*it).col);
	}
	return false;
}

bool Board::isObjectSelected(){
	for(int i=0; i<PIECES_PER_SIDE;++i){
		if(pieces1[i]->isSelected() || pieces2[i]->isSelected()){
			return true;
		}
	}
	return false;
}

bool Board::notifyObject(int row,int col){
	Piece* piece = getSelectedPiece();
	return piece->selectCell(row,col);
}

Piece* Board::getSelectedPiece(){
	for(int i=0; i<PIECES_PER_SIDE;++i){
		if(pieces1[i]->isSelected()){
				return pieces1[i];
		}
		if(pieces2[i]->isSelected()){
				return pieces2[i];
		}
	}
	return NULL;
}

void Board::unselectObjects(){
	for(int i=0; i<PIECES_PER_SIDE;++i){
		pieces1[i]->setSelected(false);
		pieces2[i]->setSelected(false);
	}
}

void Board::switchTurns(){
	turn = !turn;
}
