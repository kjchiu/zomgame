/* This is a simple message */

#ifndef _MESSAGE_H
#define _MESSAGE_H

#include <string>

using namespace std;

class Message {
	private:
		string* message;
		int numLines;

	public:
		Message();
		Message(const char* message);
		Message(string* message);
		~Message();
		Message* formatMsg(int length);
		string* getMsg();
		int getNumLines();
		const char* getCharMsg();
		void setMsg(const char* msg);
		void setMsg(string* msg);
};

#endif