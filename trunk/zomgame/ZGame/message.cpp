#include "message.h"

Message::Message(){
	setMsg(" ");
}
Message::Message(const char* message){
	setMsg(message);
}
Message::Message(string* message){
	setMsg(message);
}

Message::~Message(){
	//delete message;
}

const char * Message::getCharMsg(){
	return message->c_str();
}

/* Returns a string that fits in a space of given length */
Message* Message::formatMsg(int length){
	string* msg = getMsg();
	string* newMsg = new string(""); 
	int lastPos = 0;
	int pos = 0;
//	int offset = 0;
//	int cutoff;
	string substr = string("");
/*	
	if (msg->length() > length ){
		int runs = msg->length()/length;
		for (int k=runs; k>0; k++){
			cutoff=length;
			for (int j=(cutoff*k)-3; j>=0; j--){ //look for the nearest space, cut the string there
				if (msg->at(j) == ' '){
					cutoff = j;
					j = 0;
				}
			}
			msg->at(cutoff) = '\n';
		}
	}
*/
	for (int i=0; i<msg->size(); i++){
		if (msg->at(i) == '\n'){
			(*newMsg) += "\n   ";
		} else {
			(*newMsg) += msg->at(i);
		}
	}
	(*newMsg) += "\n";
	this->setMsg(newMsg);
	
	return this;
}

string* Message::getMsg(){
	return message;
}

void Message::setMsg(const char* msg){
	message = new string(msg);
}

void Message::setMsg(string* msg){
	message = msg;
}