# General Makefile for small C programs
# Based on one by Alexender Hiam in Jan 2013
# Jim Mahoney | Jan 2016 | Public Domain

############################################################
# Modify these to fit your project.

# The name of the target executable
TARGET  = veranda

# Space separated list of all source files
SOURCES = single_lvl2_main.c single_lvl2_source.c

# Space separated directories containing source files
INCLUDE_DIRS =

# Compiler flags (e.g. optimization, links, etc.):
CFLAGS = -g -Wall

# Compiler:
CC = gcc

############################################################
# You probably won't need to change this part.

# Append -I to each include dir
INCLUDES = $(foreach dir, $(INCLUDE_DIRS), -I$(dir))

# Create list of the object files
OBJECTS = $(SOURCES:.c=.o)

all: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.c
	echo " Compiling $<"
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f *.o *.d
