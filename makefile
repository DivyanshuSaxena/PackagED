IDIR =./include
INDIR =./lib
CC=g++
CFLAGS=-I$(IDIR) -I$(INDIR)
GLFLAGS= -lglut -lGL -lGLU
GTK= `pkg-config gtkmm-3.0 --cflags --libs`

ODIR =./bin
LDIR =./lib
SDIR =./src
BDIR =./build

LIBS=-lm

_DEPS = Classes.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_GDEPS = Classes.h gui.h
GDEPS = $(patsubst %,$(IDIR)/%,$(_GDEPS))

_OBJ = Point.o Object3D.o Projection2D.o OrthoProjection.o Main.o Maingui.o Pointgui.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_GOBJ = Maingui.o Pointgui.o
GOBJ = $(patsubst %,$(ODIR)/%,$(_GOBJ))

_SRC = Point.cpp Object3D.cpp Projection2D.cpp OrthoProjection.cpp Main.cpp
SRC = $(patsubst %,$(SDIR)/%,$(_SRC))

_GSRC = Maingui.cpp Pointgui.cpp
GSRC = $(patsubst %,$(SDIR)/%,$(_GSRC))

ESS = ./bin/Point.o ./bin/Main.o

_BUILDS = main
BUILDS = $(patsubst %,$(BDIR)/%,$(_BUILDS))

MKDIR = mkdir -p

OUT_DIR = bin build

GTKFLAG = `pkg-config --cflags --libs gtkmm-3.0`

$(ODIR)/%.o: $(SDIR)/%.cpp $(GDEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(GTKFLAG)

all: directories $(BUILDS)

directories: 
	$(MKDIR) $(OUT_DIR)

$(BDIR)/main: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS) $(GLFLAGS) $(LIBS) $(GTKFLAG) 

