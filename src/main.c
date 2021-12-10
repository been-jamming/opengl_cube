#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>
#include "../tga.h"
#include "../menu.h"

//Vertices for cube model with normal vectors
float cube_vertices[] = {
	-1.0, -1.0, -1.0, 0.0, 0.0, -1.0,
	1.0, -1.0, -1.0, 0.0, 0.0, -1.0,
	-1.0, 1.0, -1.0, 0.0, 0.0, -1.0,
	-1.0, 1.0, -1.0, 0.0, 0.0, -1.0,
	1.0, 1.0, -1.0, 0.0, 0.0, -1.0,
	1.0, -1.0, -1.0, 0.0, 0.0, -1.0,
	-1.0, -1.0, 1.0, 0.0, 0.0, 1.0,
	1.0, -1.0, 1.0, 0.0, 0.0, 1.0,
	-1.0, 1.0, 1.0, 0.0, 0.0, 1.0,
	-1.0, 1.0, 1.0, 0.0, 0.0, 1.0,
	1.0, 1.0, 1.0, 0.0, 0.0, 1.0,
	1.0, -1.0, 1.0, 0.0, 0.0, 1.0,
	-1.0, -1.0, -1.0, -1.0, 0.0, 0.0,
	-1.0, -1.0, 1.0, -1.0, 0.0, 0.0,
	-1.0, 1.0, 1.0, -1.0, 0.0, 0.0,
	-1.0, 1.0, -1.0, -1.0, 0.0, 0.0,
	-1.0, -1.0, -1.0, -1.0, 0.0, 0.0,
	-1.0, 1.0, 1.0, -1.0, 0.0, 0.0,
	1.0, -1.0, -1.0, 1.0, 0.0, 0.0,
	1.0, -1.0, 1.0, 1.0, 0.0, 0.0,
	1.0, 1.0, 1.0, 1.0, 0.0, 0.0,
	1.0, 1.0, -1.0, 1.0, 0.0, 0.0,
	1.0, -1.0, -1.0, 1.0, 0.0, 0.0,
	1.0, 1.0, 1.0, 1.0, 0.0, 0.0,
	-1.0, -1.0, -1.0, 0.0, -1.0, 0.0,
	1.0, -1.0, -1.0, 0.0, -1.0, 0.0,
	1.0, -1.0, 1.0, 0.0, -1.0, 0.0,
	1.0, -1.0, 1.0, 0.0, -1.0, 0.0,
	-1.0, -1.0, 1.0, 0.0, -1.0, 0.0,
	-1.0, -1.0, -1.0, 0.0, -1.0, 0.0,
	-1.0, 1.0, -1.0, 0.0, 1.0, 0.0,
	1.0, 1.0, -1.0, 0.0, 1.0, 0.0,
	1.0, 1.0, 1.0, 0.0, 1.0, 0.0,
	1.0, 1.0, 1.0, 0.0, 1.0, 0.0,
	-1.0, 1.0, 1.0, 0.0, 1.0, 0.0,
	-1.0, 1.0, -1.0, 0.0, 1.0, 0.0
};

float sticker_colors[21] = {
	0.9, 0.05, 0.05,
	0.9, 0.9, 0.05,
	0.05, 0.9, 0.05,
	0.9, 0.4, 0.05,
	0.8, 0.8, 0.8,
	0.05, 0.05, 0.9,
	0.05, 0.05, 0.05
};

float cubie_positions[78] = {
	-2.0, -2.0, -2.0,
	0.0, -2.0, -2.0,
	2.0, -2.0, -2.0,
	-2.0, 0.0, -2.0,
	0.0, 0.0, -2.0,
	2.0, 0.0, -2.0,
	-2.0, 2.0, -2.0,
	0.0, 2.0, -2.0,
	2.0, 2.0, -2.0,
	-2.0, -2.0, 0.0,
	0.0, -2.0, 0.0,
	2.0, -2.0, 0.0,
	-2.0, 0.0, 0.0,
	2.0, 0.0, 0.0,
	-2.0, 2.0, 0.0,
	0.0, 2.0, 0.0,
	2.0, 2.0, 0.0,
	-2.0, -2.0, 2.0,
	0.0, -2.0, 2.0,
	2.0, -2.0, 2.0,
	-2.0, 0.0, 2.0,
	0.0, 0.0, 2.0,
	2.0, 0.0, 2.0,
	-2.0, 2.0, 2.0,
	0.0, 2.0, 2.0,
	2.0, 2.0, 2.0
};

unsigned char stickers[26][6] = {
	{0, 1, 2, 6, 6, 6},
	{0, 1, 6, 6, 6, 6},
	{0, 1, 6, 6, 6, 5},
	{0, 6, 2, 6, 6, 6},
	{0, 6, 6, 6, 6, 6},
	{0, 6, 6, 6, 6, 5},
	{0, 6, 2, 6, 4, 6},
	{0, 6, 6, 6, 4, 6},
	{0, 6, 6, 6, 4, 5},
	{6, 1, 2, 6, 6, 6},
	{6, 1, 6, 6, 6, 6},
	{6, 1, 6, 6, 6, 5},
	{6, 6, 2, 6, 6, 6},
	{6, 6, 6, 6, 6, 5},
	{6, 6, 2, 6, 4, 6},
	{6, 6, 6, 6, 4, 6},
	{6, 6, 6, 6, 4, 5},
	{6, 1, 2, 3, 6, 6},
	{6, 1, 6, 3, 6, 6},
	{6, 1, 6, 3, 6, 5},
	{6, 6, 2, 3, 6, 6},
	{6, 6, 6, 3, 6, 6},
	{6, 6, 6, 3, 6, 5},
	{6, 6, 2, 3, 4, 6},
	{6, 6, 6, 3, 4, 6},
	{6, 6, 6, 3, 4, 5}
};

int sides_corners[6][4] = {
	{0, 2, 8, 6},
	{19, 25, 23, 17},
	{0, 6, 23, 17},
	{8, 25, 19, 2},
	{0, 17, 19, 2},
	{23, 25, 8, 6}
};

int sides_edges[6][4] = {
	{1, 5, 7, 3},
	{18, 22, 24, 20},
	{3, 14, 20, 9},
	{5, 16, 22, 11},
	{9, 18, 11, 1},
	{14, 24, 16, 7}
};

int sides_centers[6] = {4, 21, 12, 13, 10, 15};

int sides[6][9] = {
	{0, 1, 2, 5, 8, 7, 6, 3, 4},
	{17, 20, 23, 24, 25, 22, 19, 18, 21},
	{0, 3, 6, 14, 23, 20, 17, 9, 12},
	{2, 11, 19, 22, 25, 16, 8, 5, 13},
	{0, 9, 17, 18, 19, 11, 2, 1, 10},
	{6, 7, 8, 16, 25, 24, 23, 14, 15}
};
//0 blue 1 white 2 orange 3 green 4 yellow 5 red
int rotations[6][6] = {
	{0, 2, 4, 3, 5, 1},
	{0, 5, 1, 3, 2, 4},
	{1, 3, 2, 4, 0, 5},
	{4, 0, 2, 1, 3, 5},
	{5, 1, 0, 2, 4, 3},
	{2, 1, 3, 5, 4, 0}
};

float side_axes[6][3] = {
	{0, 0, 1},
	{0, 0, -1},
	{1, 0, 0},
	{-1, 0, 0},
	{0, 1, 0},
	{0, -1, 0}
};

struct orientation{
	float x;
	float y;
	float z;
	float w;
};

struct orientation camera_orientation = (struct orientation) {.x = 1, .y = 0, .z = 0, .w = 0};
unsigned int cube_VAO;
unsigned int cube_VBO;
unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int shaderProgram;
int vertexColorLocation;
int resolutionLocation;
int modelPositionLocation;
int modelOrientationLocation;
int fovconstLocation;
int stickerColorsLocation;
int resolution_x;
int resolution_y;
double last_x_pos = 0.0;
double last_y_pos = 0.0;
float current_time;
float animation_start_time = 0;
unsigned char animating = 1;
unsigned char animation_side = 4;
unsigned char animation_direction = 1;
char *vertex_shader_source;
char *fragment_shader_source;
GLFWwindow *window;

float smoothstep(float t){
	return t*t*(3 - 2*t);
}

void rotate(unsigned char *sticker_colors, unsigned char side, unsigned char direction){
	int index;
	unsigned char sticker_buffer[6];
	int i;

	index = (side&0xE) + direction;
	for(i = 0; i < 6; i++){
		sticker_buffer[i] = sticker_colors[rotations[index][i]];
	}

	memcpy(sticker_colors, sticker_buffer, sizeof(unsigned char)*6);
}

void twist(unsigned char side, unsigned char direction){
	int i;
	unsigned char sticker_buffer[6];

	if(!direction){
		memcpy(sticker_buffer, stickers[sides_corners[side][3]], sizeof(sticker_buffer));
		for(i = 3; i > 0; i--){
			memcpy(stickers[sides_corners[side][i]], stickers[sides_corners[side][i - 1]], sizeof(sticker_buffer));
		}
		memcpy(stickers[sides_corners[side][0]], sticker_buffer, sizeof(sticker_buffer));

		memcpy(sticker_buffer, stickers[sides_edges[side][3]], sizeof(sticker_buffer));
		for(i = 3; i > 0; i--){
			memcpy(stickers[sides_edges[side][i]], stickers[sides_edges[side][i - 1]], sizeof(sticker_buffer));
		}
		memcpy(stickers[sides_edges[side][0]], sticker_buffer, sizeof(sticker_buffer));
	} else {
		memcpy(sticker_buffer, stickers[sides_corners[side][0]], sizeof(sticker_buffer));
		for(i = 0; i < 3; i++){
			memcpy(stickers[sides_corners[side][i]], stickers[sides_corners[side][i + 1]], sizeof(sticker_buffer));
		}
		memcpy(stickers[sides_corners[side][3]], sticker_buffer, sizeof(sticker_buffer));

		memcpy(sticker_buffer, stickers[sides_edges[side][0]], sizeof(sticker_buffer));
		for(i = 0; i < 3; i++){
			memcpy(stickers[sides_edges[side][i]], stickers[sides_edges[side][i + 1]], sizeof(sticker_buffer));
		}
		memcpy(stickers[sides_edges[side][3]], sticker_buffer, sizeof(sticker_buffer));
	}

	for(i = 0; i < 8; i++){
		rotate(stickers[sides[side][i]], side, direction);
	}
}

struct orientation create_orientation(float angle, float x, float y, float z){
	float s;
	float len;
	struct orientation out;

	s = sin(angle);
	len = sqrt(x*x + y*y + z*z);
	out.x = cos(angle);
	out.y = x*s/len;
	out.z = y*s/len;
	out.w = z*s/len;

	return out;
}

struct orientation compose_orientation(struct orientation a, struct orientation b){
	struct orientation out;
	out.x = a.x*b.x - a.y*b.y - a.z*b.z - a.w*b.w;
	out.y = a.x*b.y + a.y*b.x + a.z*b.w - a.w*b.z;
	out.z = a.x*b.z - a.y*b.w + a.z*b.x + a.w*b.y;
	out.w = a.x*b.w + a.y*b.z - a.z*b.y + a.w*b.x;

	return out;
}

struct orientation inverse_orientation(struct orientation a){
	return (struct orientation) {.x = a.x, .y = -a.y, .z = -a.z, .w = -a.w};
}

struct orientation apply_orientation(struct orientation orient, struct orientation point){
	return compose_orientation(compose_orientation(orient, point), inverse_orientation(orient));
}

struct orientation normalize_orientation(struct orientation orient){
	float len;

	len = sqrt(orient.x*orient.x + orient.y*orient.y + orient.z*orient.z + orient.w*orient.w);
	return (struct orientation) {.x = orient.x/len, .y = orient.y/len, .z = orient.z/len, .w = orient.w/len};
}

char *load_file(const char *file_name){
	FILE *fp;
	size_t fsize;
	char *output;

	fp = fopen(file_name, "rb");
	if(!fp){
		fprintf(stderr, "Error: failed to load file.\n");
		glfwTerminate();
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	fsize = ftell(fp);
	rewind(fp);
	output = calloc(fsize + 1, sizeof(char));
	if(!output){
		fprintf(stderr, "Error: failed to allocate memory.\n");
		glfwTerminate();
		exit(1);
	}
	fread(output, sizeof(char), fsize, fp);
	fclose(fp);

	return output;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height){
	glViewport(0, 0, width, height);
	resolution_x = width;
	resolution_y = height;
}

void process_input(GLFWwindow *window){
	double x_pos;
	double y_pos;
	double x_diff;
	double y_diff;
	struct orientation orient_x;
	struct orientation orient_y;
	int mouse_state;

	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);
	}
	glfwGetCursorPos(window, &x_pos, &y_pos);
	mouse_state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if(mouse_state == GLFW_PRESS && (x_pos != last_x_pos || y_pos != last_y_pos)){
		x_diff = x_pos - last_x_pos;
		y_diff = y_pos - last_y_pos;
		orient_x = create_orientation(fmod(x_diff/resolution_x*3.14, 6.28), 0, -1, 0);
		orient_y = create_orientation(fmod(y_diff/resolution_y*3.14, 6.28), -1, 0, 0);
		camera_orientation = compose_orientation(orient_x, camera_orientation);
		camera_orientation = compose_orientation(orient_y, camera_orientation);
		camera_orientation = normalize_orientation(camera_orientation);
	}
	last_x_pos = x_pos;
	last_y_pos = y_pos;
}

void render_cubie(float pos_x, float pos_y, float pos_z, float orient_x, float orient_y, float orient_z, float orient_w, float *colors){
	glUseProgram(shaderProgram);
	glUniform2f(resolutionLocation, resolution_x, resolution_y);
	glUniform3f(modelPositionLocation, pos_x, pos_y, pos_z);
	glUniform4f(modelOrientationLocation, orient_x, orient_y, orient_z, orient_w);
	glUniform1f(fovconstLocation, 1.0);
	glUniform3fv(stickerColorsLocation, 6, colors);
	glBindVertexArray(cube_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

unsigned char on_side(int cubie, int side){
	int i;
	
	for(i = 0; i < 9; i++){
		if(sides[side][i] == cubie){
			return 1;
		}
	}

	return 0;
}

void render_cube(){
	int i;
	int j;
	struct orientation point;
	struct orientation orient;
	float colors[18];

	if(animating && current_time - animation_start_time > 3.14159/4){
		twist(animation_side, animation_direction);
		animation_start_time = current_time;
		animation_side = rand()%6;
		animation_direction = rand()&1;
	}

	for(i = 0; i < 26; i++){
		point = (struct orientation) {.x = 0, .y = cubie_positions[3*i], .z = cubie_positions[3*i + 1], .w = cubie_positions[3*i + 2]};
		if(animating && on_side(i, animation_side)){
			orient = compose_orientation(camera_orientation, create_orientation(smoothstep(4*(current_time - animation_start_time)/3.14)*3.14/4, side_axes[(animation_side&0xE) + animation_direction][0], side_axes[(animation_side&0xE) + animation_direction][1], side_axes[(animation_side&0xE) + animation_direction][2]));
		} else {
			orient = camera_orientation;
		}
		point = apply_orientation(orient, point);

		for(j = 5; j >= 0; j--){
			if(stickers[i][5 - j] == 6){
				colors[j*3] = 0.05;
				colors[j*3 + 1] = 0.05;
				colors[j*3 + 2] = 0.05;
			} else {
				colors[j*3] = sticker_colors[(5 - stickers[i][5 - j])*3];
				colors[j*3 + 1] = sticker_colors[(5 - stickers[i][5 - j])*3 + 1];
				colors[j*3 + 2] = sticker_colors[(5 - stickers[i][5 - j])*3 + 2];
			}
		}
		render_cubie(point.y, point.z, point.w + 10, orient.x, orient.y, orient.z, orient.w, colors);
	}
}

void free_and_exit(int code){
	glDeleteVertexArrays(1, &cube_VAO);
	glDeleteBuffers(1, &cube_VBO);
	glDeleteProgram(shaderProgram);
	menu_deinit();
	glfwTerminate();
	free(vertex_shader_source);
	free(fragment_shader_source);
	exit(code);
}

menu *create_main_menu(){
	menu *output;
	unsigned char *tex_data;
	unsigned int width;
	unsigned int height;
	double screen_coord_x;
	double screen_coord_y;
	double screen_coord_width;
	double screen_coord_height;
	
	output = create_menu(1);
	if(!output){
		fprintf(stderr, "Error: could not create menu\n");
		free_and_exit(1);
	}
	tex_data = load_tga("scramble.tga", &width, &height);
	if(!tex_data){
		free_menu(output);
		fprintf(stderr, "Error: could not load 'scramble.tga'\n");
		free_and_exit(1);
	}
	screen_coord_height = 0.1;
	screen_coord_width = (double) resolution_x*width/(resolution_y*height)*0.1;
	screen_coord_y = 0.7;
	screen_coord_x = 0.5 - screen_coord_width/2;
	//menu_set_texture(output, 0, 0, 0, 1, 1, width, height, tex_data);
	menu_set_texture(output, 0, screen_coord_x, screen_coord_y, screen_coord_width, screen_coord_height, width, height, tex_data);
	prepare_menu(output);
	free(tex_data);
	return output;
}

int render_menu_function(){
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	current_time = glfwGetTime();
	camera_orientation = create_orientation(sin(fmod(current_time/5.0, 6.28)) + 1.0, cos(fmod(current_time/3.7, 6.28)), sin(fmod(current_time/1.68, 6.28)), cos(fmod(current_time/2.72, 6.28)));
	render_cube();
	return 0;
}

void do_main_menu(){
	menu *m;
	int selection;

	m = create_main_menu();
	selection = do_menu(window, m, 0, render_menu_function);
	if(selection == -1){
		free_menu(m);
		free_and_exit(1);
	}
}

int main(int argc, char **argv){
	int success;
	char infolog[512];

	srand(time(NULL));
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	window = glfwCreateWindow(800, 600, "Rubik's Cube", NULL, NULL);
	if(window == NULL){
		fprintf(stderr, "Error: failed to create window.\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);
	if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
		fprintf(stderr, "Error: failed to initialize GLAD.\n");
		glfwTerminate();
		return 1;
	}
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glGenVertexArrays(1, &cube_VAO);
	glGenBuffers(1, &cube_VBO);

	glBindVertexArray(cube_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, cube_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void *) 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void *) (3*sizeof(float)));
	glEnableVertexAttribArray(1);

	//Load my vertex shader
	vertex_shader_source = load_file("src/vertex.glsl");

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const char * const *) &vertex_shader_source, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
		fprintf(stderr, "Error: failed to compile vertex shader:\n%s\n", infolog);
		glfwTerminate();
		free(vertex_shader_source);
		return 1;
	}
	
	//Load my fragment shader
	fragment_shader_source = load_file("src/frag.glsl");

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const char * const *) &fragment_shader_source, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
		fprintf(stderr, "Error: failed to compile fragment shader:\n%s\n", infolog);
		glfwTerminate();
		free(vertex_shader_source);
		free(fragment_shader_source);
		return 1;
	}
	
	//Linking the shaders
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success){
		glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
		fprintf(stderr, "Error: failed to link shaders:\n%s\n", infolog);
		glfwTerminate();
		free(vertex_shader_source);
		free(fragment_shader_source);
		return 1;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	if(!menu_init()){
		fprintf(stderr, "Error: menu_init returned zero\n");
		glfwTerminate();
		free(vertex_shader_source);
		free(fragment_shader_source);
		return 1;
	}

	resolutionLocation = glGetUniformLocation(shaderProgram, "resolution");
	modelPositionLocation = glGetUniformLocation(shaderProgram, "model_position");
	modelOrientationLocation = glGetUniformLocation(shaderProgram, "model_orientation");
	fovconstLocation = glGetUniformLocation(shaderProgram, "fov_const");
	stickerColorsLocation = glGetUniformLocation(shaderProgram, "sticker_colors");

	glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_MULTISAMPLE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwGetWindowSize(window, &resolution_x, &resolution_y);
	do_main_menu();
	glfwGetCursorPos(window, &last_x_pos, &last_y_pos);

	while(!glfwWindowShouldClose(window)){
		process_input(window);

		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		current_time = glfwGetTime();
		render_cube();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &cube_VAO);
	glDeleteBuffers(1, &cube_VBO);
	glDeleteProgram(shaderProgram);
	menu_deinit();
	glfwTerminate();
	free(vertex_shader_source);
	free(fragment_shader_source);
	return 0;
}

