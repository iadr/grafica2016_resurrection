#include "Collider.h"
#include "Object3D.h"
#include "BoxCollider.h"
Collider::Collider(Object3D * p){
	this->parent=p;
	//this->pos=&parent->pos;
}