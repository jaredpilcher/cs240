#ifndef PLAYER_GUARD
#define PLAYER_GUARD

#include "Piece.h"

/**
 * The IChessPlayer class provides an interface for a ChessController implementation to interact
 * with the player through, regardless of whether the player is a human or a computer.
 */
class Player{
public: //methods
	/**
	 * Indicate to the player that the user clicked on the given
	 * row and column with the mouse.
	 */
	virtual void on_CellSelected(int row, int col, int button) = 0;
	
	/**
	 * Instructs player to make a move 
	 */
	virtual void makeMove() = 0;

	/**
	 * Handle when the timeout duration has passed.
	 */
	virtual void on_TimerEvent() = 0;
};

#endif