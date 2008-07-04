#include <curses.h>
#include <sstream>
#include <math.h>

#include "game.h"
#include "referee.h"
#include "globals.h"
#include "keycodes.h"

EventDeque* Game::events = new EventDeque();
Game* Game::_instance = NULL;

Game::Game(){
//	init(100,100);
}

/* tWidth and tHeight represent the size of the world */
Game::Game(int tWidth, int tHeight){
//	init(tWidth, tHeight);
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
		addEvent(EventFactory::createSpawnEntityEvent(zombones, new Coord(rand() % 50, rand() % 50), 0));
		
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

	Door* door = PropFactory::createDoor(1000);
	map->getBlockAt(9,10)->addProp(door);

	Prop* chair = new Prop(true);
	chair->setName("Chair");
	chair->setDisplayChar('h');
	map->getBlockAt(8,8)->addProp(chair);

	map->getBlockAt(8,9)->addItem(WeaponFactory::createPistol());

	map->makeRoomAt(new Coord(7,7), 4,4);
	map->makeRoomAt(new Coord(15,15), 6, 8);
	
	ref->resolveEvents(0, getEventList());
}

Game* Game::getInstance() {
	if (_instance == NULL) {
		_instance = new Game();
	} 
	return _instance;
}

void Game::addMessage(Message *msg){
	messages.push_front(*msg->formatMsg(75));
}

EventDeque* Game::getEventList(){
	return events;
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

unsigned int Game::getTickcount(){
	return tickCount;
}

Time Game::getTime() {
	// 10ticks = 1s
	// 1minute = 600 ticks
	// 1 hr = 36000 ticks
	int ticks;
	Time t;
	t.hour = tickCount / 36000;
	t.hour = t.hour % 24;
	ticks = tickCount % 36000;
	t.minute = ticks / 600;
	ticks = ticks % 600;
	t.second = ticks / 10;
	return t;
}

bool Game::isPassable(Coord* nextLoc){
	MapBlock* checkBlock = map->getBlockAt(nextLoc->getX(), nextLoc->getY());
	if (!map->isWithinMap(nextLoc)) {
		return false;
	}
	if (checkBlock->isPassable()){
		return true;
	}
	return false;
}

bool Game::move(Player* p, Direction dir){
	/*Coord *moveLoc = new Coord((*directionOffsets[dir]) + (*p->getLoc()));
	if (map->isWithinMap(moveLoc)){
		MapBlock* checkBlock = map->getBlockAt(moveLoc->getX(), moveLoc->getY());
		addEvent(EventFactory::createMoveEvent(p, dir, 0));
		if (checkBlock->hasEntities()){

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

	}*/
	return false;
}

bool Game::move(Zombie* zombie, Direction dir){
	/*Coord *moveLoc = new Coord((*directionOffsets[dir]) + (*zombie->getLoc()));
	if (map->isWithinMap(moveLoc)){
		MapBlock* checkBlock = map->getBlockAt(moveLoc->getX(), moveLoc->getY());
		if (checkBlock->hasEntities()){
			if (!checkBlock->getTopEntity()->isPlayer()) { return false;} //don't attack or move onto other zombies
			addEvent(EventFactory::createAttackEvent(zombie, dir, 0));
			return true;
		} else if (checkBlock->hasProps() && !checkBlock->isPassable()) {
			zombie->resolveObstacle(this, dir);
		} else {
	//		map->getBlockAt(zombie->getLoc())->removeEntity(zombie);
	//		zombie->setLoc(moveLoc);
	//		map->getBlockAt(zombie->getLoc())->addEntity(zombie);
		}
	}*/
	return false;
}

void Game::moveTarget(Direction dir) {
	Coord moveLoc = (*directionOffsets[dir]) + (*getTarget());
	int deltaX = moveLoc.getX() - display->getCenter()->getLoc()->getX();
	int deltaY = moveLoc.getY() - display->getCenter()->getLoc()->getY();
	if (!map->isWithinMap(&moveLoc) || abs(deltaY) >= 17 || abs(deltaX) >= 27){

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
	int time;
	if (PDC_get_key_modifiers() & PDC_KEY_MODIFIER_CONTROL){
		Message message;
		Direction dir;
		switch(key)
		{
		case WIN_KEY_CTRL_W:
			dir = NORTH;
			break;
		case WIN_KEY_CTRL_A:
			dir = WEST;
			break;
		case WIN_KEY_CTRL_S:
			dir = SOUTH;
			break;
		case WIN_KEY_CTRL_D:
			dir = EAST;
			break;
		default:
			return 0;
		}
		time = ref->attackLocation(getPlayer(), &((*directionOffsets[dir]) + (*player->getLoc())), &message);
		addMessage(&message);
		return time;
	}
	else {
		//this is not only more efficient, but it looks a lot better
		//enough with the massive if chains
		switch(key)
		{
		case WIN_KEY_DEL:
			quitGame();
			return -1;
		case 'g':
			if(!map->getBlockAt(player->getLoc())->getItems().empty()){
				display->toggleInventory(false);
				return 5;
			}
			break;
		case 'f':
			//check for line of sight first, then
			Message* message = new Message();
			time = ref->attackRngLocation(player, getTarget(), message);
			addMessage(message);
			return time;
		case 'u':
			display->toggleAttributes();
		case 'q':
			addEvent(EventFactory::createMoveEvent(player, NORTHWEST, 0));
			return player->getSpeed();
		case 'w':
			addEvent(EventFactory::createMoveEvent(player, NORTH, 0));
			return player->getSpeed();
		case 'e':
			addEvent(EventFactory::createMoveEvent(player, NORTHEAST, 0));
			return player->getSpeed();
		case 'a':
			addEvent(EventFactory::createMoveEvent(player, WEST, 0));
			return player->getSpeed();
		case 's':
			return 10; //wait
		case 'd':
			addEvent(EventFactory::createMoveEvent(player, EAST, 0));
			return player->getSpeed();
		case 'z':
			addEvent(EventFactory::createMoveEvent(player, SOUTHWEST, 0));
			return player->getSpeed();
		case 'x':
			addEvent(EventFactory::createMoveEvent(player, SOUTH, 0));
			return player->getSpeed();
		case 'c':
			addEvent(EventFactory::createMoveEvent(player, SOUTHEAST, 0));
			return player->getSpeed();
		case 'Q':
			Coord focus = *player->getLoc() + *directionOffsets[NORTHWEST];
			return ref->interact(player, map->getBlockAt(&focus)->getTopProp());
		case 'W':
			Coord focus = *player->getLoc() + *directionOffsets[NORTH];
			return ref->interact(player, map->getBlockAt(&focus)->getTopProp());
		case 'E':
			Coord focus = *player->getLoc() + *directionOffsets[NORTHEAST];
			return ref->interact(player, map->getBlockAt(&focus)->getTopProp());
		case 'D':
			Coord focus = *player->getLoc() + *directionOffsets[EAST];
			return ref->interact(player, map->getBlockAt(&focus)->getTopProp());
		case 'C':
			Coord focus = *player->getLoc() + *directionOffsets[SOUTHEAST];
			return ref->interact(player, map->getBlockAt(&focus)->getTopProp());
		case 'X':
			Coord focus = *player->getLoc() + *directionOffsets[SOUTH];
			return ref->interact(player, map->getBlockAt(&focus)->getTopProp());
		case 'Z':
			Coord focus = *player->getLoc() + *directionOffsets[SOUTHWEST];
			return ref->interact(player, map->getBlockAt(&focus)->getTopProp());
		case 'A':
			Coord focus = *player->getLoc() + *directionOffsets[WEST];
			return ref->interact(player, map->getBlockAt(&focus)->getTopProp());
		case '.':
			return 10;
		case 'i':
			addMessage(new Message("Inventory toggled"));
			display->toggleInventory(true);
			return 5;
		case 'o':
			moveTarget(NORTH);
			break;
		case 'k':
			moveTarget(WEST);
			break;
		case 'l':
			moveTarget(SOUTH);
			break;
		case ';':
			moveTarget(EAST);
			break;
		case 'p':
			display->togglePopup();
			break;
		default: break;
		}
	}

	// i hope this is redundant -.-
	// so do I. things haven't broken yet though.
	//display->draw();
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

	//check events here
	ref->resolveEvents(getTickcount(), getEventList());
	
}

void Game::draw(){
	display->draw();
}

void Game::run(){
	char input;
	int frameTime = 0;
	addMessage(MessageFactory::getMessage(skill_list.getSkill(0)->getDescription()));
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
		if (frameTime >= 0) {
			this->tick();
		}
		tickCount += frameTime;
	}
}

vector<Coord>* Game::getRay(Coord *start, Coord *target) {
	int dir;
	vector<Coord> *ray = new vector<Coord>();
	// check for redundant ray
	if (*target == *(player->getLoc())) {
		return NULL;
	}
	float slope;
	if (target->getX() - start->getX()) {
		// a = slope = (y2 - y1) / (x2 - x1)
		// y2 - y1 = a(x2 - x1)
		float dx, dy;
		dy = (target->getY() - start->getY());
		dx = (target->getX() - start->getX());
		slope =  dy / dx ;
		// check which is the dominant axis, (i.e. dx > dy?)
		// iterate over the longer one to ensure no gaps in ray

		if (slope > -1 && slope < 1) {
			float y;
			dir = (start->getX() > target->getX()) ? -1 : 1;
			for (int x = start->getX(); x != target->getX(); x+=dir) {
				y = slope * (x - start->getX()) + start->getY();
				float flor = floor(y);
				if (y - flor > 0.5) {
					ray->push_back(Coord(x, ceil(y)));
				} else {
					ray->push_back(Coord(x,flor));
				}
			}
		} else {
			float x;
			dir =  (start->getY() > target->getY()) ? -1 : 1;

			for (int y = start->getY(); y != target->getY(); y+=dir) {
				x = ((y - start->getY()) / slope) + start->getX();
				float flor = floor(x);
				if (x - flor > 0.5) {
					ray->push_back(Coord(ceil(x), y));
				} else {
					ray->push_back(Coord(flor,y));
				}
			}
		}
	} else { // vertical line, simple case

		dir =  (start->getY() > target->getY()) ? -1 : 1;
		for (int y = start->getY(); y != target->getY(); y+=dir) {
			ray->push_back(Coord(start->getX(), y));
		}
	}


	ray->push_back(Coord(target->getX(), target->getY()));
	return ray;
}


void Game::addEvent(Event* e){
	getEventList()->addNode(e);
}
