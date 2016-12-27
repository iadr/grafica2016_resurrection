#ifndef CAMERA_H
#define CAMERA_H
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>
#include <math.h>
#include "Object3D.h"

#define ONE_DEG_IN_RAD (2.0 * M_PI) / 360.0 // 0.017444444

//using namespace glm;

class Camera{
private:
	int screenWidth=0,screenHeight=0;
	glm::vec3 pos;
	float cam_speed = 1.0f; // 1 unit per second
	float cam_yaw_speed = 10.0f; // 10 degrees per second
	float cam_yaw = 0.0f; // y-rotation in degrees
	int view_mat_location=0;
	int vmat_location=0;
	int proj_mat_location=0;

	// matrix components
	float range;
	float Sx;
	float Sy;
	float Sz;
	float Pz;

public:
	float cam_pos[3] = {0.0f, 2.0f, 5.0f}; // don't start at zero, or we will be too close
	Object3D *target;
	// input variables
	float R,H;//distancia desde el objetivo hasta la cámara (Radio del circulo)
	glm::vec3 rotation;
	float near;
	float far;
	float fov;
	float aspect;

	Camera(GLuint*,glm::vec2);
	~Camera();

	void zoom(float);

	void setPos(float,float,float);
	void move(float,float,float);
	void rotate(float,float,float);
	void rotate_around(float);
	void update();
};
#endif
