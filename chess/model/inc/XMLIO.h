#ifndef XMLIO_GUARD
#define XMLIO_GUARD

#include "XML.h"
#include "Move.h"
#include "ChessGuiDefines.h"
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <fstream>
using namespace std;

class XMLIO{
public:
	XMLIO(){}
	~XMLIO(){}
	
	//Saves the game to file named filename
	//Returns whether or not the file was saved properly
	bool saveChessGame(stack<Move> moves, stack<PieceStruct> board_pieces, string filename);
	
private:
	//performs the actual saving of the 
	bool saveFile(string file_string, string filename);
	
	string pieceToXML(PieceStruct piece);
	
	string moveToXML(Move move);
	
	//Determines which color piece is and returns a string describing it
	string getColor(PieceStruct piece);
	
	//Determines which type it is and returns a string describing it
	string getType(PieceStruct piece);
	
	//Convert an integer to string from 0-16
	string toString(int num);
	
	//inverts the moves to get in chronological order
	void invertMoves(stack<Move>& moves);
};

#endif
