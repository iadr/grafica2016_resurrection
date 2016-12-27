#include "KeyTools.h"

void keyTools::init_keys(){
	for(int i =K_UP_ARROW;i<=LAST_KEY;i++){
		key_status[i]=0;
	}
	//printf("init_keys: %i\n",key_status.size());
}

void keyTools::press(int key){
	key_status[key]=1;
}

void keyTools::release(int key){
	key_status[key]=0;
}

int keyTools::get_status(int key){
	return key_status[key];
}