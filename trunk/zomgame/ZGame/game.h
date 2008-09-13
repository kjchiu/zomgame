#ifndef _GAME_H
#define _GAME_H

#define DEBUG 1


#include <deque>

#include "event_factory.h"
#include "propfactory.h"
#include "messagefactory.h"
#include "itemFactory.h"
#include "event_dq.h" 
#include "display.h"
#include "entity.h"
#include "player.h"
#include "referee.h"
#include "zombie.h"
#include "scrollable_list.h"

#include "weaponFactory.h"


class Game;
class Display;
class Referee;

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
		vector<Item*>* rightInventory;
		unsigned int tickCount;
		bool eventsResolved;

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
		vector<Item*>* getRightInvList();
		void setRightInvList(vector<Item*>* nRightInvList);
		void openInventory(vector<Item*>* rightInvList, bool selectedSide);

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
