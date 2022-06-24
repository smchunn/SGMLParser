#include "sgmlParser.h"

int main(int argc, char const *argv[]){
	SGMLDoc doc;
	if(SGMLDoc_loader(&doc, "test.xml")){
		printf("file: %s", doc.source);
		SGMLDoc_free(&doc);
	}
	return TRUE;
}