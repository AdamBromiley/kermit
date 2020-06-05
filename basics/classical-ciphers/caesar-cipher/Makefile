.SUFFIXES:
.SUFFIXES: .c .h .o .so

COMMA = ,
NULL =
SPACE = $(NULL) $(NULL)




# Output binary
_BIN = caesar
BDIR = .
BIN = $(BDIR)/$(_BIN)

# Source code
_SRC = caesar.c caesar_cipher.c
SDIR = src
SRC = $(patsubst %,$(SDIR)/%,$(_SRC))

# Header files
_DEPS = caesar.h caesar_cipher.h
HDIR = include
DEPS = $(patsubst %,$(HDIR)/%,$(_DEPS))

# Object files
_OBJS = caesar.o caesar_cipher.o
ODIR = obj
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))




# Path to project library
LDIR = ../../../lib

# Include directories
_IDIRS = include $(LDIR)/scutils/include
IDIRS = $(patsubst %,-I%,$(_IDIRS))

# Libraries to be linked with `-l`
_LDLIBS = scutils
LDLIBS = $(patsubst %,-l%,$(_LDLIBS))

# Library search paths, `-L`, and run-time search paths
_LPATHS = $(LDIR)/scutils
_RPATHS = $(patsubst %,-rpath=%,$(_LPATHS))
LPATHS = $(patsubst %,-L%,$(_LPATHS))
RPATHS = $(subst $(SPACE),$(COMMA),$(_RPATHS))




# Compiler name
CC = gcc

# Compiler options
CFLAGS = $(IDIRS) -g -std=c99 -pedantic \
	-Wall -Wextra -Wcast-align -Wcast-qual -Wdisabled-optimization -Wformat=2 \
	-Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs \
	-Wredundant-decls -Wshadow -Wsign-conversion -Wstrict-overflow=5 \
	-Wswitch-default -Wundef


# Linker name
LD = gcc

# Linker options
LDFLAGS = $(LPATHS) -Wl,$(RPATHS) $(LDLIBS)




.PHONY: all
all: $(BIN)




# Directories with other Makefiles that must be called
MKDIRS = $(LDIR)/scutils

.PHONY: mkdirs $(MKDIRS)

mkdirs: $(MKDIRS)
$(MKDIRS):
	@ cd $@ && $(MAKE)




# Compile source into object files
$(OBJS): $(ODIR)/%.o: $(SDIR)/%.c
	@ mkdir -p $(ODIR)
	$(CC) -c $< $(CFLAGS) -o $@

# Link object files into executable
$(BIN): $(OBJS) mkdirs
	@ mkdir -p $(BDIR)
	$(LD) $(OBJS) $(LDFLAGS) -o $(BIN)




.PHONY: clean cleanall

# Perform `make clean` on dependencies in addition
cleanall: clean
	for directory in $(MKDIRS); do \
		cd $$directory && $(MAKE) clean; \
	done

# Remove object files and binary
clean:
	rm -f $(OBJS) $(BIN)