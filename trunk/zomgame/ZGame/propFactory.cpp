#include "propFactory.h"

Prop* PropFactory::createDoor(){
	return createDoor(100);
}

Prop* PropFactory::createDoor(int durability){
	Prop* door = new Door();
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