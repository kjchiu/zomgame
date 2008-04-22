#include "game.h"

extern Player* player;
extern Map* map;

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
	map->getBlockAt(player->getLoc())->addEntity(player);
	
	//set up the offsets
	directionOffsets[0] = new Coord(0,-1);
	directionOffsets[1] = new Coord(1,-1);
	directionOffsets[2] = new Coord(1,0);
	directionOffsets[3] = new Coord(1, 1);
	directionOffsets[4] = new Coord(0,1);
	directionOffsets[5] = new Coord(-1,1);
	directionOffsets[6] = new Coord(-1,0);
	directionOffsets[7] = new Coord(-1,-1);

	Entity* ent1 = new Entity();
	ent1->setDisplayChar('1');
	ent1->setColor(3);
	map->getBlockAt(1,1)->addEntity(ent1);
	Entity* ent2 = new Entity();
	ent2->setDisplayChar('2');
	map->getBlockAt(2,2)->addEntity(ent2);
	Entity* ent3 = new Entity();
	ent3->setDisplayChar('3');
	ent3->setColor(3);
	map->getBlockAt(3,3)->addEntity(ent3);
}

void Game::addMessage(Message *msg){
	messages.push_front(*msg);
}

/* returns an array of messages. This couldn't possibly go wrong, right? */
deque<Message> Game::getMessages(){
	return messages;
}

void Game::movePlayer(direction dir){
	Coord moveLoc = (*directionOffsets[dir]) + (*player->getLoc());
	if (isPassable(&moveLoc)){

		map->getBlockAt(player->getLoc())->removeEntity(player);
		player->setLoc(&moveLoc);
		map->getBlockAt(player->getLoc())->addEntity(player);
	}
}

bool Game::processKey(char key){
	if (key=='c') { // Was if the 'c' key?
		for (int i=0; i<WIDTH*HEIGHT; ++i) {  // Yes, so clear the buffer to spaces:
	//		(map->getMap())[i].getChar();//Char.UnicodeChar = ' ';
		}
	} else if (key=='w') {
		movePlayer(NORTH);//player->setLoc(new Coord(player->getLoc()->getX(), player->getLoc()->getY()-1));
	} else if (key=='a') {
		movePlayer(WEST);
	}  else if (key=='s') {
		movePlayer(SOUTH);
	} else if (key=='d') {
		movePlayer(EAST);
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

bool Game::isPassable(Coord* nextLoc){
	if (nextLoc->getX()<-300){
		int boo = 0;
	}
	MapBlock* checkBlock = map->getBlockAt(nextLoc->getX(), nextLoc->getY());
	if (nextLoc->getX() >= 0 && nextLoc->getY() >= 0 && nextLoc->getX() < map->MAPWIDTH && nextLoc->getY() < map->MAPHEIGHT
		&& checkBlock->isPassable()){
		return true;
	}
	return false;
}