#pragma once
#include "Shapestuff.h"
#include "Shape.h"
#include "frame.h" // Debug() 때문에 선언함
#include <list>
using namespace std;

class Group :
	public Shapestuff
{
public:
	Group(HDC hdc, int l, int t, int r, int b);
	void add(Shapestuff* r);
	void set_again(int, int, int, int);
	virtual void repaint();
	list<Shapestuff*> Slist;
protected:
	
private:
	
	/*int left = 0;
	int top = 0;
	int right = 0;
	int bottom = 0;*/
};

