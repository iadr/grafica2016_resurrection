#include "BoxCollider.h"
BoxCollider::BoxCollider():Collider(){

}

void BoxCollider::setSize(float w,float d){
	this->width=w;
	this->depth=d;
}