#ifndef _TOOLS_H_
#define _TOOLS_H_
#include <iostream>
#include <string>

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <assimp/cimport.h> // C importer
#include <assimp/scene.h> // collects data
#include <assimp/postprocess.h> // various extra operations

#include "gl_utils.h"

#define ONE_DEG_IN_RAD (2.0 * M_PI) / 360.0 // 0.017444444
#define ONE_RAD_IN_DEG 360.0 / (2.0 * M_PI) //57.2957795

extern bool debug_mode;

//ayuda a imprimir mensajes en la pantalla con colores respectivos
namespace tools{
	const int DBG_DEFAULT = 0;
	const int DBG_MSG = 1;
	const int DBG_INFO = 2;
	const int DBG_WARNING = 3;
	const int DBG_ERROR = 4;
	const int DBG_KEY_PRESSED = 5;
	const int DBG_KEY_RELEASED = 6;

	void debug(std::string,int);

	// funcion que carga una malla desde filename
	bool load_mesh (const char* file_name, GLuint* vao, int* point_count);	
}
#endif