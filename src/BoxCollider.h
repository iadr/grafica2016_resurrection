#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H
#include <string>
#include "Collider.h"

class BoxCollider: public Collider{
private:
	
public:
	BoxCollider(std::string);
	~BoxCollider();
	void setSize(float,float);
	void render(GLuint*);

	bool overlaps(Collider* b);
};
#endif