#include "propFactory.h"

Door* PropFactory::createDoor(){
	return createDoor(100);
}

Door* PropFactory::createDoor(int durability){
	Door* door = new Door();
	door->getDurability()->init(door->getDurability()->getName(), durability, durability);
	vector<Item*> debris;
	debris.push_back(ItemFactory::createWoodPlank());
	door->setDebris(debris);
	return door;
}

Prop* PropFactory::createWall(){
	return createWall(100);
}

Prop* PropFactory::createWall(int durability){
	Prop* wall = new Prop(false);
	wall->setName("Wall");
	wall->getDurability()->init(wall->getDurability()->getName(), durability, durability);
	vector<Item*> debris;
	debris.push_back(ItemFactory::createWoodPlank());
	debris.push_back(ItemFactory::createWoodPlank());
	wall->setDebris(debris);
	return wall;
}