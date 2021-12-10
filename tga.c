#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static unsigned char header_template[18] = {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 0};

unsigned char *load_tga(const char *file_name, unsigned int *width, unsigned int *height){
	FILE *fp;
	unsigned char header[18];
	unsigned char *output;

	fp = fopen(file_name, "rb");
	if(!fp){
		return NULL;
	}

	if(fread(header, sizeof(unsigned char), 18, fp) < sizeof(unsigned char)*18){
		fclose(fp);
		return NULL;
	}

	if(memcmp(header, header_template, 12) || header[16] != 32){
		fclose(fp);
		return NULL;
	}
	*width = header[12] + 256*(unsigned int) header[13];
	*height = header[14] + 256*(unsigned int) header[15];

	output = malloc(sizeof(unsigned char)*4*(*width)*(*height));
	if(!output){
		fclose(fp);
		return NULL;
	}
	if(fread(output, sizeof(unsigned char), 4*(*width)*(*height), fp) < sizeof(unsigned char)*4*(*width)*(*height)){
		free(output);
		fclose(fp);
		return NULL;
	}
	
	fclose(fp);
	return output;
}

