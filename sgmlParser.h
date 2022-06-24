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

// 
// Define
// 

typedef struct _SGMLNode{
	char* tag;
	char* inner_text;
	struct _SGMLNode* parent;
} SGMLNode;

SGMLNode* SGMLNode_new(SGMLNode* parent);
void SGMLNode_free(SGMLNode* node);

typedef struct _SGMLDoc{
	char* source;
	SGMLNode* root;
} SGMLDoc;

int SGMLDoc_loader(SGMLDoc* doc, const char* path);
void SGMLDoc_free(SGMLDoc* doc);

// 
// Implement
// 

SGMLNode* SGMLNode_new(SGMLNode* parent){
	SGMLNode* node = (SGMLNode*) malloc(sizeof(SGMLNode));
	node->parent = parent;
	node->tag = NULL;
	node->inner_text = NULL;

	return node;
}
void SGMLNode_free(SGMLNode* node){
	if(node->tag)
		free(node->tag);
	if(node->inner_text)
		free(node->inner_text);
	free(node);
}

int SGMLDoc_loader(SGMLDoc* doc, const char* path){
	FILE* file = fopen(path, "r");
	if(!file){
		fprintf(stderr, "Could not load file from '%s'\n", path);
		return FALSE;
	}

	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* buf = (char*) malloc(sizeof(char) * size + 1);
	fread(buf, 1, size, file);
	fclose(file);
	buf[size] = '\0';

	doc->root = SGMLNode_new(NULL);

	char lex[256];
	int lexi = 0;
	int i = 0;

	SGMLNode* curr_node = NULL;

	while (buf[i] != '\0'){
		if(buf[i] == '<'){
			// inner text
			lex[lexi] = '\0';
			if(lexi > 0){
				if (!curr_node){
					fprintf(stderr,"Text outside of document\n");
					return FALSE;
				}
				curr_node->inner_text = strdup(lex);
			}

			// End of node
			if(buf[i + 1] == '/'){
				i += 2;
				while(buf[i] != '>')
					lex[lexi++] = buf[i++];
				lex[lexi] = '\0';

				if(!curr_node){
					fprintf(stderr,"Already at the root\n");
					return FALSE;
				}

				if(strcmp(curr_node->tag, lex)){
					fprintf(stderr, "Mismatched tags (%s != %s)", curr_node->tag, lex);
					return FALSE;
				}
				curr_node = curr_node->parent;
				i++;
				continue;
			}

			// set current node
			if(!curr_node)
				curr_node = doc->root;
			else
				curr_node = SGMLNode_new(curr_node);
			
			// get tag
			i++;
			while(buf[i] != '>')
				lex[lexi++] = buf[i++];
			lex[lexi] = '\0';
			curr_node->tag = strdup(lex);


			// reset lexer
			lexi = 0;
			i++;
			continue;
		}
		else{
			lex[lexi++] = buf[i++];
		}
	}
	return TRUE;
}

void SGMLDoc_free(SGMLDoc* doc){
	free(doc->source);
	SGMLNode_free(doc->root);
}


#endif