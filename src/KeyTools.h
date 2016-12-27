#ifndef KEY_TOOLS_H
#define KEY_TOOLS_H

#include <iostream>
#include <map>
	enum keys{
		FIRST_KEY,
		//flechas
		K_UP_ARROW=FIRST_KEY,
		K_DOWN_ARROW,
		K_LEFT_ARROW,
		K_RIGHT_ARROW,
		//otras
		K_SPACE,
		K_L_CONTROL,
		K_R_CONTROL,
		K_ALT,
		//letras
		K_w,
		K_A,
		K_S,
		K_D,
		LAST_KEY = K_D,
	};
namespace keyTools{

	static std::map <int, int> key_status;
	void init_keys();
	void press(int);
	void release(int);
	int get_status(int);
	}
#endif