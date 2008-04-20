/* This is a simple message */

#include <string>

using namespace std;

class Message {
	private:
		string* message;

	public:
		Message();
		Message(char* message);
		Message(string* message);
		~Message();
		string* getMsg();
		const char* getCharMsg();
		void setMsg(char* msg);
		void setMsg(string* msg);
};