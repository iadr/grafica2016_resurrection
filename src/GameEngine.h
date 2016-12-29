#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>

#include "Tools.h"
#include "gl_utils.h"
#include "Object3D.h"
#include "Vehicle.h"
#include "Camera.h"

#include "KeyTools.h"
#include "pugixml.hpp"

#define VERTEX_SHADER_FILE "shaders/test_vs.glsl.cpp"
#define FRAGMENT_SHADER_FILE "shaders/test_fs.glsl.cpp"

//using namespace glm;
using namespace pugi;
class GameEngine{
private:
	//Otros
	Camera*cam=NULL;
	glm::vec2 screenSize;
	std::vector<Object3D *> objects;//lista de objetos 
	bool scenario_loaded=false;
	bool paused=false;
public:
	GameEngine();
	~GameEngine();
	Vehicle* test;
	void setWindowSize(int w,int h);
	void loadScenario(std::string scenario_name);
	void initGl();
	void run();
	void readInGameKeys();
	void readGlobalKeys();
	void addObj(Object3D *obj);
	void pause(bool);
};
#endif