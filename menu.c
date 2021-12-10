#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include "menu.h"

static char *fragment_source;
static char *vertex_source;
static int fragment_shader;
static int vertex_shader;
static int shader_program;
static int texture_locations[16];

static char *load_file(const char *file_name){
	FILE *fp;
	size_t fsize;
	char *output;

	fp = fopen(file_name, "rb");
	if(!fp){
		return NULL;
	}
	fseek(fp, 0, SEEK_END);
	fsize = ftell(fp);
	rewind(fp);
	output = calloc(fsize + 1, sizeof(char));
	if(!output){
		return NULL;
	}
	fread(output, sizeof(char), fsize, fp);
	fclose(fp);

	return output;
}

int menu_init(){
	int status;
	int i;
	char char_buffer[32];
	char info_log[512];

	vertex_source = load_file("menu_vertex.glsl");
	if(!vertex_source){
		return 0;
	}
	fragment_source = load_file("menu_frag.glsl");
	if(!fragment_source){
		free(vertex_source);
		return 0;
	}

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, (const char * const *) &vertex_source, NULL);
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);
	if(!status){
		free(vertex_source);
		free(fragment_source);
		glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
		fprintf(stderr, "Error: failed to compile vertex shader:\n%s\n", info_log);
		glDeleteShader(vertex_shader);
		return 0;
	}

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, (const char * const *) &fragment_source, NULL);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &status);
	if(!status){
		free(vertex_source);
		free(fragment_source);
		glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
		fprintf(stderr, "Error: failed to compile fragment shader:\n%s\n", info_log);
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
		return 0;
	}
	free(vertex_source);
	free(fragment_source);

	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);
	glGetProgramiv(shader_program, GL_LINK_STATUS, &status);
	if(!status){
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
		glDeleteProgram(shader_program);
		return 0;
	}
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	for(i = 0; i < 16; i++){
		sprintf(char_buffer, "textures[%d]", i);
		texture_locations[i] = glGetUniformLocation(shader_program, char_buffer);
	}

	return 1;
}

void menu_deinit(){
	glDeleteProgram(shader_program);
}

menu *create_menu(unsigned int num_buttons){
	menu *output;

	if(num_buttons > 16){
		return NULL;
	}

	output = malloc(sizeof(menu));
	if(!output){
		return NULL;
	}

	output->vertices = malloc(sizeof(float)*num_buttons*36);
	if(!output->vertices){
		free(output);
		return NULL;
	}

	output->num_buttons = num_buttons;
	glGenTextures(num_buttons, output->textures);
	glGenVertexArrays(1, &(output->VAO));
	glGenBuffers(1, &(output->VBO));

	return output;
}

void menu_set_texture(menu *m, unsigned int texture_id, float pos_x, float pos_y, float width_x, float width_y, int texture_width, int texture_height, unsigned char *texture_data){
	pos_x = pos_x*2.0 - 1.0;
	pos_y = 1.0 - pos_y*2.0 - 2*width_y;
	width_x *= 2.0;
	width_y *= 2.0;
	glActiveTexture(GL_TEXTURE0 + texture_id);
	glBindTexture(GL_TEXTURE_2D, m->textures[texture_id]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_width, texture_height, 0, GL_BGRA, GL_UNSIGNED_BYTE, texture_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	glUseProgram(shader_program);
	glUniform1i(texture_locations[texture_id], texture_id);
	m->vertices[36*texture_id] = pos_x;
	m->vertices[36*texture_id + 1] = pos_y;
	m->vertices[36*texture_id + 2] = 0;
	m->vertices[36*texture_id + 3] = 0;
	m->vertices[36*texture_id + 4] = 0;
	m->vertices[36*texture_id + 5] = texture_id;
	m->vertices[36*texture_id + 6] = pos_x;
	m->vertices[36*texture_id + 7] = pos_y + width_y;
	m->vertices[36*texture_id + 8] = 0;
	m->vertices[36*texture_id + 9] = 0;
	m->vertices[36*texture_id + 10] = 1;
	m->vertices[36*texture_id + 11] = texture_id;
	m->vertices[36*texture_id + 12] = pos_x + width_x;
	m->vertices[36*texture_id + 13] = pos_y + width_y;
	m->vertices[36*texture_id + 14] = 0;
	m->vertices[36*texture_id + 15] = 1;
	m->vertices[36*texture_id + 16] = 1;
	m->vertices[36*texture_id + 17] = texture_id;
	m->vertices[36*texture_id + 18] = pos_x;
	m->vertices[36*texture_id + 19] = pos_y;
	m->vertices[36*texture_id + 20] = 0;
	m->vertices[36*texture_id + 21] = 0;
	m->vertices[36*texture_id + 22] = 0;
	m->vertices[36*texture_id + 23] = texture_id;
	m->vertices[36*texture_id + 24] = pos_x + width_x;
	m->vertices[36*texture_id + 25] = pos_y;
	m->vertices[36*texture_id + 26] = 0;
	m->vertices[36*texture_id + 27] = 1;
	m->vertices[36*texture_id + 28] = 0;
	m->vertices[36*texture_id + 29] = texture_id;
	m->vertices[36*texture_id + 30] = pos_x + width_x;
	m->vertices[36*texture_id + 31] = pos_y + width_y;
	m->vertices[36*texture_id + 32] = 0;
	m->vertices[36*texture_id + 33] = 1;
	m->vertices[36*texture_id + 34] = 1;
	m->vertices[36*texture_id + 35] = texture_id;
}

void prepare_menu(menu *m){
	glBindVertexArray(m->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*36*m->num_buttons, m->vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void *) 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void *) (3*sizeof(float)));
	glEnableVertexAttribArray(1);
}

void render_menu(menu *m){
	glUseProgram(shader_program);
	glBindVertexArray(m->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6*m->num_buttons);
}

void free_menu(menu *m){
	glDeleteVertexArrays(1, &(m->VAO));
	glDeleteBuffers(1, &(m->VBO));
	free(m->vertices);
	free(m);
}

static unsigned char pos_in_button(GLFWwindow *window, menu *m, double x_pos, double y_pos, int button_id){
	int win_width;
	int win_height;
	double button_screen_space_x0;
	double button_screen_space_y0;
	double button_screen_space_x1;
	double button_screen_space_y1;

	glfwGetWindowSize(window, &win_width, &win_height);
	button_screen_space_x0 = m->vertices[36*button_id];
	button_screen_space_y0 = m->vertices[36*button_id + 1];
	button_screen_space_x1 = m->vertices[36*button_id + 30];
	button_screen_space_y1 = m->vertices[36*button_id + 31];
	x_pos = 2.0*x_pos/win_width - 1.0;
	y_pos = 1.0 - 2.0*y_pos/win_height;
	if(x_pos > button_screen_space_x0 && x_pos < button_screen_space_x1 && y_pos > button_screen_space_y0 && y_pos < button_screen_space_y1){
		return 1;
	} else {
		return 0;
	}
}

int do_menu(GLFWwindow *window, menu *m, unsigned int mask, int (*render_func)()){
	int i;
	double x_pos;
	double y_pos;
	int return_value;

	while(!glfwWindowShouldClose(window)){
		if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
			glfwGetCursorPos(window, &x_pos, &y_pos);
			for(i = 0; i < m->num_buttons; i++){
				if((mask>>i)&1){
					continue;
				}
				if(pos_in_button(window, m, x_pos, y_pos, i)){
					return i;
				}
			}
		}
		return_value = render_func();
		if(return_value){
			return return_value;
		}
		render_menu(m);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return -1;
}

