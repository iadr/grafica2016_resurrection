#version 130
#define NLUCES 2
#define LIMITELUZ 0.95f
in vec3 position_eye, normal_eye;
in vec2 st;
uniform sampler2D basic_texture;
uniform mat4 view_mat;


// fixed point light properties
vec3 light_position[NLUCES]  = vec3[](vec3 (100.0, 100.0, 100.0),vec3(-17.5f,25.0f,18.0f));
vec3 Ls = vec3 (0.8, 0.8, 0.8); // white specular colour
vec3 Ld = vec3 (0.2, 0.2, 0.2); // dull white diffuse light colour
vec3 La = vec3 (0.2, 0.2, 0.2); // grey ambient colour

// surface reflectance
vec3 Ks = vec3 (0.8, 0.8, 0.8); // fully reflect specular light
vec3 Kd = vec3 (0.8, 0.8, 0.8); // diffuse surface reflectance
vec3 Ka = vec3 (0.5, 0.5, 0.5); // fully reflect ambient light
float specular_exponent = 1000; // specular 'power'
vec3 r=vec3(0,-1,0);

out vec4 fragment_colour; // final colour of surface
void main () {
fragment_colour=vec4(0,0,0,1);
for(int i=0;i<NLUCES;i++){
	// ambient intensity
	vec3 Ia = La * Ka;

	// diffuse intensity
	// raise light position to eye space
	vec3 light_position_eye = vec3(view_mat * vec4 (light_position[i], 1.0));
	vec3 distance_to_light_eye = light_position_eye - position_eye;
	vec3 direction_to_light_eye = normalize (distance_to_light_eye);
	float dot_prod = dot (direction_to_light_eye, normal_eye);
	dot_prod = max (dot_prod, 0.0);
	vec3 Id = Ld * Kd * dot_prod; // final diffuse intensity

			// specular intensity (blinn shading)
	vec3 surface_to_viewer_eye = normalize (-position_eye);
	vec3 half_way_eye = normalize (surface_to_viewer_eye + direction_to_light_eye);
	float dot_prod_specular = max (dot (half_way_eye, normal_eye), 0.0);
	float specular_factor = pow (dot_prod_specular, specular_exponent);
	vec3 Is = Ls * Ks * specular_factor; // final specular intensity

	if(i==1){
		//filtro  spotlight
		vec3 omega=normalize(position_eye-light_position_eye);
		float foco =abs(dot (r,omega));
		if(foco<0.75f) Is=Id=vec3(0,0,0);
	}
	// final colour
	vec4 texel = texture (basic_texture, st);
	vec4 luz = vec4 ( Id + Ia, 1.0);
	fragment_colour+=vec4(texel.xyz*Id+texel.xyz*Ia+Is,1.0);
}


}
