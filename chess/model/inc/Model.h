#ifndef MODEL_GUARD
#define MODEL_GUARD

#include "History.h"
#include "XMLIO.h"
#include "Move.h"
#include <stack>
#include <iostream>
#include <fstream>
using namespace std;

class Model{
	History history;
public:

	Model();
	
	~Model();
	
	void pushMove(Move move);
	
	Move popMove();
	
	bool isHistoryEmpty();
	
	void clearHistory();
	
	//saves the file to the current filename
	//returns if successful or not
	bool saveFile(string filename);
	
	//loads the file into board and history
	//Returnts a list of piece structs that is the current board setup
	stack<PieceStruct> loadFile(string filename);
	
	//Returns whether or not it is Player 1's turn if loading a file
	bool isWhiteTurn();
	
};

#endif
