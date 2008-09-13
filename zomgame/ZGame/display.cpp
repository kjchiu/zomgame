#include "display.h"
#include "keycodes.h"
#include <deque>

using namespace std;

Display::Display(Game* game) {
	init();
	this->game = game;
}

void Display::init() {
	resize_term(50,80);
	playWin = newwin(35,55,0,0); //height, width, starty, startx
	msgWin = newwin(15,80,35,0); 
	menuWin = newwin(35,25,0,55); 
	invWin = newwin(11,80,35,0); //displays the inventory
	popupWin = new PopupWin(10, 30, 20, 20);

	showItemDetail = false;
	groundSelection = -1;
	
	dState = new DisplayState();
	dState->init();
	
	popupSelection = 0;
	

	leftInv = new ScrollableList();
	rightInv = new ScrollableList();
	

	camera = new Camera();
	camera->setViewableArea(33, 53); //height - 2, width - 2;
	start_color();

	// TODO: we really need to move colour palette stuff somewhere else
	if (can_change_color())
		init_color(15, 0, 1000, 1000);
	init_pair(WHITE_BLACK, COLOR_WHITE, COLOR_BLACK);
	init_pair(GREEN_BLACK, COLOR_GREEN, COLOR_BLACK);
	init_pair(RED_BLACK, COLOR_RED, COLOR_BLACK);
	init_pair(CYAN_BLACK, COLOR_CYAN, COLOR_BLACK);
	init_pair(YELLOW_BLACK, COLOR_YELLOW, COLOR_BLACK);  
	init_pair(MAGENTA_BLACK, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, 15, COLOR_BLACK);
#define TARGET_COLOR COLOR_RED
#define TARGET_PAIR 6
}

/* Puts the selections within correct boundaries */
void Display::cleanSelections(){
	int invSize = game->getPlayer()->getInventory()->getSize();
	if (inventorySelection < 0){ inventorySelection += invSize; }
	if (invSize == 0){ inventorySelection = 0; }
		else { inventorySelection %= invSize; }
	if (inventorySelection > maxIndex){
		minIndex += inventorySelection - maxIndex;
		maxIndex += inventorySelection - maxIndex;
	} else if (inventorySelection < minIndex){
		maxIndex -= minIndex - inventorySelection;
		minIndex -= minIndex - inventorySelection;
	}
	
	//same for the groundSelection
	int groundSize = static_cast<int>(game->getMap()->getBlockAt(game->getPlayer()->getLoc())->getItems()->size());
	if (groundSelection < 0){ groundSelection += groundSize; }
	if (groundSize == 0){ groundSelection = 0; }
		else {groundSelection %= groundSize; }
	if (groundSelection > maxGIndex){
		minGIndex += groundSelection - maxGIndex;
		maxGIndex += groundSelection - maxGIndex;
	} else if (groundSelection < minGIndex){
		maxGIndex -= minGIndex - groundSelection;
		minGIndex -= minGIndex - groundSelection;
	}
}

// pulls down necessary data from game to draw
void Display::draw() {
	if (dState->attrIsToggled()){
		drawCharacterInfo();
	} else {
		this->draw(game->getMap());
	}

	this->draw(game->getMessages());
	if (invIsToggled()){
		this->draw(game->getPlayer()->getInventoryStrings());
	}

	draw(game->getPlayer(), game->getMap()->getBlockAt(game->getTarget()));
}

void Display::draw(Map* map) {
	//VISIBLE WORLD -- Kyle did you just make a lolcat reference? Oh my.
	box(playWin, 0,0);
	wclear(playWin);
	
	int height, width;
	getmaxyx(playWin,height,width);
	height -= 2;
	width -= 2;
	chtype* view = camera->getViewableArea(map, getCenter());
	Coord transTarget = camera->getLocalCoordinates(target, getCenter());
	Coord p = camera->getLocalCoordinates(game->getPlayer()->getLoc(), getCenter());
	for (int x=0; x<width; x++){
		for (int y=0; y<height; y++){
			int index = x + (y * width);	
			// if on targeted block
			// and target is no underneath player
			if (x == transTarget.getX() && y == transTarget.getY()
				&& !target->equals(getCenter()->getLoc())) {

				short fg, bg;
				// grab foreground colour of block
				pair_content(map->getBlockAt(target)->getColor(), &fg, &bg);
				// generate new pair using block fg + red bg
				init_pair(TARGET_PAIR, fg, TARGET_COLOR);
				wattron(playWin, COLOR_PAIR(TARGET_PAIR));
				mvwaddch(playWin, y+1, x+1, (char)view[index]);
				wattroff(playWin, COLOR_PAIR(TARGET_PAIR));
			} else {			
				mvwaddch(playWin, y+1, x+1, view[index]);	
			}			
		}
	}

	//the line of aiming if 'target' has been moved
	vector<Coord>* ray = game->getRay(game->getPlayer()->getLoc(), game->getTarget());
	
	if (ray) {
		Coord c;
		for (unsigned int i = 0; i < ray->size(); i++) {
			c = ray->at(i);
			c = camera->getLocalCoordinates(&c, getCenter());
			short fg, bg;
			// grab foreground colour of block
			pair_content(map->getBlockAt(&c)->getColor(), &fg, &bg);
			// generate new pair using block fg + red bg
			init_pair(TARGET_PAIR, fg, TARGET_COLOR);
			wattron(playWin, COLOR_PAIR(TARGET_PAIR));
			mvwaddch(playWin, c.getY()+1, c.getX()+1, (char)view[c.getX() + c.getY() * width]);
			wattroff(playWin, COLOR_PAIR(TARGET_PAIR));
		}
	}
	//now display it in the play window (playWin)
	wrefresh(playWin);
	
}


void Display::draw(deque<Message> msgs) {
	wclear(msgWin);
	unsigned int height, width, offset = 1; 
	getmaxyx(msgWin,height,width);
	for (unsigned int i=0; i<height-2 && i<msgs.size();i++){
		string text = *(msgs.at(i)).getMsg(); //remove the pointer to avoid modifying the original message
		unsigned int cutoff = width; //preserving the value of windowLength
		mvwprintw(msgWin, i+offset, 1, "> %s\n", text.c_str());
		offset += msgs.at(i).getNumLines();
	}

	//then draw the box and refresh the window
	box(msgWin, 0,0);
	mvwprintw(msgWin, 0, 3, "MESSAGE LOG");
	wrefresh(msgWin);
	
}

void Display::draw(vector<string*>* inventoryStrings){
	wclear(invWin);
	leftInv->setList(inventoryStrings);
	int height, width;
	getmaxyx(invWin, height, width);
	//vector<Item*>* groundInv = &(game->getMap()->getBlockAt(game->getPlayer()->getLoc())->getItems());
	vector<string*>* groundInvStrings = this->getItemStrings(game->getRightInvList());
	//I need to set rightInv elsewhere, for shizzle.
	rightInv->setList(groundInvStrings);

	if (groundInvStrings->empty()){
		dState->invSide = true;
	} 
	if (inventoryStrings->size() == 0){
		dState->invSide = false;
	}
	if (showItemDetail && (inventoryStrings->size() > 0 || groundInvStrings->size() > 0 )){ //if the user wants to see the details of an item
		if (dState->invIsHighlighted() && dState->invSide) { //check the inventory selection
			drawItemDetails(game->getPlayer()->getInventory()->getItemAt(leftInv->getSelectedIndex()), height, width);	
		} else { //check the ground selection
			drawItemDetails(game->getMap()->getBlockAt(game->getPlayer()->getLoc())->getItemAt(rightInv->getSelectedIndex()), height, width);
		} 	
	} else {		//otherwise, draw the full inventory
		for (int i=1; i<height-1; i++){	//draw the center column
			mvwprintw(invWin, i, width/2, "|");
		}
		drawInventoryList(leftInv, 3, dState->invIsHighlighted());
		drawInventoryList(rightInv, width/2 + 4, !dState->invIsHighlighted());
	}

	//draw the skills popup if necessary
	if (popupIsToggled()) {
		popupWin->draw(); 
	}

	box(invWin, 0,0);
	mvwprintw(invWin, 0, 3, "POSSESSIONS");
	mvwprintw(invWin, 0, width/2+3, "GROUND");
	wrefresh(invWin);		
}

void Display::draw(Player* player, MapBlock* block){
	wclear(menuWin); //first clear the window

	string condition = "Healthy";
	//player = game->getPlayer();
	int curHealth = player->getAttribute("Health")->getCurValue(), 
		maxHealth = player->getAttribute("Health")->getMaxValue();
	if (curHealth < maxHealth/1){condition = "Slightly Wounded";}
	if (curHealth < maxHealth/2){condition = "Wounded";}
	if (curHealth < maxHealth/3){condition = "Badly Wounded";}
	if (curHealth < maxHealth/4){condition = "Critical";}
	if (curHealth < maxHealth/5){condition = "Near Death";}
	
	mvwprintw(menuWin, 1, 2, "%s", game->getPlayer()->getName().c_str());
	mvwprintw(menuWin, 2, 2, "Condition: %d/%d", curHealth, maxHealth);
	mvwprintw(menuWin, 3, 2, "Weapon: %s", player->getEquippedWeapon()->getName().c_str());
	mvwprintw(menuWin, 4, 2, "RngWeapon: %s", player->getEqRngWeapon() ? player->getEqRngWeapon()->getName().c_str() : "nothing");
	mvwprintw(menuWin, 5, 2, "Strength: %d", player->getAttribute("Strength")->getCurValue());
	mvwprintw(menuWin, 6, 2, "WeapDur: %d/%d", player->getEquippedWeapon()->getDurability()->getCurValue(), 
									player->getEquippedWeapon()->getDurability()->getMaxValue());
	Time t = game->getTime();
	mvwprintw(menuWin, getmaxy(menuWin) / 2 - 2, 2, "Time: %d:%d:%2.1f", t.hour, t.minute, t.second);
	mvwprintw(menuWin, getmaxy(menuWin) / 2 - 1, 2, "TickCount: %d", game->getTickcount());
	
	mvwprintw(menuWin, 8, 2, "EventListSize: %d", game->getEventList()->getSize());
	
	//draw the mapblock info
	int halfway = getmaxy(menuWin)/2;
	if (block->hasEntities()){
		mvwprintw(menuWin, halfway+1, 2, "Entity: %s", block->getTopEntity()->getName().c_str());
		mvwprintw(menuWin, halfway+2, 3,  "Health: %d", block->getTopEntity()->getAttribute("Health")->getCurValue());
	}
	if (block->hasProps()){
		mvwprintw(menuWin, halfway+4, 2, "Prop: %s", block->getTopProp()->getName().c_str());
		mvwprintw(menuWin, halfway+5, 3,  "Durability: %d", block->getTopProp()->getHealth()->getCurValue());
	}
	if (block->getItems()->size() > 0){
		mvwprintw(menuWin, halfway+7, 2, "Items");
		for (unsigned int i = 0; i < block->getItems()->size(); i++){
			mvwprintw(menuWin, i+halfway+8, 3, "%s", block->getItemAt(i)->getListName().c_str());
		}
	}
	//draw the box + dividing line
	box(menuWin, 0,0);
	mvwprintw(menuWin, 0, 3, "PLAYER");
	mvwaddch(menuWin, halfway, 0, ACS_LTEE);
	for (int i = 1; i<  getmaxx(menuWin) - 1; i++){
		mvwaddch(menuWin, halfway, i, ACS_HLINE);
	}
	mvwaddch(menuWin, halfway, getmaxx(menuWin) - 1, ACS_RTEE);
	mvwprintw(menuWin, halfway, 2, "INFO");
	wrefresh(menuWin);
}

void Display::drawCharacterInfo(){
	wclear(playWin);
	int height, width;
	getmaxyx(playWin, height, width);
	Player* p = game->getPlayer();
	//character name, equipped weapons, skills
	mvwprintw(playWin, 2,2, "Name: %s", p->getName().c_str());
	mvwprintw(playWin, 4,2, "ATTRIBUTES");
	vector<Attribute*>* attributeList = p->getAttributes();
	for (unsigned int j = 0; j < attributeList->size(); j++){
		mvwprintw(playWin, j+5,2, "%s: %d/%d", attributeList->at(j)->getName().c_str(), attributeList->at(j)->getCurValue(), attributeList->at(j)->getMaxValue());
	}

	mvwprintw(playWin, 1, width-20, "SKILLS");
	for (unsigned int i = 0; i < p->getSkills()->size(); i++){
		if (skill_list.getSkill(i)->getType() != INHERENT){
			mvwprintw(playWin, i+2, width-20, "%-12s - %d", skill_list.getSkill(i)->getName().c_str(), p->getSkillValue(i));
		}
	}
	
	box(playWin, 0,0);
	mvwprintw(playWin, 0, 3, "CHARACTER INFO");
	wrefresh(playWin);
}

void Display::drawInventoryList(ScrollableList* inv, int xPos, bool highlight){
	int height, width, offset;
	string* itemName;
	Item* item;
	
	getmaxyx(invWin, height, width);
	offset = inv->getDisplayOffset(height-2, 0);

	for (int i=0; i<9;i++){
		itemName = inv->getStringForPosition(i, 9);
		item = game->getPlayer()->getInventory()->getItemAt(i+offset);
		if (i + offset == inv->getSelectedIndex() && highlight) {  //if the item is highlighted
			wattron(invWin, COLOR_PAIR(YELLOW_BLACK));
			*itemName = "-" + *itemName + "-";
		} else { 
			*itemName = " " + *itemName; 
		}
		if (item != NULL && xPos < width/2) {				//if this is on the left side
			if (item == game->getPlayer()->getEquippedWeapon() || //and the weapon is equipped
				item == game->getPlayer()->getEqRngWeapon()){
				*itemName = "E " + *itemName;
			} else {
				*itemName = "  " + *itemName;
			}
		}
		mvwprintw(invWin,i+1,xPos, "%s", itemName->c_str());
		wattroff(invWin, COLOR_PAIR(YELLOW_BLACK));
	}
}

void Display::drawItemDetails(Item* item, int height, int width){
	mvwprintw(invWin, 2, 3, item->getName().c_str());
	mvwprintw(invWin, 4, 5, item->getDescription().c_str());
	mvwprintw(invWin, height-2, 4, "Weight: %d lbs", item->getWeight());
	mvwprintw(invWin, height-2, width-20, "Bulk: %d", item->getBulk()); 
	mvwprintw(invWin, height-2, 40, "Type: %s", item->getTypeString().c_str());
	if (item->getTypeString().compare("Weapon") == 0) { //display weapon stats if its a weapon
		Weapon* weapon = (Weapon*)item;
		mvwprintw(invWin, 2, width-30, "Weapon Class: %s", weapon->getWTypeString().c_str());
		mvwprintw(invWin, 3, width-30, "Durability: %d/%d", weapon->getDurability()->getCurValue(), weapon->getDurability()->getMaxValue());
		mvwprintw(invWin, 4, width-30, "Base Damage: %d", weapon->getDamage());
	}
}

void Display::drawPopup(Item* item){
	popupWin->draw();
}

/* Says whether or not the game should be ticking */
bool Display::gameIsActive(){
	return dState->mapIsToggled();
}

Entity* Display::getCenter() {
	return center;
}

vector<string*>* Display::getItemStrings(vector<Item*>* itemList){
	vector<string*>* stringList = new vector<string*>();

	for (unsigned int i = 0; i < itemList->size(); i++){
			stringList->push_back(new string(itemList->at(i)->getName()));
	}
	
	return stringList;
}

bool Display::invIsToggled(){
	return dState->invIsToggled();
}

bool Display::popupIsToggled(){
	return dState->popupIsToggled();
}

/* Decides what context to process the key in. Returns false if no context */
int Display::processKey(int input){
	if (input == WIN_KEY_ESC) {
		if (dState->popupIsToggled()) {
			togglePopup();
			showItemDetail = false;
		} else if (dState->invIsToggled()) {
			toggleInventory(true);
		} else if (dState->attrIsToggled()) {
			toggleAttributes();
		}
	} else if (popupIsToggled()){
		return this->processKeyUseItem(input);
	} else if (invIsToggled()){
		return this->processKeyInventory(input);
	} else if (dState->attrIsToggled()){
		return processKeyAttributes(input);
	}
	return 0;
}

int Display::processKeyAttributes(int input){
	if (input == 'u'){
		dState->toggleAttr();
	}
	return 0;
}

int Display::processKeyInventory(int input){
	wclear(invWin);
	if (input == 'i'){
		leftInv->resetIndex();
		rightInv->resetIndex();
		showItemDetail = false;
		this->toggleInventory(true);
		return 5;
	} else if (input == WIN_KEY_DOWN) { //down
		if (dState->invIsHighlighted()){ leftInv->incIndex(); }
			else {rightInv->incIndex();}
	} else if (input == WIN_KEY_UP) { //up
		if (dState->invIsHighlighted()){ leftInv->decIndex(); }
			else {rightInv->decIndex();}	} 
	else if (input == WIN_KEY_LEFT) { //left
		dState->switchInvSelect();
	} else if (input == WIN_KEY_RIGHT) { //right
		dState->switchInvSelect();
	} else if (input == 'g'){
		if (!dState->invIsHighlighted()){
			game->addEvent(EventFactory::createGetItemEvent(game->getPlayer(), game->getPlayer()->getLoc(), rightInv->getSelectedIndex(), 0));
			rightInv->decIndex();
			return 5;
		} //pick up the item
	} else if (input == WIN_KEY_ENTER) { //enter key
		Item* item = NULL;
		if (dState->invIsHighlighted()){
			item = game->getPlayer()->getInventory()->getItemAt(leftInv->getSelectedIndex());
		}
		if (item) {
			this->setUpSkillWindow(item);
			togglePopup();
			showItemDetail = !showItemDetail;
		}
	}

	return 0;
}

int Display::processKeyUseItem(int input){
	if (input == 'u'){
		togglePopup();
	} else if (input == WIN_KEY_DOWN) { 
		popupWin->incrementSelection(); 
	} else if (input == WIN_KEY_UP) { 
		popupWin->decrementSelection();
	} else if (input == WIN_KEY_ENTER) {
		togglePopup();
		showItemDetail = !showItemDetail;
		Item* item = game->getPlayer()->getInventory()->getItemAt(leftInv->getSelectedIndex());
		if (popupWin->getListItemAt(popupWin->getSelectedIndex()) == "Drop"){
			game->addEvent(EventFactory::createDropItemEvent(game->getPlayer(), leftInv->getSelectedIndex(), 0));
			return 5;
		}
		//use the selected skill
		game->addEvent(EventFactory::createSkillEvent(game->getPlayer(), skill_list.getSkill(item->getSkills()->at(popupWin->getSelectedIndex())), item, 0));
		return 5;
	}
	return 0;
}

void Display::setCenter(Entity* newCenter){
	center = newCenter;
}

void Display::setTarget(Coord* newTarget) {
	target = newTarget;
}


void Display::setUpSkillWindow(Item* item){
	popupWin->clear();
	vector<string>* skillNames = new vector<string>();
	
	for (unsigned int i = 0; i < item->getSkills()->size(); i++){
		skillNames->push_back(skill_list.getSkill(item->getSkills()->at(i))->getName());
	}
	skillNames->push_back("Drop"); //every item can be dropped
	popupWin->setHeader(item->getName());
	popupWin->setList(skillNames);
}

void Display::toggleInventory(bool selectedSide){
	dState->toggleInv();
	if (dState->invIsToggled()){
		if (!selectedSide){ dState->switchInvSelect(); }
		minIndex = 0, maxIndex = 8; 
		minGIndex = 0, maxGIndex = 8;
		leftInv->resetIndex(); 
		rightInv->resetIndex();
		wresize(msgWin, 4, 80);
		mvwin(msgWin, 46,0);
	} else {
		wresize(msgWin, 15, 80);
		mvwin(msgWin, 35,0);
	}
}

void Display::toggleAttributes(){
	dState->toggleAttr();
}

void Display::togglePopup(){
	if (dState->invIsHighlighted() || dState->popupIsToggled()){ //can only use items you've picked up
		dState->togglePopup();
		popupSelection = 0;
	}
}

	
