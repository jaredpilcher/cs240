#ifndef I_CHESS_CONTROLLER_H
#define I_CHESS_CONTROLLER_H

#include "IChessView.h"
#include "Model.h"
#include "Human.h"
#include "Computer.h"
#include <string.h>

#define HUMAN 0
#define COMPUTER 1

class ChessView;
class Board;
class Player;

//Processes Events from gui
//Makes all appropriate calls to Current and History 
//	for storing/retrieving
class IChessController
{
	IChessView * view;
	//Model model;
	Board * board;
	
	//Players on the board
	Player* player1;
	Player* player2;
	
	int p1_type;
	int p2_type;
	
	bool game_over;
	
	Model model;
	
public:
	/**
	 * Constructor
	 */
	IChessController(char ** argv, int argc);
	
	/**
	 * Destructor
	 */
	virtual ~IChessController();
	
	/**
	 * Indicate to the player that the user clicked on the given
	 * row and column with the mouse.
	 */
	virtual void on_CellSelected(int row, int col, int button);
	
	///@param row where drag began
	///@param col where drag began
	virtual void on_DragStart(int row,int col);

	///@param row where drag ended
	///@param col where drag ended
	///@return true if the drag resulted in a successful drop
	virtual bool on_DragEnd(int row,int col);

	/**
	 * Handle when the user selected the new game button.
	 */
	virtual void on_NewGame();

	/**
	 * Handle when the user selected the save game button.
	 */
	virtual void on_SaveGame();

	/**
	 * Handle when the user selected the save game as button.
	 */
	virtual void on_SaveGameAs();

	/**
	 * Handle when the user selected the load game button.
	 */
	virtual void on_LoadGame();
	/**
	 * Handle when the user selected the undo move button.
	 */
	virtual void on_UndoMove();
		
	/**
	 * Handle when the user selects to quit the game, either through the
	 * quit button, the close X button, or the file menu.
	 */
	virtual void on_QuitGame();
		
	/**
	 * Handle when a timer event has been signaled.
	 */
	virtual void on_TimerEvent();
	
	/**
	 * Set the IChessView that this IChessController will handle inputs for.
	 */
	virtual void SetView(IChessView* view);
	
	/**
	 * Set the Board that this IChessController will handle inputs for.
	 */
	virtual void SetBoard(Board* board);
	
	/**
	 * Ends the game
	 */
	void endOfGame();
};

#endif

