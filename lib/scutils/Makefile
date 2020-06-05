.SUFFIXES:
.SUFFIXES: .c .h .o .so

SDIR = src
IDIR = include
ODIR = obj
LDIR = .

# Source files
_SRC = log.c parser.c
SRC = $(patsubst %,$(SDIR)/%,$(_SRC))

# Header files
_DEPS = log.h parser.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

# Object files
_OBJS = log.o parser.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

# Output dynamic library
DLIB = $(LDIR)/libscutils.so

# Compiler name
CC = gcc

# GCC options
CFLAGS = -g -I$(IDIR) -std=c99 -pedantic \
	-Wall -Wextra -Wcast-align -Wcast-qual -Wdisabled-optimization -Wformat=2 \
	-Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs \
	-Wredundant-decls -Wshadow -Wsign-conversion -Wstrict-overflow=5 \
	-Wswitch-default -Wundef

# Linker options
LDFLAGS = -shared


all: $(DLIB)

# Compile source into object files
$(ODIR)/%.o: $(SDIR)/%.c
	@ mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

# Compile object files into dynamic library
$(DLIB): $(OBJS)
	@ mkdir -p $(LDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^


# Remove object files and dynamic library
.PHONY: clean
clean:
	rm -f $(OBJS) $(DLIB)