#ifndef COLLIDER_H_
#define COLLIDER_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

class Collider{
protected:
	glm::vec3 pos; //posicion del collider 
public:
	float * pos_x,pos_y,pos_z;
	Collider();
	~Collider();
	virtual void setSize(float,float)=0;
	virtual void render(GLuint*)=0;
	void setPos(glm::vec3);
};
#endif