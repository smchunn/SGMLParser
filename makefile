
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	OSFLAG := linux
    SHARED_LIB := libsystem5msg.so
    LINK_FLAGS := -shared
endif
ifeq ($(UNAME_S),Darwin)
	OSFLAG := darwin
    SHARED_LIB := libsystem5msg.dylib
    LINK_FLAGS := -dynamiclib
endif

all : sgmlparser

    
sgmlparser:sgmlParser.c sgmlParser.h
	gcc -std=c99 -DNDEBUG -D_GNU_SOURCE $(MAC_FLAG) sgmlParser.c -o sgmlParser

clean :
	rm -f sgmlParser
