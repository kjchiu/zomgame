
#include <curses.h>
#include "game.h"
#include "referee.h"
#include "globals.h"
#include <sstream>

Game::Game(){
	init(100,100);
}

/* tWidth and tHeight represent the size of the world */
Game::Game(int tWidth, int tHeight){ 
	init(tWidth, tHeight);
}

void Game::init(int tWidth, int tHeight){
	tickCount = 0;	
	skill_list.load(std::string("."));
	map = new Map();
	player = new Player();
	player->setName("PlayerMan");
	player->getName().c_str();
	player->setLoc(new Coord(10,10));
	target = new Coord(player->getLoc());
	map->getBlockAt(player->getLoc())->addEntity(player);

	ref = new Referee(this);
	display = new Display(this);
	display->setCenter(player);
	display->setTarget(target);
	
	//set up the offsets
	directionOffsets[0] = new Coord(0,-1);
	directionOffsets[1] = new Coord(1,-1);
	directionOffsets[2] = new Coord(1,0);
	directionOffsets[3] = new Coord(1, 1);
	directionOffsets[4] = new Coord(0,1);
	directionOffsets[5] = new Coord(-1,1);
	directionOffsets[6] = new Coord(-1,0);
	directionOffsets[7] = new Coord(-1,-1);


	Zombie* zombones = new Zombie();
	zombones->setLoc(new Coord(2,6));
	map->getBlockAt(zombones->getLoc())->addEntity(zombones);
	zombies.push_back(zombones);
	for ( int i = 0; i < 1000; i++) {
		zombones = new Zombie();
		zombones->setLoc(new Coord(rand() % 50, rand() % 50));
		map->getBlockAt(zombones->getLoc())->addEntity(zombones);
		zombies.push_back(zombones);
	}
	
	Item* foodItem = new Item();
	foodItem->setName("Chocolate Bar");
	foodItem->setType(Item::FOOD);
	foodItem->addSkill(skill_list.getSkillID("Consume"));
	foodItem->setDescription("A good-looking chocolate bar wrapped in foil.");
	player->getInventory()->addItem(foodItem);

	player->addAttribute(new Attribute("Strength", 10));

	Weapon* katana = new Weapon("Katana", 5);
	katana->addSkill(skill_list.getSkillID("Equip"));
	katana->setDescription("Damn, it's a ninja weapon!");
	map->getBlockAt(7,5)->addItem(katana);

	Weapon* weapon2 = new Weapon();
	weapon2->setName("Weapon2");
	map->getBlockAt(7,5)->addItem(weapon2);
	addMessage(new Message(weapon2->getListName().c_str()));
}
	
/**
 *	Force the redraw otherwise message isnt drawn 
 *	until the next tick.
 */
void Game::addMessage(Message *msg){
	messages.push_front(*msg->formatMsg(75));
	display->draw(getMessages());
}

/* returns an array of messages */
deque<Message> Game::getMessages(){
	return messages;
}

Player* Game::getPlayer(){
	return player;
}

Coord* Game::getTarget() {
	return target;
}

unsigned int Game::getTime(){
	return tickCount;
}

bool Game::isPassable(Coord* nextLoc){
	MapBlock* checkBlock = map->getBlockAt(nextLoc->getX(), nextLoc->getY());
	if (checkBlock->isPassable()){
		return true;
	}
	return false;
}

bool Game::moveEntity(Entity* ent, Direction dir){
	Coord *moveLoc = new Coord((*directionOffsets[dir]) + (*ent->getLoc()));
	if (moveLoc->getX() < 0 || moveLoc->getY() < 0 || moveLoc->getX() >= map->getWidth() || moveLoc->getY() >= map->getHeight()){
		return false; //can't move here, outside of map
	}
	if (isPassable(moveLoc)){
		map->getBlockAt(ent->getLoc())->removeEntity(ent);
		ent->setLoc(moveLoc);
		map->getBlockAt(ent->getLoc())->addEntity(ent);
	} else { //why is it not passable?
		MapBlock* checkBlock = map->getBlockAt(moveLoc->getX(), moveLoc->getY());
		if (checkBlock->hasEntities()){  //resolve an attack (what about friendly NPCs?)	
			Message msg;
			if (ref->resolveAttack(ent, checkBlock->getTopEntity(), &msg)) { //true means the battle was won
				checkBlock->removeEntity(checkBlock->getTopEntity());
			}
			//addMessage(&msg);
		} else {
			return false;
		}
	}
}

bool Game::move(Player* p, Direction dir){
	Coord *moveLoc = new Coord((*directionOffsets[dir]) + (*p->getLoc()));
	if (moveLoc->getX() < 0 || moveLoc->getY() < 0 || moveLoc->getX() >= map->getWidth() || moveLoc->getY() >= map->getHeight()){
		return false; //can't move here, outside of map
	}
	if (isPassable(moveLoc)){
		map->getBlockAt(p->getLoc())->removeEntity(p);
		p->setLoc(moveLoc);
		map->getBlockAt(p->getLoc())->addEntity(p);
	} else { //why is it not passable?
		MapBlock* checkBlock = map->getBlockAt(moveLoc->getX(), moveLoc->getY());
		if (checkBlock->hasEntities()){  //resolve an attack (what about friendly NPCs?)	
			Message msg;
			if (ref->resolveAttack(p, checkBlock->getTopEntity(), &msg)) { //true means the battle was won
				checkBlock->removeEntity(checkBlock->getTopEntity());
			}
			addMessage(&msg);
		} else {
			return false;
		}
	}		
	Message *msg = MessageFactory::getItems(map->getBlockAt(moveLoc)->getItems());
	if (msg) addMessage(msg);
	return true;
}

bool Game::move(Zombie* zombie, Direction dir){
	Coord *moveLoc = new Coord((*directionOffsets[dir]) + (*zombie->getLoc()));
	if (moveLoc->getX() < 0 || moveLoc->getY() < 0 || moveLoc->getX() >= map->getWidth() || moveLoc->getY() >= map->getHeight()){
		return false; //can't move here, outside of map
	}
	if (isPassable(moveLoc)){
		map->getBlockAt(zombie->getLoc())->removeEntity(zombie);
		zombie->setLoc(moveLoc);
		map->getBlockAt(zombie->getLoc())->addEntity(zombie);
	} else { //why is it not passable?
		MapBlock* checkBlock = map->getBlockAt(moveLoc->getX(), moveLoc->getY());
		if (checkBlock->hasEntities()){  //resolve an attack (what about friendly NPCs?)	
			Message msg;
			if (*player->getLoc() == *moveLoc) {
				if (ref->resolveAttack(zombie, checkBlock->getTopEntity(), &msg)) { //true means the battle was won
					checkBlock->removeEntity(checkBlock->getTopEntity());
				}
				addMessage(&msg);
			} else {
				; // wtf stop attacking other zombies
			}
			
		} else {
			return false;
		}
	}		
	return true;

}

void Game::moveTarget(Direction dir) {
	Coord moveLoc = (*directionOffsets[dir]) + (*getTarget());
	if (moveLoc.getX() < 0 || moveLoc.getY() < 0 || 
		moveLoc.getX() >= map->getWidth() || moveLoc.getY() >= map->getHeight()){
		//this->addMessage(new Message("You cannot move beyond here"));
		return; //can't move here, outside of map
	}
	target->setCoord(&moveLoc);

#if DEBUG
	char* msg = new char[255];
	sprintf(msg, "Target: (%d,%d)", target->getX(), target->getY());
	addMessage(new Message(msg));
#endif
	
	Message *msg = MessageFactory::getItems(map->getBlockAt(&moveLoc)->getItems());
	if (msg) addMessage(msg);
}



void Game::dropItem(int index){
	Coord* playerLoc = getPlayer()->getLoc();
	Inventory* playerInv = getPlayer()->getInventory();
	MapBlock* mapB = getMap()->getBlockAt(playerLoc->getX(), playerLoc->getY());
	if (playerInv->getSize() > 0){
		mapB->addItem(playerInv->getItemAt(index));
		playerInv->removeItemAt(index);
		//displayMapBlockInfo(map->getBlockAt(player->getLoc()));
//		display->refresh();
	}
}

void Game::pickUpItem(int index){
	Message* msg = new Message();
	if (map->getBlockAt(player->getLoc())->getItems().size() == 0){
		addMessage(new Message("There's nothing here"));
		return;
	}
	
	Item* item = map->getBlockAt(player->getLoc())->getItemAt(index);
	ref->pickUpItem(player,item, msg);
	map->getBlockAt(player->getLoc())->removeItem(item);
	addMessage(msg);
}

int Game::processKey(char key){
	if (key=='~') {
		
	} else if (key=='c'){ 
		display->toggleAttributes();
	} else if (key=='g'){
		if (!map->getBlockAt(player->getLoc())->getItems().empty()){
			if (map->getBlockAt(player->getLoc())->getItems().size() > 1) {
				display->toggleInventory(false);
				return 5;
			} else {
				// this could possibly break it, lets hope 
				// std::vector removes deadspace in the list.
				this->pickUpItem(0);
				return 2; //based on item bulk
			}
		}
	} else if (key=='m'){
		player->getAttribute("Strength")->changeCurValueBy(-1);
		Message* test = new Message("Strength reduced by 1");
		addMessage(test);
	} else if (key=='w') {
		move(player, NORTH);
		return 10; //based on speed
	} else if (key=='a') {
		move(player, WEST);
		return 10; //based on speed
	}  else if (key=='s') {
		move(player, SOUTH);
		return 10; //based on speed
	} else if (key=='d') {
		move(player, EAST);
		return 10; //based on speed
	} else if (key=='.') {
		return 10;
	} else if (key=='q') {
		//do some stuff, but for now
		return -1;
	} else if (key=='i') {
		addMessage(new Message("Inventory toggled"));
		display->toggleInventory(true);
		return 5;
	} else if (key == 'o') {
		moveTarget(NORTH);
	} else if (key == 'k') {
		moveTarget(WEST);
	} else if (key == 'l') {
		moveTarget(SOUTH);
	} else if (key == ';') {
		moveTarget(EAST);
	} else if (key == 'p') {
		display->togglePopup();
	}
	display->draw();
	return 0;
}

void Game::tick(){
	for (unsigned int i=0; i<zombies.size(); i++){
		Zombie* z = zombies.at(i);
		z->tick(this);
	}
}

void Game::draw(){
	display->draw();
}

void Game::run(){
	char input;
	int frameTime = 0;
	addMessage(MessageFactory::getMessage(skill_list.getSkill(0)->description));
#ifdef _GCC 
	addMessage(new Message("yay ming gcc")); 
#endif
	while (frameTime >= 0){
		frameTime = 0;
		//tick, draw, until something results in quitting
		this->tick();
		this->draw();
		refresh();
		input = getch();
		frameTime = display->processKey(input);
		if (frameTime <= -1){ //if display does not need to process the key 
			frameTime = this->processKey(input);	//if no windows are open, process in the game	
			this->target->setCoord(getPlayer()->getLoc());
		}
		for (int i = 0; i < zombies.size(); i++) {
			zombies.at(i)->tick(this);
		}
		tickCount += frameTime;
	}
}