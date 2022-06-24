#ifndef SGML_PARSER_H
#define SGML_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TRUE
	#define TRUE 1
#endif
#ifndef FALSE
	#define  FALSE 0
#endif

// Define

typedef struct {
	char* source;
} SGMLDoc;

int SGMLDoc_loader(SGMLDoc* doc, const char* path);
void SGMLDoc_free(SGMLDoc* doc);


// Implement


int SGMLDoc_loader(SGMLDoc* doc, const char* path){
	FILE* file = fopen(path, "r");
	if(!file){
		fprintf(stderr, "Could not load file from '%s'\n", path);
		return FALSE;
	}

	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	fseek(file, 0, SEEK_SET);

	doc->source = (char*) malloc(sizeof(char) * size + 1);
	fread(doc->source, 1, size, file);
	fclose(file);
	doc->source[size] = '\0';

	return TRUE;
}

void SGMLDoc_free(SGMLDoc* doc){
	free(doc->source);
}


#endif