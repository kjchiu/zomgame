/* A prop, usually interactive, like a table, wall, chair, etc */

#ifndef _PROP_H
#define _PROP_H

#include <string>

#include "renderable.h"

using namespace std;

class Prop : public Renderable {

	private:
		bool passable; //passed in, dependent on the prop

	public:
		Prop();
		Prop(bool canPass);
		bool isPassable();
		void setPassable(bool canPass);
};

#endif
