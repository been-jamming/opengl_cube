#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 a_norm;

uniform vec3 model_position;
uniform vec4 model_orientation;
uniform vec2 resolution;
uniform float fov_const;

out vec3 model_coords;
out vec3 model_normal;
out vec3 normal;
out vec3 world_coords;

vec4 inverse_orientation(vec4 orientation){
	return vec4(orientation.x, -orientation.yzw);
}

vec4 compose_orientation(vec4 a, vec4 b){
	return mat4(b.xyzw, b.yxwz*vec4(-1.0, 1.0, -1.0, 1.0), b.zwxy*vec4(-1.0, 1.0, 1.0, -1.0), b.wzyx*vec4(-1.0, -1.0, 1.0, 1.0))*a;
}

vec3 apply_orientation(vec3 p, vec4 o){
	vec4 v;

	v.x = 0.0;
	v.yzw = p.xyz;
	return compose_orientation(compose_orientation(o, v), inverse_orientation(o)).yzw;
}

vec4 screen_space(vec3 p){
	return vec4(p.xy*min(resolution.x, resolution.y)*fov_const/resolution, p.z - 2.0, p.z);
}

void main(){
	model_coords = aPos;
	gl_Position = screen_space(apply_orientation(aPos, model_orientation) + model_position);
	world_coords = gl_Position.xyz;
	normal = normalize(apply_orientation(a_norm, model_orientation));
	model_normal = a_norm;
}

