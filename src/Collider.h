#ifndef COLLIDER_H_
#define COLLIDER_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

#include <string>
class BoxCollider;
//#include "BoxCollider.h"
class Collider{
protected:
	int type;
public:
	float width=0,depth=0;//largo y ancho
	glm::vec3 pos; //posicion del collider 
	std::string id;
	float * pos_x,pos_y,pos_z;
	Collider(std::string);
	~Collider();
	virtual void setSize(float,float)=0;
	virtual void render(GLuint*)=0;
	virtual bool overlaps(Collider*)=0;
	void setPos(glm::vec3);
	int getType();
};
#endif