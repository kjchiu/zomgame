/* A scrollable list of strings. */

#ifndef _SCROLL_LIST_H
#define _SCROLL_LIST_H

#include <vector>
#include <string>

using namespace std;

class ScrollableList {

	private:
		int selectedIndex;
		bool selected;
		vector<string*>* stringList;

	public:
		ScrollableList();
		ScrollableList(vector<string*>* nStringList);
		string* getStringForPosition(int position, int displayHeight);
		bool isSelected();
		void incIndex();
		void decIndex();
		void resetIndex();
		int getDisplayOffset(int displayHeight, int position);
		int getSelectedIndex();
		void setSelected(bool nSelected);
		void setList(vector<string*>* nStringList);
};

#endif