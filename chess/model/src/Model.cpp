#include "Model.h"
#include "Piece.h"

Model::Model(){
	
}

Model::~Model(){
	
}

void Model::pushMove(Move move){
	history.pushMove(move);
}

Move Model::popMove(){
	return history.popMove();
}

bool Model::isHistoryEmpty(){
	return history.isEmpty();
}

void Model::clearHistory(){
		history.clearMoves();
}

bool Model::saveFile(string filename, stack<PieceStruct> pieces){
	xml.saveChessGame(history.getMoves(),pieces,filename);
}

//loads the file into board and history
//Returns whether or not it was loaded properly
bool Model::loadFile(string filename, stack<PieceStruct>& current_board){
	stack<Move> moves;
	if(!xml.loadChessGame(moves,current_board,filename)) return false;
	return true;
}


//Returns whether or not it is Player 1's turn when loading a file
bool Model::isWhiteTurn(){
	//FIX LATER!
	return true;
	//END FIX LATER!
}
