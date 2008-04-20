#include "message.h"

Message::Message(){
	setMsg(" ");
}
Message::Message(char* message){
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

string* Message::getMsg(){
	return message;
}

void Message::setMsg(char* msg){
	message = new string(msg);
}

void Message::setMsg(string* msg){
	message = msg;
}