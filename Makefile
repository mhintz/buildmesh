VERSION := 0.1.0

FILES := \
	buildmesh.cpp

OBJ = $(addprefix obj/, $(FILES:.cpp=.o))

OUT_DIR = build

CPPSTDFLAGS := -std=c++11 -stdlib=libc++
WARNINGFLAGS := -g -Wall -Wextra
COMPILEFLAGS := -MMD -O0

glminclude := -I$(brew --prefix glm)/include

.PHONY: all clean build

all: build

clean:
	rm -rf obj/*
	rm -rf $(OUT_DIR)/*

obj/%.o: %.cpp
	mkdir -p $(dir $@)
	clang++ -c $(CPPSTDFLAGS) $(WARNINGFLAGS) $(COMPILEFLAGS) $(glminclude) -o $@ $<

build: Makefile $(OBJ)
	mkdir -p $(OUT_DIR)
	libtool -static -o $(OUT_DIR)/buildmesh.lib $(OBJ)

