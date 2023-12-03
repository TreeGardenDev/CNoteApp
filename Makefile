OSTYPE=$(shell uname)

LIBS		= sdl ftgl fontconfig 
CFLAGS		= -O$(OPTIMIZE) -std=c99  -Wall `pkg-config --cflags $(LIBS)`
LDFLAGS		= `pkg-config --libs $(LIBS)` -lm

ifeq ($(OSTYPE),Darwin)
	LIBS		+= freetype2
	LDFLAGS		+= -framework OpenGL
else
	LIBS		+= gl
endif

EXECUTABLE = gcodeview

OPTIMIZE	= 2

SOURCES		= noteapp.c
OBJECTS		= $(SOURCES:.c=.o)

.PHONY: all clean

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	@echo Building for [$(OSTYPE)].

%.o: %.c
	$(CC) $(CFLAGS) -std=c99 -c $< -o $@

clean:
	rm $(OBJECTS) $(EXECUTABLE)
