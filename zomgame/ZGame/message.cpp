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

	string substr = string("");
	for (int i=0; i<msg->size(); i++){
		if (msg->at(i) == '\n'){
			numLines++;
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

int Message::getNumLines(){
	return numLines;
}

void Message::setMsg(const char* msg){
	message = new string(msg);
	numLines = 0;
}

void Message::setMsg(string* msg){
	message = msg;
}