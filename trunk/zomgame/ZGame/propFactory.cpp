#include "propFactory.h"

ContainerProp* PropFactory::createContainer(){
	return createContainer(new vector<Item*>());
}

ContainerProp* PropFactory::createContainer(vector<Item*>* items){
	ContainerProp* container = new ContainerProp();
	container->setItems(items);
	return container;
}

Door* PropFactory::createDoor(){
	return createDoor(100);
}

Door* PropFactory::createDoor(int health){
	Door* door = new Door();
	door->getHealth()->init(door->getHealth()->getName(), health, health);
	vector<Item*> debris;
	debris.push_back(ItemFactory::createWoodPlank());
	door->setDebris(debris);
	return door;
}

Prop* PropFactory::createWall(){
	return createWall(100);
}

Prop* PropFactory::createWall(int health){
	Prop* wall = new Prop(false);
	wall->setName("Wall");
	wall->getHealth()->init(wall->getHealth()->getName(), health, health);
	vector<Item*> debris;
	debris.push_back(ItemFactory::createWoodPlank());
	debris.push_back(ItemFactory::createWoodPlank());
	wall->setDebris(debris);
	return wall;
}