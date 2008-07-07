/* Represents a popup window. For ease of use. */

#ifndef _POPUPWIN_H
#define _POPUPWIN_H

#include "all_includes.h"

using namespace std;

class PopupWin {
	private:
		string header;
		vector<string>* list;
		WINDOW* win;
		int selectedIndex;
	
		void init(int nXPos, int nYPos, int nHeight, int nWidth);

	public:
		PopupWin();
		PopupWin(int nXPos, int nYPos);
		PopupWin(int nXPos, int nYPos, int nHeight, int nWidth);
		
		string getHeader();
		vector<string>* getList();
		string getListItemAt(int index);
		int getSelectedIndex();
		WINDOW* getWindow();
	
		void draw();

		void clear();

		void decrementSelection();
		void incrementSelection();

		void setHeader(string nHeader);
		void setList(vector<string>* nList);
		void setListItemAt(int index, string nListItem);
		void setSelectedIndex(int nSelectedIndex);
		void setWindow(WINDOW* nWin);

		
};

#endif