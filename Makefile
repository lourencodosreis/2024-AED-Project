# ******************************************************************************
# 2024 AED PROJECT - Guilherme Gameiro, Lourenço Reis
#
# NAME
#   Makefile
#
# COMMENTS
#   To compile the program:
#		make
# 
# *****************************************************************************

# Variables.
CC = gcc
FLAGS = -Wall -std=c99 -O3
OBJECTS = navigate.o solving.o final_tasks.o dfs.o bound.o

# Main target.
navigate: $(OBJECTS)
	$(CC) $(FLAGS) -o $@ $(OBJECTS)

# Generic target for object file compilation.
%.o: %.c solving.h final_tasks.h dfs.h bound.h
	$(CC) $(FLAGS) -c $<

# Targets to remove generated files.
.PHONY: clean
clean:
	rm -f *.o navigate 