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
	int lastPos = 0, pos = 0;
	//first go through the message and place a \n after 'length' number of characters
	string substr = "";
	for (unsigned int i = 0; i < msg->size() / length; i++){
		for (unsigned int j = lastPos + 1; j <= (i + 1) * (length - 2); j++){
			if (msg->at(j) == ' '){
				pos = j;
			}
		}
		if (pos == 0){
			pos = (i+1)*(length-2);
		}
		(*newMsg) += msg->substr(lastPos, pos-lastPos) + "\n";
		lastPos = pos+1;
		pos = 0;
		
	} 
	(*newMsg) += msg->substr(lastPos, msg->size() - lastPos);

	this->setMsg(newMsg);
	newMsg = new string("");
	msg = getMsg();
	
	//now format the \n to take account of the borders
	for (unsigned int i = 0; i < msg->size(); i++){
		if (msg->at(i) == '\n'){
			numLines++;
			(*newMsg) += "\n   ";
		} else {
			(*newMsg) += msg->at(i);
		}
	}
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
	numLines = 0;
}