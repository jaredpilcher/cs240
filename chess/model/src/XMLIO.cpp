#include "XMLIO.h"
#include "Piece.h"

//Saves the game to file named filename
//Returns whether or not it was successful;
bool XMLIO::saveChessGame(stack<Move> moves, 
	stack<PieceStruct> board_pieces, string filename){
	string file_string;
	invertMoves(moves);
	file_string = "<chessgame><board>";
	//cout << "here" << endl;
	int i=0;
	while(!board_pieces.empty()){
		
		//~ cout << "here1" << i << endl;

		file_string += pieceToXML(board_pieces.top());
		board_pieces.pop();
		//~ cout << "here2" << i++ << endl;
	}
	file_string += "</board><history>";
	while(!moves.empty()){
		file_string += moveToXML(moves.top());
		moves.pop();
	}
	file_string += "</history></chessgame>";
	//~ cout << "File_string: " << file_string << endl;
	return saveFile(file_string, filename);	

}

void XMLIO::invertMoves(stack<Move>& moves){
	stack<Move> temp_moves;
	while(!moves.empty()){
		temp_moves.push(moves.top());
		moves.pop();
	}
	moves = temp_moves;
}

//performs the actual saving of the 
bool XMLIO::saveFile(string file_string, string filename){
	ofstream opened_file;
	try{
		opened_file.open(filename.data());
	}catch(...){
		cout << "INVALID FILENAME" << endl;
		return false;
	}
	try{
		opened_file << file_string << endl;
	}catch(...){
		cout << "Unable to save to file" << endl;
	}
	opened_file.close();
	return true;
}

string XMLIO::pieceToXML(PieceStruct piece){
	string return_string;
	//char col[3];
	//char row[3];
	//itoa(,col,10);
	//itoa(piece.getCol(),row,10);
	return_string += "<piece ";
	return_string += "type=\"";
	return_string += getType(piece);
	//~ cout << "here" << endl;
	return_string += "\" color=\"";
	return_string += getColor(piece);
	//~ cout << "here1" << endl;
	return_string += "\" column=\"";
	return_string += toString(piece.col);
	//~ cout << "here2" << endl;
	return_string += "\" row=\"";
	return_string += toString(piece.row);
	//~ cout << "here3" << endl;
	return_string += "\"/>";
	return return_string;
	
}

string XMLIO::moveToXML(Move move){
	string return_string;
	return_string = "<move>";
	return_string += pieceToXML(move.getPrevPiece());
	return_string += pieceToXML(move.getAfterPiece());
	if(move.getDestroyedPiece().row!=-1){
		cout << "PIECE DESTROYED!" << endl;
		return_string += pieceToXML(move.getDestroyedPiece());
	}
	return_string += "</move>";
	return return_string;
}

//Determines which type it is and returns a string describing it
string XMLIO::getType(PieceStruct piece){
	ImageName type = piece.type;
	if(type == W_PAWN || type == B_PAWN){
		return "pawn";
	}if(type == W_ROOK || type == B_ROOK){
		return "rook";
	}if(type == W_KNIGHT || type == B_KNIGHT){
		return "knight";
	}if(type == W_BISHOP || type == B_BISHOP){
		return "bishop";
	}if(type == W_KING || type == B_KING){
		return "king";
	}if(type == W_QUEEN || type == B_QUEEN){
		return "queen";
	}
	return " ";
}

//Determines which color piece is and returns a string describing it
string XMLIO::getColor(PieceStruct piece){
	int color = piece.color;
	if(color == WHITE){
		return "white";
	}
	return "black";
}

string XMLIO::toString(int num){
	switch(num){
		case -1:
			return "-1";
		case 0:
			return "0";
		case 1:
			return "1";
		case 2:
			return "2";
		case 3:
			return "3";
		case 4:
			return "4";
		case 5:
			return "5";
		case 6:
			return "6";
		case 7:
			return "7";
		case 8:
			return "8";
		case 9:
			return "9";
		case 10:
			return "10";
		case 11:
			return "11";
		case 12:
			return "12";
		case 13:
			return "13";
		case 14:
			return "14";
		case 15:
			return "15";
	}
	return " ";
}
