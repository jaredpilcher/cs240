#ifndef COMPUTER_GUARD
#define COMPUTER_GUARD

#include "Player.h"

/**
 * Interface for interacting with computer plaer
 */
class Computer: public Player{
	
public: //methods

	/**
	 * Constructor
	 */
	Computer();
	
	/**
	 * Destructor
	 */
	~Computer();

	/**
	 * Indicate to the player that the user clicked on the given
	 * row and column with the mouse.
	 */
	virtual void on_CellSelected(int row, int col, int button);
	
	/**
	 * Instructs player to make a move 
	 */
	virtual int makeMove(Move& move);

	/**
	 * Handle when the timeout duration has passed.
	 */
	virtual void on_TimerEvent();
};

#endif
