/* This is a simple message */

#ifndef _MESSAGE_H
#define _MESSAGE_H

#include <string>

using namespace std;

class Message {
	private:
		string* message;

	public:
		Message();
		Message(const char* message);
		Message(string* message);
		~Message();
		string* getMsg();
		const char* getCharMsg();
		void setMsg(const char* msg);
		void setMsg(string* msg);
};

#endif