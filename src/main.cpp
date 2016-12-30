#include "GameEngine.h"

int main(int argc, char const *argv[]){
	GameEngine *ge=new GameEngine();
	ge->setWindowSize(800,600);	
	ge->initGl();
	//ge->loadScenario("map1");
	ge->showMainMenu();
	ge->run();
	return 0;
}