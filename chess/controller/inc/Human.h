#ifndef HUMAN_GUARD
#define HUMAN_GUARD

#include "Player.h"

/**
 * Interface for interacting with human player
 */
class Human: public Player{
public: //methods

	/**
	 * Constructor
	 */
	Human();
	
	/**
	 * Destructor
	 */
	~Human();
	
	/**
	 * Indicate to the player that the user clicked on the given
	 * row and column with the mouse.
	 */
	virtual void on_CellSelected(int row, int col, int button);
	
	/**
	 * Instructs player to make a move 
	 */
	virtual void makeMove();

	/**
	 * Handle when the timeout duration has passed.
	 */
	virtual void on_TimerEvent();
};

#endif
