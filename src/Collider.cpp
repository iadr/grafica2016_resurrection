#include "Collider.h"
#include "Object3D.h"
#include "BoxCollider.h"
Collider::Collider(std::string id){
	this->id=id;
}
Collider::~Collider(){}

void Collider::setPos(glm::vec3 p){
	this->pos=p;
}
int Collider::getType(){
	return this->type;
}