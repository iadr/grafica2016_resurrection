#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "Collider.h"
//#include "Object3D.h"

class BoxCollider: public Collider{
private:
	int width=0,depth=0;//largo y ancho
public:
	BoxCollider(Object3D* p);
	~BoxCollider();
};
#endif