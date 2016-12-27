#ifndef VEHICLE_H
#define VEHICLE_H
#include "Object3D.h"

class Vehicle : public Object3D{
public:
	float velocity=0.0f;
	
	/*Giro:
		<0 : izquierda
		=0 : sin giro
		>0 : derecha
	*/

	float giro=0.0f;
	float giro_incremento=0.00025f;

	float accel=0.000125f;//aceleracion
	float decel=0.000125f;//desaceleracion
	float decel_brake=0.75f;//freno
	
	float max_velocity=0.1f;

	Vehicle(const char*,GLuint*,const char*);
	~Vehicle();
	
	void move_forward();
	void move_backward();
	void brake();
	void update();//sobre-escritura metodo update
	void girar(int);
	void centrar();
	void decelerate();
};
#endif