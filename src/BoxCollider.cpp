#include "BoxCollider.h"
#include <iostream>
BoxCollider::BoxCollider(std::string id):Collider(id){
	this->type=1;
}

void BoxCollider::setSize(float w,float d){
	this->width=w;
	this->depth=d;
}
void BoxCollider::render(GLuint* sp){
	//printf("rendering collider!.\n");
    
	
}

bool BoxCollider::overlaps(Collider * b){
	/*
	bool over=false;
	int type=b->getType();
	if(type==this->type){
		if(
			this->pos.x+(this->width/2) > b->pos.x-(b->width/2) && 
			this->pos.z+(this->width/2) > b->pos.z-(b->width/2) &&
			this->pos.x-(this->width/2) < b->pos.x+(b->width/2) &&
			this->pos.z-(this->width/2) < b->pos.z+(b->width/2)
		){
			over=true;
		}
	}
	return over;*/

    bool collisionX = 	(pos.x + (width/2.0f) >= b->pos.x - (b->width/2.0f) && pos.x + (width/2.0f) <= b->pos.x + (b->width/2.0f))
    				||	(pos.x - (width/2.0f) <= b->pos.x + (b->width/2.0f) && pos.x - (width/2.0f) >= b->pos.x - (b->width/2.0f))
    					;
    
    bool collisionZ = 	(pos.z + (depth/2.0f) >= b->pos.z - (b->depth/2.0f) && pos.z + (depth/2.0f) <= b->pos.z + (b->depth/2.0f))
    				||	(pos.z - (depth/2.0f) <= b->pos.z + (b->depth/2.0f) && pos.z - (depth/2.0f) >= b->pos.z - (b->depth/2.0f))
    					;

	/*
    if(id=="player_car"){
		printf("pcx+w/2:%f\n",pos.x+(width/2.0f));  	
    }
	if(b->id=="cone_1"){
		printf("cx-w/2:%f\n",b->pos.x-(b->width/2.0f));
		printf("cx+w/2:%f\n",b->pos.x+(b->width/2.0f));
		printf("colx: %i\n",collisionX);
	}
	*/
    return collisionX && collisionZ;
}

