#ifndef BOARD_GUARD
#define BOARD_GUARD

#include "Player.h"
#include "Piece.h"
#include "Move.h"
#include "Queen.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "IChessView.h"
#include <list>
#include <iostream>

/**
 * Must be 0 and 1 for switchTurns() to work
 */
#define PLAYER1 0
#define PLAYER2 1
#define PIECES_PER_SIDE 16

using namespace std;

class ChessView;

//Contains two players with pieces and calls players to move their
// stored pieces
//Checks for end of game scenarios
//Handles general functions of the game board
class Board{
	//Players on the board
	Player * player1, *player2;
	
	//Pieces on the board
	Piece* pieces1[PIECES_PER_SIDE];
	Piece* pieces2[PIECES_PER_SIDE];
	
	//Player's turn
	int turn;
	
	//Last Piece Selected
	int prev_piece;
	
	int prev_row, prev_col;
	
	IChessView * view;
	
	list<square> lit_squares;
public:	
	//Default Constructor
	Board(IChessView* _view);
	
	//Destructor
	~Board();
	
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
	void handleSelect(int row, int col);
	
	//Uses the passed in Move object to move the pieces back
	//Activates pieces if necessary
	void undoMove(Move move);
	
	//Resets all pieces to original positions
	void resetBoard();

	/**
	* determines if a piece belongs to player whose turn it is not
	*/
	 bool canDestroy(int row, int col);
	 
   /*
   * determines if a piece is on the specified square
   */
   bool isObject(int row, int col);

   /*
	* Returns the piece pointer of the object with these coordinates
	*/
   Piece* getPiece(int row, int col);
   
   /*
	* Determine if the selected piece is the right player
	*/
   bool correctPlayer(int row, int col);
   
   /**
   * Determines if King is in check
   */
   virtual bool inCheck();
   
   /**
   * Switches turns
   */
   void switchTurns();

private:
	//Highlights the given square
	void lightSquare(int row, int col);
	
	//Unhighlight all squares
	void unlightSquares();
	
	//Checks Checkmate or stalemate
	void checkEOG();
	
	//Checks validity of move (Checkmate)
	void checkMoveValid(Piece* piece, int from_row, int from_col,
						int to_row, int to_col);
	
	//Initializes the positions of all pieces on board
	void initializePieces();
	
	/**
	 * Initializes the pieces passed in
	 */
	void initializeSide(Piece** pieces, int color);
	
	/*
	 * Determines if the square is currently lit
	 */
	 bool isLit(int row, int column);
	 
	 /*
	  * Highlights and unhighlights appropriate squares
	  */
	  void highlightSquares(int row, int col);
	   
	   /*
	    * determines if the row and column were the last ones selected
	    */
	   bool sameAsLast(int row, int col);
	   
	   /*
	    * highlights all squares in the list
	    */
	   bool highlightList(list<square>& squares);
	  
	    
	    /*
	     * Notifies the selected object that cell has been successful
	     * Returns true if the cell was valid
	     */
	     bool notifyObject(int row,int col);
	     
	     /*
	      * Returns pointer to selected piece
	      * Only one piece can be selected at a time
	      */
	     Piece* getSelectedPiece();
	     
	     /**
	      * Unselects all objects in pieces1 and pieces2
	      */
	     void unselectObjects();
	    
	     
	     /*
		* Determines if any piece is selected
		*/
		bool isObjectSelected();
	    
	    /**
		* Gets the King's coodinate of opponent
		*/
		void getKingSquare(int& row, int& col);
		
		/**
    	* Determines if the given square is current player's move
		*/
		bool isMyMove(int& row, int& col);
};

#endif
