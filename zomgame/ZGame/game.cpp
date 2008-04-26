
#include <curses.h>
#include "game.h"
#include "referee.h"

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
	ref = new Referee();

	//set up the offsets
	directionOffsets[0] = new Coord(0,-1);
	directionOffsets[1] = new Coord(1,-1);
	directionOffsets[2] = new Coord(1,0);
	directionOffsets[3] = new Coord(1, 1);
	directionOffsets[4] = new Coord(0,1);
	directionOffsets[5] = new Coord(-1,1);
	directionOffsets[6] = new Coord(-1,0);
	directionOffsets[7] = new Coord(-1,-1);

	Entity* ent1 = new Entity("Zombie 1");
	ent1->setDisplayChar('Z');
	ent1->setColor(3);
	map->getBlockAt(1,1)->addEntity(ent1);
	Prop* wall1 = new Prop();
	wall1->setName("Wall");
	wall1->setDisplayChar(ACS_CKBOARD);
	wall1->setPassable(false);
	map->getBlockAt(5,5)->addProp(wall1);
	wall1 = new Prop();
	wall1->setName("Wall");
	wall1->setDisplayChar(ACS_CKBOARD);
	wall1->setPassable(false);
	map->getBlockAt(5,6)->addProp(wall1);
}

void Game::addMessage(Message *msg){
	messages.push_front(*msg);
}

/* returns an array of messages */
deque<Message> Game::getMessages(){
	return messages;
}

void Game::moveEntity(Entity* ent, direction dir){
	Coord moveLoc = (*directionOffsets[dir]) + (*ent->getLoc());
	if (isPassable(&moveLoc)){
		map->getBlockAt(player->getLoc())->removeEntity(ent);
		ent->setLoc(&moveLoc);
		map->getBlockAt(player->getLoc())->addEntity(ent);
	} else { //why is it not passable?
		MapBlock* checkBlock = map->getBlockAt(moveLoc.getX(), moveLoc.getY());
		if (checkBlock->hasEntities()){  //resolve an attack (what about friendly NPCs?)	
			addMessage(ref->resolveAttack(ent, checkBlock->getTopEntity()));
		}
	}
}

bool Game::processKey(char key){
	if (key=='c') { 
	} else if (key=='m'){
		addMessage(new Message("Test Message"));
	} else if (key=='w') {
		moveEntity(player, NORTH);
	} else if (key=='a') {
		moveEntity(player, WEST);
	}  else if (key=='s') {
		moveEntity(player, SOUTH);
	} else if (key=='d') {
		moveEntity(player, EAST);
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
	MapBlock* checkBlock = map->getBlockAt(nextLoc->getX(), nextLoc->getY());
	if (nextLoc->getX() >= 0 && nextLoc->getY() >= 0 && nextLoc->getX() < map->MAPWIDTH && nextLoc->getY() < map->MAPHEIGHT
		&& checkBlock->isPassable()){
		return true;
	}
	return false;
}