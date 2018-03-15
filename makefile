IDIR =./include
INDIR =./lib
CC=g++
CFLAGS=-I$(IDIR) -I$(INDIR)
GLFLAGS= -lglut -lGL -lGLU
GTKFLAG = `pkg-config gtkmm-3.0 --cflags --libs`

ODIR =./bin/source
OGDIR=./bin/gui
LDIR =./lib
SDIR =./src
BDIR =./build

LIBS=-lm

_DEPS = Classes.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_GDEPS = Classes.h gui.h
GDEPS = $(patsubst %,$(IDIR)/%,$(_GDEPS))

_OBJ = Point.o Object3D.o Projection2D.o OrthoProjection.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_GOBJ = Main.o Maingui.o Projectgui.o
GOBJ = $(patsubst %,$(OGDIR)/%,$(_GOBJ))

ESS = ./bin/Point.o ./bin/Main.o

_BUILDS = main
BUILDS = $(patsubst %,$(BDIR)/%,$(_BUILDS))

MKDIR = mkdir -p

OUT_DIR = bin/gui bin/source build

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(GTKFLAG)

$(OGDIR)/%.o: $(SDIR)/%.cpp $(GDEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(GTKFLAG)

all: directories $(BUILDS)

directories: 
	$(MKDIR) $(OUT_DIR)

$(BDIR)/main: $(OBJ) $(GOBJ)
		$(CC) -o $@ $^ $(CFLAGS) $(GTKFLAG) $(LIBS) 
