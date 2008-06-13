#include "propFactory.h"

Door* PropFactory::createDoor(){
	return createDoor(100);
}

Door* PropFactory::createDoor(int durability){
	Door* door = new Door();
	door->getDurability()->changeMaxValueBy(durability - 100);
	door->getDurability()->changeCurValueBy(durability - 100);
	return door;
}

Prop* PropFactory::createWall(){
	return createWall(100);
}

Prop* PropFactory::createWall(int durability){
	Prop* wall = new Prop(false);
	wall->setName("Wall");
	wall->getDurability()->changeMaxValueBy(durability - 100);
	wall->getDurability()->changeCurValueBy(durability - 100);
	return wall;

}