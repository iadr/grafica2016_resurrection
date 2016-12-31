#include "BoxCollider.h"
#include <iostream>
BoxCollider::BoxCollider():Collider(){

}

void BoxCollider::setSize(float w,float d){
	this->width=w;
	this->depth=d;
}
void BoxCollider::render(GLuint* sp){
	printf("rendering collider!.\n");
    GLfloat qpoints[] = {
        0.4f, -0.3f, 0.0f,
        0.4f, -0.5f, 0.0f,
        -0.4f, -0.5f, 0.0f,
        -0.4f, -0.3f, 0.0f
    };

    // ejercicio (1.5)
    // colores quads
    GLfloat qcolors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f
    };

    GLuint qvbo;
	glGenBuffers (1, &qvbo);
	glBindBuffer (GL_ARRAY_BUFFER, qvbo);
	glBufferData (GL_ARRAY_BUFFER, 12 * sizeof (GLfloat), qpoints, GL_STATIC_DRAW);
	
	GLuint qcvbo;
	glGenBuffers (1, &qcvbo);
	glBindBuffer (GL_ARRAY_BUFFER, qcvbo);
	glBufferData (GL_ARRAY_BUFFER, 12 * sizeof (GLfloat), qcolors, GL_STATIC_DRAW);

	GLuint qvao;
	glGenVertexArrays(1, &qvao);
	glBindVertexArray(qvao);
	glBindBuffer (GL_ARRAY_BUFFER, qvbo);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer (GL_ARRAY_BUFFER, qcvbo);
	glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	

}