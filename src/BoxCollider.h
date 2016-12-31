#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "Collider.h"

class BoxCollider: public Collider{
private:
	int width=0,depth=0;//largo y ancho
public:
	BoxCollider();
	~BoxCollider();
	void setSize(float,float);
};
#endif