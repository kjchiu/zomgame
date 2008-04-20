#include "game.h"

Game::Game(){
	init(100,100);
}

/* tWidth and tHeight represent the size of the world */
Game::Game(int tWidth, int tHeight){ 
	init(tWidth, tHeight);
}

void Game::init(int tWidth, int tHeight){
	map = new Map();
	player = new Player();
	player->setName("Durr");
	player->setLoc(new Coord(10,10));
	addMessage(new Message("Message 1"));
	addMessage(new Message("Message 2"));
	addMessage(new Message("123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456"));
	addMessage(new Message("Message 4"));
}


void Game::addMessage(Message *msg){
	messages.push_front(*msg);
}

/* returns an array of messages. This couldn't possibly go wrong, right? */
deque<Message> Game::getMessages(){
	return messages;
}

bool Game::processKey(char key){
	if (key=='c') { // Was if the 'c' key?
		for (int i=0; i<WIDTH*HEIGHT; ++i) {  // Yes, so clear the buffer to spaces:
	//		(map->getMap())[i].getChar();//Char.UnicodeChar = ' ';
		}
	} else if (key=='w') {
	//	player->setLoc(new Coord(player->getLoc()->getX(), player->getLoc()->getY()-1));
	} else if (key=='a') {
	//	player->setLoc(new Coord(player->getLoc()->getX()-1, player->getLoc()->getY()));
	}  else if (key=='s') {
	//	player->setLoc(new Coord(player->getLoc()->getX(), player->getLoc()->getY()+1));
	} else if (key=='d') {
	//	player->setLoc(new Coord(player->getLoc()->getX()+1, player->getLoc()->getY()));
	} else if (key=='q') {
		//do some stuff, but for now
		return false;
	}
	return true;
}

void Game::tick(){

}

void Game::draw(){
	map->clear();
	//player->draw(map);
}

void Game::runGame(){

}