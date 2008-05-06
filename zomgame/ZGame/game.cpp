
#include <curses.h>
#include "game.h"
#include "referee.h"

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
	display = new Display(this);
	display->setTarget(player);
	
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

	map->getBlockAt(6,6)->addItem(new Item());
	map->getBlockAt(1,1)->addEntity(ent1);
	Zombie* zombones = new Zombie();
	zombones->setLoc(new Coord(2,6));
	map->getBlockAt(zombones->getLoc())->addEntity(zombones);
	zombies.push_back(zombones);
	Item* item1 = new Item();
	item1->setName("Item1");
	Item* item2 = new Item();
	item2->setName("Item2");
	Item* item3 = new Item();
	item3->setName("Item3");
	Item* item4 = new Item();
	item4->setName("Item4");
	Item* item5 = new Item();
	item5->setName("Item5");
	Item* item6 = new Item();
	item6->setName("Item6");
	Item* item7 = new Item();
	item7->setName("Item7");
	Item* item8 = new Item();
	item8->setName("Item8");
	Item* item9 = new Item();
	item9->setName("Item9");
	Item* item10 = new Item();
	item10->setName("Item10");
	
	player->getInventory()->addItem(item1);
	player->getInventory()->addItem(item2);
	player->getInventory()->addItem(item3);
	player->getInventory()->addItem(item4);
	player->getInventory()->addItem(item5);
	player->getInventory()->addItem(item6);
	player->getInventory()->addItem(item7);
	player->getInventory()->addItem(item8);
	player->getInventory()->addItem(item9);
	player->getInventory()->addItem(item10);

	Weapon* weapon1 = new Weapon();
	map->getBlockAt(7,5)->addItem(weapon1);
	Weapon* weapon2 = new Weapon();
	weapon2->setName("Weapon2");
	map->getBlockAt(7,5)->addItem(weapon2);
	
	/*Prop* wall1 = new Prop();
	wall1->setName("Wall");
	wall1->setDisplayChar(ACS_CKBOARD);
	wall1->setPassable(false);
	map->getBlockAt(5,5)->addProp(wall1);
	wall1 = new Prop();
	wall1->setName("Wall");
	wall1->setDisplayChar(ACS_CKBOARD);
	wall1->setPassable(false);
	map->getBlockAt(5,6)->addProp(wall1);*/
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

void Game::moveEntity(Entity* ent, direction dir){
	Coord moveLoc = (*directionOffsets[dir]) + (*ent->getLoc());
	if (moveLoc.getX() < 0 || moveLoc.getY() < 0 || 
		moveLoc.getX() >= map->getWidth() || moveLoc.getY() >= map->getHeight()){
		//this->addMessage(new Message("You cannot move beyond here"));
		return; //can't move here, outside of map
	}
	if (isPassable(&moveLoc)){
		map->getBlockAt(ent->getLoc())->removeEntity(ent);
		ent->setLoc(&moveLoc);
		map->getBlockAt(ent->getLoc())->addEntity(ent);
	} else { //why is it not passable?
		MapBlock* checkBlock = map->getBlockAt(moveLoc.getX(), moveLoc.getY());
		if (checkBlock->hasEntities()){  //resolve an attack (what about friendly NPCs?)	
			Message msg;
			if (ref->resolveAttack(ent, checkBlock->getTopEntity(), &msg)) { //true means the battle was won
				checkBlock->removeEntity(checkBlock->getTopEntity());
				addMessage(&msg);
			}

		}
	}
}

void Game::dropItem(int index){
	Coord* playerLoc = getPlayer()->getLoc();
	Inventory* playerInv = getPlayer()->getInventory();
	MapBlock* mapB = getMap()->getBlockAt(playerLoc->getX(), playerLoc->getY());
	if (playerInv->getSize() > 0){
		mapB->addItem(playerInv->getItemAt(index));
		playerInv->removeItemAt(index);
		//showItemDetail = false;
	}
}

void Game::pickUpItem(int index){
	Message* msg = new Message();
	Item* item = map->getBlockAt(player->getLoc())->getItemAt(index);
	ref->pickUpItem(player,item, msg);
	map->getBlockAt(player->getLoc())->removeItem(item);
	addMessage(msg);
}

bool Game::processKey(char key){
	if (key=='~') {

	} else if (key=='g'){
		if (!map->getBlockAt(player->getLoc())->getItems().empty()){
			display->toggleInventory();
		}
	} else if (key=='m'){
		Message* test = new Message("Testing\n123");
		addMessage(test);
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
	} else if (key=='i') {
		addMessage(new Message("Inventory toggled"));
		display->toggleInventory();
	}
	display->draw();
	return true;
}

void Game::tick(){
	for (int i=0; i<zombies.size(); i++){
		Zombie* z = zombies.at(i);
		z->tick(this);
	}
}

void Game::draw(){
	display->draw();
}

void Game::run(){
	char input;
	bool keepPlaying = true;
	while (keepPlaying){
		//tick, draw, until something results in quitting
		this->tick();
		this->draw();
		refresh();
		input = getch();
		if (display->invIsToggled()) { //process the key in the inventory screen
			display->processKey(input);
		} else if (false) { //status is toggled, etc

		} else {
			keepPlaying = this->processKey(input);	//if no windows are open, process in the game	
		}
	}
}

bool Game::isPassable(Coord* nextLoc){
	MapBlock* checkBlock = map->getBlockAt(nextLoc->getX(), nextLoc->getY());
	if (checkBlock->isPassable()){
		return true;
	}
	return false;
}