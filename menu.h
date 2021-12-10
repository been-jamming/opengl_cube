typedef struct menu menu;

struct menu{
	float *vertices;
	unsigned int textures[16];
	unsigned int num_buttons;
	unsigned int VAO;
	unsigned int VBO;
};

int menu_init();
void menu_deinit();
menu *create_menu(unsigned int num_buttons);
void menu_set_texture(menu *m, unsigned int texture_id, float pos_x, float pos_y, float width_x, float width_y, int texture_width, int texture_height, unsigned char *texture_data);
void prepare_menu(menu *m);
void render_menu(menu *m);
void free_menu(menu *m);
int do_menu(GLFWwindow *window, menu *m, unsigned int mask, int (*render_func)());

