#ifndef COLLIDER_H_
#define COLLIDER_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

class Object3D;

class Collider{
protected:
	Object3D* parent;
	glm::vec3*pos; //posicion del collider 
public:
	float * pos_x,pos_y,pos_z;
	Collider(Object3D * p);
	~Collider();
	
};
#endif