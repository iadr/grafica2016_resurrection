#include "Collider.h"
#include "Object3D.h"
#include "BoxCollider.h"
Collider::Collider(){
	
}

void Collider::setPos(glm::vec3 p){
	this->pos=p;
}