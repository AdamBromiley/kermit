.SUFFIXES:
.SUFFIXES: .c .h .o .so

COMMA = ,
NULL =
SPACE = $(NULL) $(NULL)


BDIR = .
SDIR = src
IDIR = include
ODIR = obj
LDIR = ../../../lib
# Directories with Makefiles that must be called
MKDIRS = $(LDIR)/scutils

_BIN = caesar
_SRC = caesar.c caesar_cipher.c
_DEPS = caesar.h caesar_cipher.h
_OBJS = caesar.o caesar_cipher.o
# Libraries to be linked with `-l`
_LDLIBS = scutils
# Libraries requiring a specified run-time search path
_RLIBS = scutils

# Compiler name
CC = gcc

# Compiler options
CFLAGS = -g -I$(IDIR) -I$(LDIR)/scutils/include -std=c99 -pedantic \
	-Wall -Wextra -Wcast-align -Wcast-qual -Wdisabled-optimization -Wformat=2 \
	-Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs \
	-Wredundant-decls -Wshadow -Wsign-conversion -Wstrict-overflow=5 \
	-Wswitch-default -Wundef

# Linker options
LDFLAGS = -L$(LDIR)/scutils -Wl,$(RPATHS)


BIN = $(BDIR)/$(_BIN)
SRC = $(patsubst %,$(SDIR)/%,$(_SRC))
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

LDLIBS = $(patsubst %,-l%,$(_LDLIBS))

_RPATHS = $(patsubst %,-rpath=$(LDIR)/%,$(_RLIBS))
RPATHS = $(subst $(SPACE),$(COMMA),$(_RPATHS))


all: $(BIN)


# Make dependencies
$(MKDIRS):
	@ cd $< && make

# Compile source into object files
$(OBJS): $(ODIR)/%.o: $(SDIR)/%.c $(MKDIRS)
	@ mkdir -p $(ODIR)
	$(CC) -c $< $(CFLAGS) -o $@

# Link object files into executable
$(BIN): $(OBJS) $(MKDIRS)
	@ mkdir -p $(BDIR)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(BIN)


# Remove object files and executable
.PHONY: clean
clean:
	rm -f $(OBJS) $(BIN)