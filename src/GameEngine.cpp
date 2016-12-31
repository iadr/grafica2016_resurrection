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
	//paused=false;
	GLuint filtro_loc= glGetUniformLocation (shader_programme, "filtropantalla");//conexion fragment

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
			//printf("Flag 1!\n");
			if(paused==false){
				readInGameKeys();//leer teclas de interaccion dentro del juego
			}
			//printf("Flag 2!\n");
			for(int i=0;i<objects.size();i++){
				if(objects[i]->enabled){
					if(!paused){//si el juego está pausado...
						objects[i]->update();//actualizar el objeto (posicion,rotacion,etc)
							//printf("%f  %f  %f\n",test->pos.x,test->pos.y,test->pos.z);
					}
					if(i>1) glUniform1i(filtro_loc,0);//determina si utilizamos la luz o solo la textura
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
		if(test!=NULL){
			test->decelerate();
		}
	}else{
		if (GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_UP)) {
			tools::debug("UP",tools::DBG_KEY_PRESSED);
			//keyTools::press(K_UP_ARROW);
			if(test!=NULL){
				test->move_forward();
			}
		}
		if(GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_DOWN)){
			tools::debug("DOWN",tools::DBG_KEY_PRESSED);
			if(test!=NULL){
				test->move_backward();
			}
		}
	}
	if(GLFW_RELEASE == glfwGetKey (g_window, GLFW_KEY_LEFT) && GLFW_RELEASE == glfwGetKey (g_window, GLFW_KEY_RIGHT)){
		test->centrar();
	}else{
		if (GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_LEFT)) {
			tools::debug("LEFT",tools::DBG_KEY_PRESSED);
			if(test!=NULL){
				test->girar(-1);
			}
			//test->rotate(0.0f,-0.125f,0.0f);
		}
		if(GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_RIGHT)){
			tools::debug("RIGHT",tools::DBG_KEY_PRESSED);
			//test->rotate(0.0f,+0.125f,0.0f);
			if(test!=NULL){
				test->girar(1);
			}
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

	if(!f1_pressed&&GLFW_PRESS == glfwGetKey(g_window,GLFW_KEY_F1)){
		printf("F1\n");
		loadScenario("map1");
		f1_pressed=true;
	}
	else if(f1_pressed&&GLFW_RELEASE == glfwGetKey(g_window,GLFW_KEY_F1)){
		f1_pressed=false;
	}

	if(!f2_pressed&&GLFW_PRESS == glfwGetKey(g_window,GLFW_KEY_F2)){
		printf("F2\n");
		loadScenario("map2");
		f2_pressed=true;
	}
	else if(f2_pressed&&GLFW_RELEASE == glfwGetKey(g_window,GLFW_KEY_F2)){
		f2_pressed=false;
	}

	if(!f3_pressed&&GLFW_PRESS == glfwGetKey(g_window,GLFW_KEY_F3)){
		printf("F3\n");
		loadScenario("map3");
		f3_pressed=true;
	}
	else if(f3_pressed&&GLFW_RELEASE == glfwGetKey(g_window,GLFW_KEY_F3)){
		f3_pressed=false;
	}

	if(!f4_pressed&&GLFW_PRESS == glfwGetKey(g_window,GLFW_KEY_F4)){
		printf("F4\n");
		loadScenario("map4");
		f4_pressed=true;
	}
	else if(f4_pressed&&GLFW_RELEASE == glfwGetKey(g_window,GLFW_KEY_F4)){
		f4_pressed=false;
	}
	if(!enter_pressed&&GLFW_PRESS == glfwGetKey(g_window,GLFW_KEY_ENTER)){
		printf("LET'S PLAY!!!!\n");
		loadScenario("map1");
		enter_pressed=true;
	}
	if(firstTime&&!z_pressed&&GLFW_PRESS == glfwGetKey(g_window,GLFW_KEY_Z)){
		printf("instrucciones\n");
		objects.clear();
		showInsMenu();
		z_pressed=true;
		firstTime=false;
	}
}

void GameEngine::showMainMenu(){
	GLuint filtro_loc= glGetUniformLocation (shader_programme, "filtropantalla");
	Object3D * menu=new Object3D("mesh/pantalla.obj",&shader_programme,"textures/city1-3.png");
	menu->setPos(0,5,0);
	//menu->set_scale(2,2,2);
	glUniform1i(filtro_loc,1);
	addObj(menu);
	cam->setPos(0,-1,0);
	cam->target=menu;
	cam->zoom(2);
	scenario_loaded=true;
	paused=true;
}
void GameEngine::showInsMenu(){
	GLuint filtro_loc= glGetUniformLocation (shader_programme, "filtropantalla");
	Object3D * menu2=new Object3D("mesh/pantalla.obj",&shader_programme,"textures/city1-4.png");
	menu2->setPos(0,5,0);
	//menu->set_scale(2,2,2);
	glUniform1i(filtro_loc,1);
	addObj(menu2);
	cam->setPos(0,-1,0);
	cam->target=menu2;
	cam->zoom(2);
	scenario_loaded=true;
	paused=true;
}

void GameEngine::loadScenario(std::string scenario_name){
	tools::debug("Cargando escenario: "+scenario_name,tools::DBG_MSG);
	pause(true);
	firstTime=false;
	xml_document doc;
	std::string file=("maps/"+scenario_name+".xml");
	xml_parse_result result = doc.load_file(file.c_str());
	if((bool)result){
		objects.clear();
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
				xml_node collider=n.child("collider");

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

				if(collider!=NULL){
					printf("Agregando collider\n");
					test->attachCollider(1,1,1);
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
	scenario_loaded=(bool)result;
}

void GameEngine::addObj(Object3D *obj){
	objects.push_back(obj);
}
void GameEngine::pause(bool b){
	this->paused=b;
}
