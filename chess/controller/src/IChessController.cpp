#include "IChessController.h"
#include "Board.h"


/**
 * Constructor
 */
IChessController::IChessController(char ** argv, int argc): game_over(false),current_file(""),game_paused(false){
	string temp_type = argv[1];
	if(temp_type=="0"){
		std::cout << "Human vs Human" << std::endl;
		player1 = new Human();
		player2 = new Human();
		p1_type = HUMAN;
		p2_type = HUMAN;
	}
	
	if(temp_type=="1"){
		std::cout << "Human vs Computer" << std::endl;
		player1 = new Human();
		player2 = new Computer();
		p1_type = HUMAN;
		p2_type = COMPUTER;
	}
	
	if(temp_type=="2"){
		std::cout << "Computer vs Human" << std::endl;
		player1 = new Computer();
		player2 = new Human();
		p1_type = COMPUTER;
		p2_type = HUMAN;
	}
	
	if(temp_type=="3"){
		std::cout << "Computer vs Computer" << std::endl;
		player1 = new Computer();
		player2 = new Computer();
		p1_type = COMPUTER;
		p2_type = COMPUTER;
	}
}

/**
 * Destructor
 */
IChessController::~IChessController(){
	delete player1;
	delete player2;
}

/**
 * Indicate to the player that the user clicked on the given
 * row and column with the mouse.
 */
void IChessController::on_CellSelected(int row, int col, int button){
	int select_return;
	Move move;
	if((board->isWhiteTurn()) && p1_type==HUMAN && !game_over){
		select_return = board->handleSelect(row, col, move);
		if(select_return == MOVED){
			model.pushMove(move);
			player2->makeMove(move);
		}
	}else if(!(board->isWhiteTurn()) && p2_type==HUMAN && !game_over){
		select_return = board->handleSelect(row, col,move);
		if(select_return == MOVED){
			model.pushMove(move);
			player1->makeMove(move);
		}
	}
}

///@param row where drag began
///@param col where drag began
void IChessController::on_DragStart(int row,int col){
	//g_debug("IChessController::on_DragStart");

}

void IChessController::endOfGame(){
	game_over = true;
}

///@param row where drag ended
///@param col where drag ended
///@return true if the drag resulted in a successful drop
bool IChessController::on_DragEnd(int row,int col){
	//g_debug("IChessController::on_DragEnd");
	return false;
}

/**
 * Handle when the user selected the new game button.
 * Calls to Board to reset pieces
 * Calls to model to delete Current and History
 */
void IChessController::on_NewGame(){
	game_paused = true;
	board->clearBoard();
	model.clearHistory();
	//g_debug("IChessController::on_NewGame");
	Move move;
	board->initializePieces();
	view->SetBottomLabel("Player 1's Turn!");
	player1->makeMove(move);
	game_paused = false;
}

/**
 * Handle when the user selected the save game button.
 * Calls to the Model to save the current file with 
 * 		Current and History
 */
void IChessController::on_SaveGame(){
	game_paused = true;
	board->unlightSquares();
	if(current_file==""){
		on_SaveGameAs();
	}else{
		if(!(model.saveFile(current_file,board->getPieces()))){
			cout << "Unable to save file" << endl;
		}else{
			cout << "File Saved" << endl;
		}
	}
	game_paused = false;

}

/**
 * Handle when the user selected the save game as button.
 * Calls to view to get the path
 * Calls to the Model to save file with Current and History
 */
void IChessController::on_SaveGameAs(){
	game_paused = true;
	board->unlightSquares();
	current_file = view->SelectSaveFile();
	model.saveFile(current_file,board->getPieces());
	game_paused = false;
}

/**
 * Handles when the user selected the load game button.
 * Calls SelectLoadFile() to get file path.
 * Calls to Model to read the file and load contents into
 * 		Current and History objects in Model
 */
void IChessController::on_LoadGame(){
	game_paused = true;
	board->unlightSquares();
	Move move;
	stack<PieceStruct> current_pieces;
	current_file = view->SelectLoadFile();
	if(model.loadFile(current_file, current_pieces)){
		board->clearBoard();
		loadPieces(current_pieces);
		if(model.isWhiteTurn()){
			view->SetBottomLabel("Player 1's Turn!");
			player1->makeMove(move);
		}else{
			view->SetBottomLabel("Player 2's Turn!");
			player2->makeMove(move);		
		}
	}
	game_paused = false;
}

void IChessController::loadPieces(stack<PieceStruct> current_pieces){
	board->clearBoard();
	while(current_pieces.size()>0){
		board->loadPiece(current_pieces.top());
		current_pieces.pop();
	}
}

/**
 * Handle when the user selected the undo move button.
 * Grabs last move from History and instructs the board to 
 * 	undo those moves
 */
void IChessController::on_UndoMove(){
	game_paused = true;
	if(game_over) game_over=false;
	board->unlightSquares();
	if(!model.isHistoryEmpty()){
		board->undoMove(model.popMove());
	}
	game_paused = false;
}
	
/**
 * Handle when the user selects to quit the game, either through the
 * quit button, the close X button, or the file menu.
 */
void IChessController::on_QuitGame(){
	game_paused = true;
	//g_debug("IChessController::on_QuitGame");

}
	
/**
 * Handle when a timer event has been signaled.
 * Calls Player timer Events
 */
void IChessController::on_TimerEvent(){	
	if(!game_paused){
		int select_return = NO_MOVE;
		Move move;
		if((board->isWhiteTurn()) && !game_over){
			view->SetBottomLabel("Player 1's Turn!");
			select_return = player1->makeMove(move);
			if(board->checkEOG()) endOfGame();
		}else if(!game_over){
			view->SetBottomLabel("Player 2's Turn!");
			select_return = player2->makeMove(move);
			if(board->checkEOG()) endOfGame();
		}else if(board->isWhiteTurn()){
			view->SetBottomLabel("Checkmate! Player 2 Wins!");
		}else{
			view->SetBottomLabel("Checkmate! Player 1 Wins!");
		}
		if(select_return == MOVED){
			model.pushMove(move);
		}
	}
}

/**
 * Set the IChessView that this IChessController will handle inputs for.
 */
void IChessController::SetView(IChessView* view){
	//g_debug("IChessController::SetView");
	this->view = view;
}

/**
 * Set the Board that this IChessController will handle inputs for.
 */
void IChessController::SetBoard(Board* _board){
	//g_debug("IChessController::SetBoard");
	board = _board;
	player1->setBoard(board);
	player2->setBoard(board);
}
