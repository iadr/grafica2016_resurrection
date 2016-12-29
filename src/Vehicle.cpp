#include "Vehicle.h"

Vehicle::Vehicle(const char* file_name,GLuint* shader_programme,const char* texture):Object3D(file_name,shader_programme,texture){
	velocity=0.0f;
}
void Vehicle::move_forward(){
	//printf("acelerando...\n");
	if(fabs(velocity)<max_velocity){
		if(velocity>=0){
			velocity+=accel;
		}else{
			velocity+=8*accel;
		}
		velocity+=accel;
	}
	pos.x-=velocity*cos(rotation.y);
	pos.z-=velocity*sin(rotation.y);
}
void Vehicle::move_backward(){
	if(fabs(velocity)<max_velocity){
		if(velocity<=0){
			velocity-=accel;
		}else{
			velocity-=8*accel;
		}
	}
	pos.x-=velocity*cos(rotation.y);
	pos.z-=velocity*sin(rotation.y);
}

void Vehicle::girar(int s){
	int sentido=s;
	if(velocity<0&&sentido<0)sentido=fabs(-sentido);
	else if(velocity<0&&sentido>0)sentido=-fabs(sentido);
	float max=0.025f;//*(velocity*10);//giro maximo segun la velocidad
	if(sentido>0&&giro<0 || sentido<0&&giro>0){
		giro=0.0f;
	}else{
		if(fabs(giro)<max){//giro maximo
			giro+=giro_incremento*sentido;
		}else{
			giro=max*sentido;
		}
	}
	if(fabs(velocity)>0){
		Object3D::rotate(0.0f,giro,0.0f);
	}
}

void Vehicle::centrar(){
	if(fabs(giro)<0.00125f){
		giro=0.0f;
	}else{
		if(giro>0.0f){
			giro-=giro_incremento;
		}else if(giro<0.0f){
			giro+=giro_incremento;
		}
	}
}

void Vehicle::decelerate(){
	float factor=4.0f;//4veces mas fuerte que la aceleracion 
	if(fabs(velocity)<0.00125f){
		velocity=0.0f;
	}else{
		if(velocity>0.0f){
			//printf("desacelerando...\n");
			velocity-=factor*decel;
			pos.x-=velocity*cos(rotation.y);
			pos.z-=velocity*sin(rotation.y);
		}
		if(velocity<0.0f){
			//printf("desacelerando...\n");
			velocity+=factor*decel;
			pos.x-=velocity*cos(rotation.y);
			pos.z-=velocity*sin(rotation.y);
		}
	}
}

void Vehicle::brake(){

}

void Vehicle::update(){
	M=glm::mat4();
	M=glm::translate(M,pos);
	M=glm::scale(M,scale);
	M=glm::rotate(M,-rotation.y,glm::vec3(0.0f,1.0f,0.0f));
	M=glm::translate(M,glm::vec3(-0.450f,0.0f,0.0f));
	//printf("Car_giro    : %f\n",giro);
}