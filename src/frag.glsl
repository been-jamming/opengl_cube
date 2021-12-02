#version 330 core

#define EPSILON 0.001

out vec4 FragColor;
in vec3 model_coords;
in vec3 normal;

uniform vec3 sticker_colors[6];

vec3 get_color(){
	int side = 0;
	vec2 face_coords = vec2(0.0);

	side = model_coords.y > 1.0 - EPSILON ? 1 : side;
	side = model_coords.z > 1.0 - EPSILON ? 2 : side;
	side = model_coords.x < -1.0 + EPSILON ? 3 : side;
	side = model_coords.y < -1.0 + EPSILON ? 4 : side;
	side = model_coords.z < -1.0 + EPSILON ? 5 : side;

	face_coords = side == 0 || side == 3 ? model_coords.yz : face_coords;
	face_coords = side == 1 || side == 4 ? model_coords.xz : face_coords;
	face_coords = side == 2 || side == 5 ? model_coords.xy : face_coords;

	if((abs(face_coords.x) < 0.8 && abs(face_coords.y) < 0.7) || (abs(face_coords.x) < 0.7 && abs(face_coords.y) < 0.8) || length(vec2(abs(face_coords.x) - 0.7, abs(face_coords.y) - 0.7)) < 0.1){
		return sticker_colors[side];
	} else {
		return vec3(0.05);
	}
}

void main(void){
	gl_FragColor = vec4((0.1 + 0.9*abs(dot(normal, vec3(0.0, 0.0, -1.0))))*get_color(), 1.0);
}
