
#include <curses.h>
#include "game.h"
#include "referee.h"
#include "globals.h"
#include "keycodes.h"
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
	for ( int i = 0; i < 100; i++) {
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

	Weapon* katana = new Weapon("Katana", 1000);
	katana->setDescription("Damn, it's a ninja weapon!");
	map->getBlockAt(7,5)->addItem(katana);

	Door* door = PropFactory::createDoor(100000);
	map->getBlockAt(9,10)->addProp(door);

	Prop* chair = new Prop(true);
	chair->setName("Chair");
	chair->setDisplayChar('h');
	map->getBlockAt(8,8)->addProp(chair);

	Weapon* gun = new Weapon("Gun", 10);
	gun->setWType(Weapon::RANGED);
	map->getBlockAt(12,12)->addItem(gun);

	Prop* wall = new Prop(false);
	wall->setName("Wall");
	map->getBlockAt(7,7)->addProp(PropFactory::createWall(1000));
	map->getBlockAt(7,8)->addProp(PropFactory::createWall(1000));
	map->getBlockAt(7,9)->addProp(PropFactory::createWall(1000));
	map->getBlockAt(7,10)->addProp(PropFactory::createWall(1000));
	map->getBlockAt(8,10)->addProp(PropFactory::createWall(1000));
	map->getBlockAt(10,10)->addProp(PropFactory::createWall(1000));
	map->getBlockAt(10,9)->addProp(PropFactory::createWall(1000));
	map->getBlockAt(10,8)->addProp(PropFactory::createWall(1000));
	map->getBlockAt(10,7)->addProp(PropFactory::createWall(1000));
	map->getBlockAt(9,7)->addProp(PropFactory::createWall(1000));
	map->getBlockAt(8,7)->addProp(PropFactory::createWall(1000));
}

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
	if (!map->isWithinMap(nextLoc)){
		return false;
	}
	if (checkBlock->isPassable()){
		return true;
	}
	return false;
}

bool Game::move(Player* p, Direction dir){
	Coord *moveLoc = new Coord((*directionOffsets[dir]) + (*p->getLoc()));
	if (map->isWithinMap(moveLoc)){
		MapBlock* checkBlock = map->getBlockAt(moveLoc->getX(), moveLoc->getY());
		if (checkBlock->hasEntities()){
			Message msg;
			ref->resolveAttack(p, checkBlock->getTopEntity(), &msg); //does the removing 
			addMessage(&msg);
			return true;
		} else if (checkBlock->hasProps() && !checkBlock->isPassable()) {
			if (checkBlock->getTopProp()->getName() == "Door" && !checkBlock->getTopProp()->isPassable()) {
				checkBlock->getTopProp()->interact(player);
			}
		} else {
			map->getBlockAt(p->getLoc())->removeEntity(p);
			p->setLoc(moveLoc);
			map->getBlockAt(p->getLoc())->addEntity(p);
			Message *msg = MessageFactory::getItems(map->getBlockAt(moveLoc)->getItems());
			if (msg) {addMessage(msg);}
			this->target->setCoord(getPlayer()->getLoc());
		} 
		
	}
	return false;
}

bool Game::move(Zombie* zombie, Direction dir){
	Coord *moveLoc = new Coord((*directionOffsets[dir]) + (*zombie->getLoc()));
	if (map->isWithinMap(moveLoc)){
		MapBlock* checkBlock = map->getBlockAt(moveLoc->getX(), moveLoc->getY());
		if (checkBlock->hasEntities()){
			if (*player->getLoc() != *moveLoc) { return false;} //don't attack or move onto other zombies
			Message msg;
			ref->resolveAttack(zombie, checkBlock->getTopEntity(), &msg); //does the removing 
			addMessage(&msg);
			return true;
		} else if (checkBlock->hasProps() && !checkBlock->isPassable()) {
			zombie->resolveObstacle(this, dir);
		} else {
			map->getBlockAt(zombie->getLoc())->removeEntity(zombie);
			zombie->setLoc(moveLoc);
			map->getBlockAt(zombie->getLoc())->addEntity(zombie);
		} 	
	}
	return false;
}

void Game::moveTarget(Direction dir) {
	Coord moveLoc = (*directionOffsets[dir]) + (*getTarget());
	if (moveLoc.getX() < 0 || moveLoc.getY() < 0 || 
		moveLoc.getX() >= map->getWidth() || moveLoc.getY() >= map->getHeight()){
		return; //can't move here, outside of map
	}
	target->setCoord(&moveLoc);
	Message *msg = MessageFactory::getItems(map->getBlockAt(&moveLoc)->getItems());
	if (msg) addMessage(msg);
}

int Game::processKey(int key){
	//char ikey[4];
	//itoa(key, ikey, 10);
	//addMessage(new Message(&ikey[0]));
	if (PDC_get_key_modifiers() & PDC_KEY_MODIFIER_CONTROL){
		if (key==WIN_KEY_CTRL_W){
			Message message;
			ref->attackLocation(getPlayer(), getMap()->getBlockAt(&((*directionOffsets[NORTH])+(*player->getLoc()))), &message); 	
			addMessage(&message);
			return 5;
		} else if (key==WIN_KEY_CTRL_A){
			Message message;
			ref->attackLocation(getPlayer(), getMap()->getBlockAt(&((*directionOffsets[WEST])+(*player->getLoc()))), &message); 	
			addMessage(&message);
			return 5;
		} else if (key==WIN_KEY_CTRL_S){
			Message message;
			ref->attackLocation(getPlayer(), getMap()->getBlockAt(&((*directionOffsets[SOUTH])+(*player->getLoc()))), &message); 	
			addMessage(&message);
			return 5;
		} else if (key==WIN_KEY_CTRL_D){
			Message message;
			ref->attackLocation(getPlayer(), getMap()->getBlockAt(&((*directionOffsets[EAST])+(*player->getLoc()))), &message); 	
			addMessage(&message);
			return 5;
		}
	} else if(key == WIN_KEY_DEL) {
		quitGame();
		return -1;
	} else if (key=='~') {
		
	} else if (key=='g'){
		if (!map->getBlockAt(player->getLoc())->getItems().empty()){
			display->toggleInventory(false);
			return 5;
		}
	} else if (key=='f'){
		//check for line of sight first, then
		Message* message = new Message();
		ref->attackRngLocation(player, map->getBlockAt(getTarget()), message);	
		addMessage(message);
		
	}
#if DEBUG 
	else if (key=='m'){
		/*player->getAttribute("Strength")->changeCurValueBy(-1);
		Message* test = new Message("Strength reduced by 1");
		addMessage(test);
		*/
		char buf[128];
		sprintf(&buf[0], "Querying (%d,%d)", target->getX(), target->getY());
		addMessage(map->getBlockAt(this->getTarget())->getBlockInfo());
		addMessage(new Message(new std::string(buf)));
		
	}
#endif

	else if (key=='q') {
		move(player, NORTHWEST); return 10; //based on speed
	} else if (key=='w') {
		move(player, NORTH); return 10; //based on speed
	} else if (key=='e') {
		move(player, NORTHEAST); return 10; //based on speed
	} else if (key=='a') {
		move(player, WEST); return 10; //based on speed
	} else if (key=='s') {
		return 10; //wait
	} else if (key=='d') {
		move(player, EAST); return 10; //based on speed
	} else if (key=='z') {
		move(player, SOUTHWEST); return 10; //based on speed
	} else if (key=='x') {
		move(player, SOUTH); return 10; //based on speed
	} else if (key=='c') {
		move(player, SOUTHEAST); return 10; //based on speed
	} else if (key=='Q') {
		Coord focus = *player->getLoc() + *directionOffsets[NORTHWEST];
		return ref->interact(player, map->getBlockAt(&focus)->getTopProp());
	} else if (key=='W') {
		Coord focus = *player->getLoc() + *directionOffsets[NORTH];
		return ref->interact(player, map->getBlockAt(&focus)->getTopProp());
	} else if (key=='E') {
		Coord focus = *player->getLoc() + *directionOffsets[NORTHEAST];
		return ref->interact(player, map->getBlockAt(&focus)->getTopProp());
	} else if (key=='D') {
		Coord focus = *player->getLoc() + *directionOffsets[EAST];
		return ref->interact(player, map->getBlockAt(&focus)->getTopProp());
	} else if (key=='C') {
		Coord focus = *player->getLoc() + *directionOffsets[SOUTHEAST];
		return ref->interact(player, map->getBlockAt(&focus)->getTopProp());
	} else if (key=='X') {
		Coord focus = *player->getLoc() + *directionOffsets[SOUTH];
		return ref->interact(player, map->getBlockAt(&focus)->getTopProp());
	} else if (key=='Z') {
		Coord focus = *player->getLoc() + *directionOffsets[SOUTHWEST];
		return ref->interact(player, map->getBlockAt(&focus)->getTopProp());
	} else if (key=='A') {
		Coord focus = *player->getLoc() + *directionOffsets[WEST];
		return ref->interact(player, map->getBlockAt(&focus)->getTopProp());
	} else if (key=='.') { return 10;
	} else if (key=='i') {
		addMessage(new Message("Inventory toggled"));
		display->toggleInventory(true);
		return 5;
	} else if (key == 'o') { moveTarget(NORTH);
	} else if (key == 'k') { moveTarget(WEST);
	} else if (key == 'l') { moveTarget(SOUTH);
	} else if (key == ';') { moveTarget(EAST);
	} else if (key == 'p') {
		display->togglePopup();
	}
	display->draw();
	return 0;
}

void Game::quitGame(){
	
}

void Game::tick(){
	for (unsigned int i=0; i<zombies.size(); i++){
		Zombie* z = zombies.at(i);
		if (z->getAttribute("Health")->getCurValue()) {
			z->tick(this); 
		} else {
			// respawn the zombie
			Coord c;
			do {
				c = Coord(rand() % map->getWidth(), rand() % map->getHeight());
			} while(!map->getBlockAt(c.getX(), c.getY())->isPassable() && !map->getBlockAt(c.getX(), c.getY())->hasEntities());
			
			char bufA[128];
			char bufB[128];
			sprintf(&bufA[0],"Respawn zombie @ (%d,%d)", z->getLoc()->getX(), z->getLoc()->getY());			
			
			//map->getBlockAt(z->getLoc())->removeEntity(z);
			z->respawn(new Coord(c));
			sprintf(&bufB[0],"Zombie moved to (%d,%d)", z->getLoc()->getX(), z->getLoc()->getY());
			addMessage(new Message(new std::string(bufB)));
			addMessage(new Message(new std::string(bufA)));
			map->getBlockAt(&c)->addEntity(z);
			z->tick(this);
		}
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
		
		this->draw();
		refresh();
		input = getch();
		frameTime = display->processKey(input);
		if (frameTime <= -1){ //if display does not need to process the key 
			frameTime = this->processKey(input);	//if no windows are open, process in the game				
		}
		if (frameTime > 0) {
			this->tick();
		}
		tickCount += frameTime;
	}
}