#include "renderable.h"

int Renderable::id = 0;

string Renderable::getListName(){
	string returnString = "";
	for (unsigned int i = 0; i < getName().size();i++){
		//65 = A, 90=Z, 97 = a
		int lowerChar = getName().at(i);
		if (i == 0){
			returnString = "a ";
			if (lowerChar == 65 || lowerChar == 69 || lowerChar == 73 || lowerChar == 79 || lowerChar == 85){
				returnString = "an ";
			}
		}
		
		if (lowerChar >= 65 && lowerChar <= 90){ //if it's uppercase
			lowerChar += 32;
		}
		returnString += lowerChar;
	}
	return returnString;
}