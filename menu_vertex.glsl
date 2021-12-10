#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 coords;

out vec3 tex_coords;

void main(){
	tex_coords = coords;
	gl_Position = vec4(aPos, 1.0);
}

