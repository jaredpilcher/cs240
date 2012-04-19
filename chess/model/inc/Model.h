#ifndef MODEL_GUARD
#define MODEL_GUARD

#include "History.h"
#include "XMLIO.h"
#include "Move.h"
#include <stack>
#include <iostream>
#include <fstream>
using namespace std;

class Piece;

class Model{
	History history;
	XMLIO xml;
public:

	Model();
	
	~Model();
	
	void pushMove(Move move);
	
	Move popMove();
	
	bool isHistoryEmpty();
	
	void clearHistory();
	
	//saves the file to the current filename
	//returns if successful or not
	bool saveFile(string filename,stack<PieceStruct> pieces);
	
	//loads the file into board and history
	//Returns whether or not it was loaded properly
	bool loadFile(string filename, stack<PieceStruct>& current_board);
	
	//Returns whether or not it is Player 1's turn if loading a file
	bool isWhiteTurn();
	
};

#endif
