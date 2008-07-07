#ifndef _GAME_H
#define _GAME_H

#define DEBUG 1

#include "attack_event.h"
#include "ranged_attack_event.h"
#include "get_item_event.h"
#include "move_event.h"
#include "spawn_entity_event.h"
#include "spawn_item_event.h"
#include "spawn_prop_event.h"
#include "interact_event.h"
#include "drop_item_event.h"
#include "skill_event.h"

using namespace std;


struct Time {
	int hour;
	int minute;
	double second;
};

class Game {
	private:
		deque<Message> messages;
		Display* display;
		static EventDeque* events; 
		static Game* _instance;
		Referee* ref;
		Map* map;
		Player* player;
		Coord* target;
		vector<Zombie*> zombies;
		unsigned int tickCount;

	public:
		Coord* directionOffsets[8];
		Game();
		Game(int tWidth, int tHeight);
		void init(int tWidth, int tHeight);
		static Game* getInstance();

		static EventDeque* getEventList();
		vector<Coord>* getRay(Coord *start, Coord *target);
		Map* getMap() {return this->map;}
		Referee* getReferee() {return this->ref;}
		void addMessage(Message* msg);
		deque<Message> getMessages();

		char* getView();
		Player* getPlayer();
		Coord* getTarget();
		Time getTime();
		void draw();
		void drawMenu();
		int processKey(int input);

		void addEvent(Event* e);
		void moveTarget(Direction dir);
		bool isPassable(Coord* nextLoc);
		unsigned int getTickcount();

		void quitGame();
		void tick();
		void run();
};

#endif
