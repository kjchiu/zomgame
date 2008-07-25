#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "attribute.h"

class Effect {
protected:
	std::string name;
	static int count;
	int id;
	int duration;
	int start_tick;
	int last_tick;
public:
	Effect();
	bool tick(int tick);
	virtual int modify(Attributes type, int value) = 0;
	void setTickCount(int tick);
};


#endif