#include "Board.h"
#include <iostream>


//Default Constructor
Board::Board(IChessView* _view): turn(PLAYER1), view(_view), 
		prev_row(-1), prev_col(-1), prev_piece(0){
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
int Board::handleSelect(int row, int col){
	int temp_row = row;
	int temp_col = col;
	bool return_int = NO_MOVE;
	if(isObject(row, col)){
		if(sameAsLast(row, col)){
			unselectObjects();
			unlightSquares();
			temp_row = -1;
			temp_col = -1;
		}
		else if(correctPlayer(row, col)){
			Piece * temp_piece = getPiece(row, col);
			unlightSquares();
			unselectObjects();
			list<square> temp_squares = temp_piece->selectPiece();
			temp_squares.push_front((square){temp_piece->getRow(),temp_piece->getCol()});
			highlightList(temp_squares);
		}else{
			if(isObjectSelected()){
				bool success_select = notifyObject(row,col);
				if(success_select){
					switchTurns();
				return_int = MOVED;
				}
				unselectObjects();
				unlightSquares();
				temp_row = -1;
				temp_col = -1;
			}else{
				unselectObjects();
				unlightSquares();
			}
		}
	}else{
		if(isObjectSelected()){
			bool success_select = notifyObject(row,col);
			//std::cout << "success_select: " << success_select << std::endl;
			if(success_select){
				//std::cout << "Successful move!" << std::endl;
				//g_debug("Successful move!");
				switchTurns();
				return_int = MOVED;
			}
			unselectObjects();
			unlightSquares();
			temp_row = -1;
			temp_col = -1;
		}else{
			unselectObjects();
			unlightSquares();
		}
		
	}
	//std::cout << "End of handleSelect! " << return_int << std::endl;

	prev_row = temp_row;
	prev_col = temp_col;
	return return_int;
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
	//std::cout << "lightSquare row: " << row << " col: " << col << std::endl;
	 view->HighlightSquare(row, col, 65535);
	 lit_squares.push_front((square){row,col});
}

//Unhighlight all squares
void Board::unlightSquares(){
	list<square>::iterator it;
	for(it = lit_squares.begin();it!=lit_squares.end();it++){
		//std::cout << "UnlightSquare row: " << (*it).row << " col: " << (*it).col << std::endl;
		view->UnHighlightSquare((*it).row,(*it).col);
	}
	lit_squares.clear();
}

//Checks Checkmate or stalemate
bool Board::checkEOG(){
	 Piece ** pieces;
	 list<square> moves;
	 bool game_over = true;
	if(turn==PLAYER1){
		pieces=pieces1;
	}else{
		pieces=pieces2;
	}
	for(int i=0;i<PIECES_PER_SIDE;++i){
		if(pieces[i]->isActive()){
			pieces[i]->getMoves(moves);
		}
		if(moves.size()!=0){;
			game_over=false;
			break;
		}
		moves.clear();		
	}
	return game_over;
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
			pieces[i] = new Pawn(6,i,WHITE, view, this, W_PAWN);
		}
	}else{
		for(;i<8;++i){
			pieces[i] = new Pawn(1,i,BLACK, view, this, B_PAWN);
		}
	}
	
	if(color==WHITE){
		pieces[i++] = new Rook(7,0,WHITE, view, this, W_ROOK);
		pieces[i++] = new Rook(7,7,WHITE, view, this, W_ROOK);
	}else{
		pieces[i++] = new Rook(0,0,BLACK, view, this, B_ROOK);
		pieces[i++] = new Rook(0,7,BLACK, view, this, B_ROOK);
	}
	
	if(color==WHITE){
		pieces[i++] = new Knight(7,1,WHITE, view, this, W_KNIGHT);
		pieces[i++] = new Knight(7,6,WHITE, view, this, W_KNIGHT);
	}else{
		pieces[i++] = new Knight(0,1,BLACK, view, this, B_KNIGHT);
		pieces[i++] = new Knight(0,6,BLACK, view, this, B_KNIGHT);
	}
	
	if(color==WHITE){
		pieces[i++] = new Bishop(7,2,WHITE, view, this, W_BISHOP);
		pieces[i++] = new Bishop(7,5,WHITE, view, this, W_BISHOP);
	}else{
		pieces[i++] = new Bishop(0,2,BLACK, view, this, B_BISHOP);
		pieces[i++] = new Bishop(0,5,BLACK, view, this, B_BISHOP);
	}
	
	if(color==WHITE){
		pieces[i++] = new Queen(7,3,WHITE, view, this, W_QUEEN);
	}else{
		pieces[i++] = new Queen(0,3,BLACK, view, this, B_QUEEN);
	}
	
	if(color==WHITE){
		pieces[i++] = new King(7,4,WHITE, view, this, W_KING);
	}else{
		pieces[i++] = new King(0,4,BLACK, view, this, B_KING);
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
		if(pieces[i]!=NULL){
			if(pieces[i]->getRow() == row && pieces[i]->getCol() == col){
					return true;
			}
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
		if(pieces[i]!=NULL){
			if(pieces[i]->getRow() == row && pieces[i]->getCol() == col){
					return true;
			}
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
	bool temp_select = piece->selectCell(row,col);
	//std::cout << "returned from select cell" << std::endl;
	//std::cout << "temp_select: " << temp_select << std::endl;
	return temp_select;
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

/**
* Determines if King is in check
*/
bool Board::inCheck(){
	int row, col;
	getKingSquare(row,col);
	return isMyMove(row,col);
}

/**
 * Gets the King's coodinate of opponent
 */
void Board::getKingSquare(int& row, int& col){
	Piece ** pieces;
	if(turn==PLAYER1){
		pieces=pieces2;
	}else{
		pieces=pieces1;
	}
	for(int i=0; i<PIECES_PER_SIDE;++i){
		if((pieces[i]->getType() == W_KING) || (pieces[i]->getType() == B_KING)){
				row = pieces[i]->getRow();
				col = pieces[i]->getCol();
				//std::cout << "Found King at row: " << row << " and col: " << col << std::endl;
				return;
		}
	}
	row = -1;
	col = -1;
}

/**
 * Determines if the given square is a valid curren player's move
 */
bool Board::isMyMove(int& row, int& col){
	Piece ** pieces;
	if(turn==PLAYER1){
		pieces=pieces1;
	}else{
		pieces=pieces2;
	}
	for(int i=0; i<PIECES_PER_SIDE;++i){
		if((pieces[i]->isActive()) && (pieces[i]->isValidPossibleMove(row,col))){
			return true;
		}
	}
	return false;
}

/**
* Returns who's turn it is
*/
bool Board::isWhiteTurn(){
	return !turn;
}

