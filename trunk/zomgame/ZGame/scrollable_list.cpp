#include "scrollable_list.h"


ScrollableList::ScrollableList(){
	selectedIndex = 0;
	selected = true;
	stringList = new vector<string*>();
}

ScrollableList::ScrollableList(vector<string*>* nStringList){
	selectedIndex = 0;
	selected = true;
	stringList = nStringList;
}
		
string* ScrollableList::getStringForPosition(int position, int displayHeight){
	if (displayHeight > stringList->size()) {
		if (position >= stringList->size()) {
			return new string(" ");
		}
		return stringList->at(position);
	}
	if (selectedIndex <= displayHeight/2) {
		return stringList->at(position);
	}
	if (selectedIndex >= stringList->size() - displayHeight/2) {
		return stringList->at(stringList->size() - displayHeight + position);
	}

	int result = selectedIndex - displayHeight/2 + position;
	
	return stringList->at(result);
}

bool ScrollableList::isSelected() {
	return selected;
}

void ScrollableList::incIndex(){
	if (selectedIndex < stringList->size()-1) {
		selectedIndex++;
	}
}

void ScrollableList::decIndex(){
	if (selectedIndex > 0){
		selectedIndex--;
	}
}

void ScrollableList::resetIndex(){
	selectedIndex = 0;
}

int ScrollableList::getDisplayOffset(int displayHeight, int position){
	if (selectedIndex <= displayHeight/2 || displayHeight > stringList->size()){
		return 0;
	} 
	if (selectedIndex >= stringList->size() - displayHeight/2){
		return stringList->size() - (displayHeight-position);
	}
	return selectedIndex - displayHeight/2;
}

int ScrollableList::getSelectedIndex(){
	return selectedIndex;
}

void ScrollableList::setSelected(bool nSelected){
	selected = nSelected;
}

void ScrollableList::setList(vector<string*>* nStringList){
	stringList = nStringList;
}