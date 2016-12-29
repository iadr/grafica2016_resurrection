#include "GameEngine.h"
bool debug_mode;
int g_gl_width;
int g_gl_height;
GLFWwindow* g_window = NULL;
GLuint shader_programme;

GameEngine::GameEngine(){
	screenSize=glm::vec2(800,600);
	g_gl_width=screenSize.x;
	g_gl_height=screenSize.y;
	debug_mode=false;
	tools::debug("GameEngine created",tools::DBG_INFO);
	keyTools::init_keys();
	//printf("Key:%i\n",key_status.count;
}

void GameEngine::setWindowSize(int w,int h){
	this->screenSize=glm::vec2(w,h);
	g_gl_width=screenSize.x;
	g_gl_height=screenSize.y;
	tools::debug("New window size: "+std::to_string(w)+"x"+std::to_string(h),tools::DBG_INFO);
}

void GameEngine::initGl(){
	restart_gl_log ();
	start_gl ();
	glEnable (GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"
	glEnable (GL_CULL_FACE); // cull face
	glCullFace (GL_BACK); // cull back face
	glFrontFace (GL_CCW); // set counter-clock-wise vertex order to mean the front
	glClearColor (0.2, 0.2, 0.2, 1.0); // grey background to help spot mistakes
	glViewport (0, 0, g_gl_width, g_gl_height);
	shader_programme = create_programme_from_files (VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE);
	cam=new Camera(&shader_programme,screenSize);
}

void GameEngine::run(){
	tools::debug("Engine is running",tools::DBG_INFO);
	paused=false;
	/*
	test=new Vehicle("mesh/sedan.obj",&shader_programme,"textures/azulmate2-1.jpg");
	Vehicle* test3=new Vehicle("mesh/sedan.obj",&shader_programme,"textures/azulmate2-1.jpg");
	test3->setPos(2.0f,0.0f,3.0f);
	addObj(test);
	addObj(test3);
	//addObj(new Object3D("mesh/car/car.obj",&shader_programme,NULL));
	test->setPos(-17.5f,0.0f,-18.75f);
	cam->target=test;
	test->set_scale(0.25f,0.25f,0.25f);
	test3->set_scale(0.25f,0.25f,0.25f);
	Object3D* extra=new Object3D("mesh/StreetLamp.obj",&shader_programme,"textures/dark-metal-texture.jpg");
	addObj(extra);
	extra->set_scale(5.0f,5.0f,5.0f);

	//Object3D* city=new Object3D("mesh/city.obj",&shader_programme,"textures/grafito1.jpg");
	//addObj(city);
	*Object3D* floor=new Object3D("mesh/city/floor.obj",&shader_programme,"textures/Textura-asfalto.jpg");
	*addObj(floor);
	*floor->set_scale(5.0f,5.0f,5.0f);
	*Object3D* floor2=new Object3D("mesh/city/parkingslot.obj",&shader_programme,"textures/3.jpg");
	*addObj(floor2);
	*floor2->set_scale(5.0f,5.0f,5.0f);
	*Object3D* blanquitos=new Object3D("mesh/city/blanquitos.obj",&shader_programme,"textures/sa.jpg");
	*addObj(blanquitos);
	*blanquitos->set_scale(5.0f,5.0f,5.0f);
	*Object3D* estacionamiento=new Object3D("mesh/city/estacionamiento.obj",&shader_programme,"textures/brick.jpg");
	*addObj(estacionamiento);
	*estacionamiento->set_scale(5.0f,5.0f,5.0f);
	*Object3D* departamentos=new Object3D("mesh/city/departamentos2.obj",&shader_programme,"textures/Building.jpg");
	*addObj(departamentos);
	*departamentos->set_scale(5.0f,5.0f,5.0f);
	*Object3D* laberinto=new Object3D("mesh/city/laberinto.obj",&shader_programme,"textures/bloody.jpg");
	*addObj(laberinto);
	*laberinto->set_scale(5.0f,5.0f,5.0f);
	*Object3D* coliseo=new Object3D("mesh/city/collosseum.obj",&shader_programme,"textures/coliseo.jpg");
	*addObj(coliseo);
	*coliseo->set_scale(5.0f,5.0f,5.0f);
	*Object3D* oficinas=new Object3D("mesh/city/oficinas.obj",&shader_programme,"textures/texture.jpg");
	*addObj(oficinas);
	*oficinas->set_scale(5.0f,5.0f,5.0f);
	*Object3D* residenciales=new Object3D("mesh/city/residenciales.obj",&shader_programme,"textures/edificio.jpg");
	*addObj(residenciales);
	*residenciales->set_scale(5.0f,5.0f,5.0f);
	*Object3D* rojitos=new Object3D("mesh/city/rojitos.obj",&shader_programme,"textures/fachada1.jpg");
	*addObj(rojitos);
	*rojitos->set_scale(5.0f,5.0f,5.0f);
	*Object3D* grandesEdificios=new Object3D("mesh/city/grandesEdificios.obj",&shader_programme,"textures/alpha.jpg");
	*addObj(grandesEdificios);
	*grandesEdificios->set_scale(5.0f,5.0f,5.0f);
	*Object3D* geA=new Object3D("mesh/city/geA.obj",&shader_programme,"textures/alpha.jpg");
	*addObj(geA);
	*geA->set_scale(5.0f,5.0f,5.0f);
	Object3D* geB=new Object3D("mesh/city/geB.obj",&shader_programme,"textures/alpha.jpg");
	addObj(geB);
	geB->set_scale(5.0f,5.0f,5.0f);
	Object3D* geC=new Object3D("mesh/city/geC.obj",&shader_programme,"textures/alpha.jpg");
	addObj(geC);
	geC->set_scale(5.0f,5.0f,5.0f);
	Object3D* geD=new Object3D("mesh/city/geD.obj",&shader_programme,"textures/alpha.jpg");
	addObj(geD);
	geD->set_scale(5.0f,5.0f,5.0f);

	//city->set_scale(5.0f,5.0f,5.0f);
	*/
	while(!glfwWindowShouldClose (g_window)){//bucle principal del motor de juegos
		static double previous_seconds = glfwGetTime ();
		double current_seconds = glfwGetTime ();
		double elapsed_seconds = current_seconds - previous_seconds;
		previous_seconds = current_seconds;
		_update_fps_counter (g_window);

		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport (0, 0, g_gl_width, g_gl_height);
		glUseProgram (shader_programme);
		glfwPollEvents ();

		//si algun escenario ha sido cargado
		readGlobalKeys();//leer teclas "globales"
		if(scenario_loaded){
			if(!paused){
				readInGameKeys();//leer teclas de interaccion dentro del juego
			}
			for(int i=0;i<objects.size();i++){
				if(objects[i]->enabled){
					if(!paused){//si el juego está pausado...
						objects[i]->update();//actualizar el objeto (posicion,rotacion,etc)
							//printf("%f  %f  %f\n",test->pos.x,test->pos.y,test->pos.z);
					}
					objects[i]->render();//renderizar cada objeto en la lista
				}
			}
		}
		cam->update();
		glfwSwapBuffers (g_window);
	}
	glfwTerminate();

	tools::debug("Engine is stopped",tools::DBG_INFO);
}

void GameEngine::loadScenario(std::string scenario_name){
	tools::debug("Cargando escenario: "+scenario_name,tools::DBG_MSG);
	pause(true);
	objects.clear();

	xml_document doc;
	std::string file=("maps/"+scenario_name+".xml");
	xml_parse_result result = doc.load_file(file.c_str());

	if((bool)result){
		tools::debug("Analizando archivo de mapa...",tools::DBG_INFO);
		for(xml_node n = doc.first_child().first_child();n;n=n.next_sibling()){
			std::string nodeName=n.name();
			std::cout<<"Nodo: "<<nodeName<<std::endl;
			if(nodeName=="player_car"){
				//obtener la textura
				std::string tex=(n.child_value("texture"));
				//instanciar un objeto car con el modelo especificado en el XML
				
				if(tex.length()>0){// si se encontro alguna textura especificada se asigna al objeto
					test=new Vehicle(std::string(n.child_value("model")).c_str(),&shader_programme,tex.c_str());
				}else{//sino se usa una textura NULL
					test=new Vehicle(std::string(n.child_value("model")).c_str(),&shader_programme,NULL);
				}

				vec3 pos=vec3(0.0f,0.0f,0.0f);

				pos.v[0]=atoi(n.child("position").attribute("x").value());
				pos.v[1]=atoi(n.child("position").attribute("y").value());
				pos.v[2]=atoi(n.child("position").attribute("z").value());

				xml_node scale=n.child("scale");
				xml_node rotation=n.child("rotation");
				
				if (scale!=NULL){//si se encontró un nodo de escalado dentro de player_car...
					float scale_x=1.0f,scale_y=1.0f,scale_z=1.0f;
					scale_x=atof(scale.attribute("x").value());
					scale_y=atof(scale.attribute("y").value());
					scale_z=atof(scale.attribute("z").value());
					printf("Escalando a: (%.2f,%.2f,%.2f)\n",scale_x,scale_y,scale_z);
					test->set_scale(scale_x,scale_y,scale_z);
				}
				
				if(rotation!=NULL){
					float rotation_x=1.0f,rotation_y=1.0f,rotation_z=1.0f;
					rotation_x=atof(rotation.attribute("x").value());
					rotation_y=atof(rotation.attribute("y").value());
					rotation_z=atof(rotation.attribute("z").value());
					printf("Rotando a: (%.2f,%.2f,%.2f)\n",rotation_x,rotation_y,rotation_z);
					test->rotate(rotation_x,rotation_y,rotation_z);	
				}
				
				//agregar ese objeto a la lista de objetos a renderizar
				test->setPos(pos.v[0],pos.v[1],pos.v[2]);
				addObj(test);
				//setear el target de la cámara
				cam->target=test;
			}else if(nodeName=="Object3D"){
				Object3D *obj;
				std::string objectName=std::string(n.attribute("name").value());
				std::string model=n.child_value("model");
				vec3 pos=vec3(0.0f,0.0f,0.0f);

				pos.v[0]=atoi(n.child("position").attribute("x").value());
				pos.v[1]=atoi(n.child("position").attribute("y").value());
				pos.v[2]=atoi(n.child("position").attribute("z").value());

				std::cout<<"|->nombre:"<<objectName<<std::endl;
				std::cout<<"|->modelo:"<<model<<std::endl;
				std::cout<<"|->posision:"<<"("<<pos.v[0]<<","<<pos.v[1]<<","<<pos.v[2]<<")"<<std::endl;

				//obtener la textura
				std::string tex=(n.child_value("texture"));
				//instanciar un objeto 3D con el modelo especificado en el XML
				
				if(tex.length()>0){// si se encontro alguna textura especificada se asigna al objeto
					obj=new Object3D(std::string(n.child_value("model")).c_str(),&shader_programme,tex.c_str());
				}else{//sino se usa una textura NULL
					obj=new Object3D(std::string(n.child_value("model")).c_str(),&shader_programme,NULL);
				}

				if(obj){//si se logró crear el objeto3d
					obj->name=objectName;
					obj->setPos(pos.v[0],pos.v[1],pos.v[2]);
					addObj(obj);
					xml_node scale=n.child("scale");
					xml_node rotation=n.child("rotation");
					if (scale!=NULL){//si se encontró un nodo de escalado dentro de player_car...
						float scale_x=1.0f,scale_y=1.0f,scale_z=1.0f;
						scale_x=atof(scale.attribute("x").value());
						scale_y=atof(scale.attribute("y").value());
						scale_z=atof(scale.attribute("z").value());
						printf("Escalando a: (%.2f,%.2f,%.2f)\n",scale_x,scale_y,scale_z);
						obj->set_scale(scale_x,scale_y,scale_z);
					}

				if(rotation!=NULL){
					float rotation_x=1.0f,rotation_y=1.0f,rotation_z=1.0f;
					rotation_x=atof(rotation.attribute("x").value());
					rotation_y=atof(rotation.attribute("y").value());
					rotation_z=atof(rotation.attribute("z").value());
					printf("Rotando a: (%.2f,%.2f,%.2f)\n",rotation_x,rotation_y,rotation_z);
					obj->rotate(rotation_x,rotation_y,rotation_z);	
				}


				}
			}else if(nodeName=="camera"){
				vec3 pos=vec3(0.0f,0.0f,0.0f);
				pos.v[0]=atoi(n.child("position").attribute("x").value());
				pos.v[1]=atoi(n.child("position").attribute("y").value());
				pos.v[2]=atoi(n.child("position").attribute("z").value());
				cam->setPos(pos.v[0],pos.v[1],pos.v[2]);
			}
		}
	}else{
		tools::debug("Error!. El archivo de mapa solicitado no ha sido encontrado",tools::DBG_ERROR);
	}

	pause(false);
	scenario_loaded=true;
}

void GameEngine::readInGameKeys(){

	if (GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_W)) {
		//tools::debug("UP",tools::DBG_KEY_PRESSED);
		//test->move(0.025,0.0f,0.0f);
		cam->zoom(-0.125f);
	}
	if (GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_S)) {
		//tools::debug("UP",tools::DBG_KEY_PRESSED);
		cam->zoom(+0.125f);
		//test->move(-0.025,0.0f,0.0f);
	}

	if (GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_A)) {
		//tools::debug("UP",tools::DBG_KEY_PRESSED);
		//test->move(0.0f,0.0f,0.025);
		cam->rotate_around(0.125f);
	}

	if (GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_D)) {
		//tools::debug("UP",tools::DBG_KEY_PRESSED);
		//test->move(0.0f,0.0f,-0.025);
		cam->rotate_around(-0.125f);
	}

	if (GLFW_RELEASE == glfwGetKey (g_window, GLFW_KEY_UP) && GLFW_RELEASE == glfwGetKey (g_window, GLFW_KEY_DOWN)) {
		//keyTools::release(K_UP_ARROW);
		//keyTools::press(K_UP_ARROW);
		test->decelerate();
	}else{
		if (GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_UP)) {
			tools::debug("UP",tools::DBG_KEY_PRESSED);
			//keyTools::press(K_UP_ARROW);
			test->move_forward();
		}
		if(GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_DOWN)){
			tools::debug("DOWN",tools::DBG_KEY_PRESSED);
			test->move_backward();
		}
	}
	if(GLFW_RELEASE == glfwGetKey (g_window, GLFW_KEY_LEFT) && GLFW_RELEASE == glfwGetKey (g_window, GLFW_KEY_RIGHT)){
		test->centrar();
	}else{
		if (GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_LEFT)) {
			tools::debug("LEFT",tools::DBG_KEY_PRESSED);
			test->girar(-1);
			//test->rotate(0.0f,-0.125f,0.0f);
		}
		if(GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_RIGHT)){
			tools::debug("RIGHT",tools::DBG_KEY_PRESSED);
			//test->rotate(0.0f,+0.125f,0.0f);
			test->girar(1);
		}
	}
}

void GameEngine::readGlobalKeys(){
	//salir con ESC
	if (GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose (g_window, 1);
		tools::debug("ESC",tools::DBG_KEY_PRESSED);
		tools::debug("ESC pressed... quitting.",tools::DBG_INFO);
	}
	//limpiar pantalla
	if (GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_C)) {
		if (system("CLS")) system("clear");
	}
}

void GameEngine::addObj(Object3D *obj){
	objects.push_back(obj);
}
void GameEngine::pause(bool b){
	this->paused=b;
}