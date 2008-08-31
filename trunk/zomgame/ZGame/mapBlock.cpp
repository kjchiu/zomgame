#include "mapBlock.h"
#include "terrain_factory.h"
#include "itemFactory.h"


MapBlock::MapBlock(){
	entityList = vector<Entity*>();
	propList = vector<Prop*>();
	itemList = vector<Item*>();
	terrain = new Grass();
	isTarget = false;
}

/* Adds an entity to the entities on the mapBlock, takes an int as well for height */
void MapBlock::addEntity(Entity *entity){
	//note, check for multiple entities on the same height. Something's wrong if that happens
	entityList.push_back(entity);
}

void MapBlock::addItem(Item* item){
	itemList.push_back(item);
}

/* Adds a prop to the mapBlock */
void MapBlock::addProp(Prop* prop){
	propList.push_back(prop);
}

void MapBlock::clear(){
	entityList.clear();
	itemList.clear();
	propList.clear();

}

/* Gets the char that represents this tile of the map */
chtype MapBlock::getChar() {
	//order of appearance -> entity, item, prop, terrain
	if (!entityList.empty()){
		return entityList.back()->getDisplayChar();
	} else if (!itemList.empty()){
		return itemList.back()->getDisplayChar();
	} else if (!propList.empty()){
		return propList.back()->getDisplayChar();
	}
	return terrain->getDisplayChar();
}

/* Return the color for this tile of the map */
short MapBlock::getColor() {
	if (!entityList.empty()) {
		return entityList.back()->getColor();
	} else if (!itemList.empty()){
		return itemList.back()->getColor();
	} else if (!propList.empty()){
		return propList.back()->getColor();
	}
	return terrain->getColor();
}

Item* MapBlock::getItemAt(int index){
	return itemList.at(index);
}

// only returns a copy - damn you nick
vector<Item*>* MapBlock::getItems() {
	return &itemList;
}

vector<string*>* MapBlock::getItemStrings(){
	vector<string*>* strings = new vector<string*>();
	for (int i=0; i < itemList.size(); i++){
		string* name = new string(itemList.at(i)->getName());
		strings->push_back(name);
	}

	return strings;
}

/* Simply get the entity that's on the top of the vector/stack. */
Entity* MapBlock::getTopEntity(){
	if (entityList.size())
		return entityList.back();	
	else 
		return NULL;
}

/* Simply get the prop that's on the top of the vector/stack. */
Prop* MapBlock::getTopProp(){
	if (propList.size() > 0)
		return propList.back();	
	else
		return NULL;
}

/* Are there any creatures here? Take an int, change with hasEntitiesAt(int height) eventually */
bool MapBlock::hasEntities(){
	return !entityList.empty();
}

/* Are there any props on the block? */
bool MapBlock::hasProps(){
	return !propList.empty();
}

/* Check for entities, other stuff */
bool MapBlock::isPassable(){
	if (!entityList.empty()) {
		return false;	
	}
	for (unsigned int i=0; i<propList.size(); i++){
		if (!propList.at(i)->isPassable()){
			return false;
		}
	}
	return true;
}

bool MapBlock::isObstacle() {
	for (unsigned int i=0; i<propList.size(); i++){
		if (!propList.at(i)->isPassable()){
			return true;
		}
	}
	return false;
}

// @TODO WHEN HEIGHT IS IMPLEMENTED, ONLY CHECK AT THE HEIGHT
/* Remove an entity from the list. Might take height later, if necessary */
void MapBlock::removeEntity(Entity *entity){
	for (unsigned int i=0; i<entityList.size(); i++){
		if (entityList.at(i)->getID() == entity->getID()){
			if (i==entityList.size()-1){
				entityList.pop_back();
			} else {
				entityList.erase(entityList.begin()+i, entityList.begin()+i+1); 
			} 
		}
	}
}

void MapBlock::removeItem(Item* item){
	for (unsigned int i=0; i<itemList.size(); i++){
		if (itemList.at(i)->getID() == item->getID()){
			if (i==itemList.size()-1){
				itemList.pop_back();
			} else {
				itemList.erase(itemList.begin()+i, itemList.begin()+i+1); 
			} 
		}
	}
}

/* Remove an prop from the list. Might take height later, if necessary */
void MapBlock::removeProp(Prop *prop){
	for (unsigned int i=0; i<propList.size(); i++){
		if (propList.at(i)->getID() == prop->getID()){
			if (i==propList.size()-1){
				propList.pop_back();
			} else {
				propList.erase(propList.begin()+i, propList.begin()+i+1); 
			} 
		}
	}
}

/* Set the terrain. For initializing or terrain modification (wall destruction, for example) */
void MapBlock::setTerrain(Terrain* ter){
	terrain = ter;
}

Message* MapBlock::getBlockInfo() {
	char buf[512];
	sprintf_s(&buf[0], 512, "Entities: %d, Props: %d, passable: %d", entityList.size(), propList.size(), isPassable());
	return new Message(new std::string(buf));
}

void MapBlock::loadFrom(std::ifstream &in)
{
	//load the terrain
	if(terrain)
	{
		delete terrain;
		terrain = NULL;
	}
	char tType = 0;
	in.read(&tType, sizeof(char));
	terrain = TerrainFactory::makeTerrain(static_cast<TerrainType>(tType));

	//load the item list
	char temp = 0;
	in.read(&temp, sizeof(char));
	int numItems = temp;
	for(int i = 0; i < numItems; i++)
	{
		//get info from file
		char itemId = 0;
		in.read(&itemId, sizeof(char));
		char nameLen = 0;
		in.read(&nameLen, sizeof(char));
		char nameBuffer[256] = "";
		if(nameLen > 0)
			in.read(nameBuffer, nameLen);
		short descLen = 0;
		in.read(reinterpret_cast<char*>(&descLen), sizeof(short));
		char descBuffer[512] = "";
		if(descLen > 0)
			in.read(descBuffer, descLen);

		//create the item
		if(descLen > 0)
			itemList.push_back(ItemFactory::createItem(nameBuffer, static_cast<Item::ItemType>(itemId), descBuffer));
		else
			itemList.push_back(ItemFactory::createItem(nameBuffer, static_cast<Item::ItemType>(itemId)));
	}
}

void MapBlock::saveTo(std::ofstream &out)
{
	//write out the type
	char tType = static_cast<char>(terrain->getType());
	out.write(&tType, sizeof(char));

	//write out the item list
	char numItems = static_cast<char>(itemList.size());
	out.write(&numItems, sizeof(char));
	for(vector<Item*>::iterator iter = itemList.begin(); iter != itemList.end(); iter++)
	{
		char itemId = static_cast<char>((*iter)->getID());
		out.write(&itemId, sizeof(char));
		//Item *item = *iter;

		if(!(*iter)->getName().empty())
		{
			string itemName = (*iter)->getName();
			char nameLen = static_cast<char>(itemName.size() + 1);
			out.write(&nameLen, sizeof(char));
			out.write(itemName.c_str(), nameLen);
		}
		else
		{
			char len = 0;
			out.write(&len, sizeof(char));
		}

		if(!(*iter)->getDescription().empty())
		{
			string itemDesc = (*iter)->getDescription();
			short descLen = static_cast<short>(itemDesc.size() + 1);
			out.write(reinterpret_cast<char*>(&descLen), sizeof(short));
			out.write(itemDesc.c_str(), descLen);
		}
		else
		{
			char len = 0;
			out.write(&len, sizeof(char));
		}
	}
}