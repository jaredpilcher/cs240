#include "IChessController.h"
#include "Board.h"


/**
 * Constructor
 */
IChessController::IChessController(char ** argv, int argc){
	
		std::cout << "argv: " << argv[1] << std::endl;
	if(argv[1]==0){
		std::cout << "Human vs Human" << std::endl;
		player1 = new Human();
		player2 = new Human();
		p1_type = HUMAN;
		p2_type = HUMAN;
	}
	
	if(argv[1]=="1"){
		std::cout << "Human vs Computer" << std::endl;
		player1 = new Human();
		player2 = new Computer();
		p1_type = HUMAN;
		p2_type = COMPUTER;
	}
}

/**
 * Destructor
 */
IChessController::~IChessController(){
	//delete player1;
	//delete player2;
}

/**
 * Indicate to the player that the user clicked on the given
 * row and column with the mouse.
 */
void IChessController::on_CellSelected(int row, int col, int button){
	g_debug("IChessController::on_CellSelected");
	if((board->isWhiteTurn()) && p1_type==HUMAN){
		board->handleSelect(row, col);
	}else if(!(board->isWhiteTurn()) && p2_type==HUMAN){
		board->handleSelect(row, col);
	}
}

///@param row where drag began
///@param col where drag began
void IChessController::on_DragStart(int row,int col){
	g_debug("IChessController::on_DragStart");

}

///@param row where drag ended
///@param col where drag ended
///@return true if the drag resulted in a successful drop
bool IChessController::on_DragEnd(int row,int col){
	g_debug("IChessController::on_DragEnd");
	return false;
}

/**
 * Handle when the user selected the new game button.
 * Calls to Board to reset pieces
 * Calls to model to delete Current and History
 */
void IChessController::on_NewGame(){
	//g_debug("IChessController::on_NewGame");
	
	board->initializePieces();
}

/**
 * Handle when the user selected the save game button.
 * Calls to the Model to save the current file with 
 * 		Current and History
 */
void IChessController::on_SaveGame(){
	g_debug("IChessController::on_SaveGame");

}

/**
 * Handle when the user selected the save game as button.
 * Calls to view to get the path
 * Calls to the Model to save file with Current and History
 */
void IChessController::on_SaveGameAs(){
	view->SelectSaveFile();
}

/**
 * Handles when the user selected the load game button.
 * Calls SelectLoadFile() to get file path.
 * Calls to Model to read the file and load contents into
 * 		Current and History objects in Model
 */
void IChessController::on_LoadGame(){
	view->SelectLoadFile();
}

/**
 * Handle when the user selected the undo move button.
 * Grabs last move from History and instructs the board to 
 * 	undo those moves
 */
void IChessController::on_UndoMove(){
	g_debug("IChessController::on_UndoMove");

}
	
/**
 * Handle when the user selects to quit the game, either through the
 * quit button, the close X button, or the file menu.
 */
void IChessController::on_QuitGame(){
	//g_debug("IChessController::on_QuitGame");

}
	
/**
 * Handle when a timer event has been signaled.
 * Calls Player timer Events
 */
void IChessController::on_TimerEvent(){
	//g_debug("IChessController::on_TimerEvent");
	//player1->on_TimerEvent();
	//player2->on_TimerEvent();
}

/**
 * Set the IChessView that this IChessController will handle inputs for.
 */
void IChessController::SetView(IChessView* view){
	g_debug("IChessController::SetView");
	this->view = view;
}

/**
 * Set the Board that this IChessController will handle inputs for.
 */
void IChessController::SetBoard(Board* board){
	g_debug("IChessController::SetBoard");
	this->board = board;
}
