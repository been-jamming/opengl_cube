#version 330 core

#define EPSILON 0.001

out vec4 FragColor;
in vec3 tex_coords;
uniform sampler2D textures[16];

void main(){
	if(int(tex_coords.z) == 0){
		FragColor = texture(textures[0], tex_coords.xy);
		if(FragColor.w < 0.1){
			discard;
		}
	} else {
		FragColor = vec4(0.0, 0.0, 0.0, 1.0);
	}
	//FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
