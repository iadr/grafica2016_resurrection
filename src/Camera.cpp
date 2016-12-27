#include "Camera.h"
#include <math.h>
#define MIN_CAM_DISTANCE 1
#define MAX_CAM_DISTANCE 10
Camera::Camera(GLuint *shader_programme,glm::vec2 ScreenSize){
	this->target=NULL;
	rotation=glm::vec3(0.0f,0.0f,0.0f);
	R=MIN_CAM_DISTANCE;
	H=10.0f;
	screenWidth=ScreenSize.x;
	screenHeight=ScreenSize.y;
	// input variables
	near = 0.1f; // clipping plane
	far = 100.0f; // clipping plane
	fov = 67.0f * ONE_DEG_IN_RAD; // convert 67 degrees to radians
	aspect = (float)screenWidth / (float)screenHeight; // aspect ratio
	// matrix components

	range = tan (fov * 0.5f) * near;
	Sx = (2.0f * near) / (range * aspect + range * aspect);
	Sy = near / range;
	Sz = -(far + near) / (far - near);
	Pz = -(2.0f * far * near) / (far - near);

	GLfloat proj_mat[] = {
		Sx, 0.0f, 0.0f, 0.0f,
		0.0f, Sy, 0.0f, 0.0f,
		0.0f, 0.0f, Sz, -1.0f,
		0.0f, 0.0f, Pz, 0.0f
	};

	glm::mat4 T= glm::translate(glm::mat4(),glm::vec3 (-cam_pos[0], -cam_pos[1], -cam_pos[2]));

	glm::mat4 view_mat= T;

	view_mat_location = glGetUniformLocation (*shader_programme, "view");
	glUseProgram (*shader_programme);

	glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, value_ptr(view_mat));
	proj_mat_location = glGetUniformLocation (*shader_programme, "proj");
	glUniformMatrix4fv (proj_mat_location, 1, GL_FALSE, proj_mat);

	vmat_location = glGetUniformLocation (*shader_programme, "view_mat");
	glUseProgram (*shader_programme);
	glUniformMatrix4fv (vmat_location, 1, GL_FALSE, value_ptr(view_mat));
}

void Camera::zoom(float dR){
	H+=dR;
	if(H<MIN_CAM_DISTANCE)H=MIN_CAM_DISTANCE;
	if(H>MAX_CAM_DISTANCE)H=MAX_CAM_DISTANCE;
	//printf("cam-> Zoom %f\n",R);
}

void Camera::rotate_around(float angle){
	rotation.y+=angle;

	//printf("cam-> rotate_around %f\n", rot_y);
}

void Camera::move(float x,float y,float z){
	/*
	cam_pos[0]+=x;
	cam_pos[1]+=y;
	cam_pos[2]+=z;
	*/
}

void Camera::setPos(float x,float y,float z){
	cam_pos[0]=x;
	cam_pos[1]=y;
	cam_pos[2]=z;
}

void Camera::rotate(float x,float y,float z){
	cam_yaw-=y;
}

void Camera::update(){
	glm::mat4 T=glm::mat4();
	//Si el objetivo esta definido, entonces se actualizará la cámara para que rote en funcion
	//de el
	if(target!=NULL){
		cam_pos[0]=target->pos.x;
		cam_pos[1]=H;
		cam_pos[2]=target->pos.z;
		T=glm::lookAt(glm::vec3(cam_pos[0],cam_pos[1],cam_pos[2]),target->pos,glm::vec3(0.0f,0.0f,1.0f));
		//printf("cam_pos   (%f,%f,%f)\n",cam_pos[0],cam_pos[1],cam_pos[2]);
		//printf("target_pos(%f,%f,%f)\n",target->pos.x,target->pos.y,target->pos.z);
	}else{
		T = glm::translate (T, glm::vec3 (-cam_pos[0], -cam_pos[1], -cam_pos[2]));
	}
	glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, value_ptr(T));
	glUniformMatrix4fv (vmat_location, 1, GL_FALSE, value_ptr(T));
}
