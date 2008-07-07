#include "popupWin.h"

PopupWin::PopupWin() {
	init(0,0, 10, 10);
}

PopupWin::PopupWin(int nXPos, int nYPos) {
	init(nXPos, nYPos, 10, 10);
}

PopupWin::PopupWin(int nXPos, int nYPos, int nHeight, int nWidth) {
	init(nXPos, nYPos, nHeight, nWidth);
}

void PopupWin::init(int nXPos, int nYPos, int nHeight, int nWidth) {
	win = newwin(nHeight,nWidth,nXPos,nYPos); //height, width, starty, startx
	header = "Header";
	list = new vector<string>();
	selectedIndex = 0;
}

/* Clears all the data */
void PopupWin::clear(){
	setHeader("");
	setList(new vector<string>());
	setSelectedIndex(0);
	wclear(getWindow());
}

void PopupWin::draw(){
	wclear(getWindow());
	mvwprintw(getWindow(), 1, 1, "%s", header.data());
	for (int i=0; i<list->size(); i++){
		if (i==selectedIndex){
			wattron(getWindow(), COLOR_PAIR(4)); //4 = yellow/black
			mvwprintw(getWindow(), i+2, 2, "-%s-", list->at(i).data());
			wattroff(getWindow(), COLOR_PAIR(4));
		} else {
			mvwprintw(getWindow(), i+2, 3, "%s", list->at(i).data());
		}
	}
	box(getWindow(), 0,0);
	mvwprintw(getWindow(), 0, 1, "USE ITEM");
	wrefresh(getWindow());	
}

string PopupWin::getHeader(){
	return header;
}

vector<string>* PopupWin::getList(){
	return list;
}

string PopupWin::getListItemAt(int index){
	return list->at(index);
}

int PopupWin::getSelectedIndex(){
	return selectedIndex;
}

WINDOW* PopupWin::getWindow(){
	return win;
}

void PopupWin::decrementSelection(){
	selectedIndex--;
	if (selectedIndex < 0){
		selectedIndex = list->size() - 1;
	} 
}

void PopupWin::incrementSelection(){
	selectedIndex++;
	if (selectedIndex >= list->size()){
		selectedIndex = 0;
	}
}

void PopupWin::setHeader(string nHeader){
	header = nHeader;
}

void PopupWin::setList(vector<string>* nList){
	list = nList;
}

void PopupWin::setListItemAt(int index, string nListItem){
	if (index < list->size() && index >= 0){
		list->at(index) = nListItem;
	}
}

void PopupWin::setSelectedIndex(int nSelectedIndex){
	selectedIndex = nSelectedIndex;
}

void PopupWin::setWindow(WINDOW* nWin){
	win = nWin;
}
