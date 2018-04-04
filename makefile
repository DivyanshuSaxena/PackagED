IDIR =./include
INDIR =./lib
CC=g++
CFLAGS=-I$(IDIR) -I$(INDIR)
GTKFLAG = `pkg-config gtkmm-3.0 --cflags --libs`

ODIR =./bin/source
OGDIR=./bin/gui
LDIR =./lib
SDIR =./src
BDIR =./build
TDIR = ./test

LIBS=-lm

_DEPS = Classes.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_GDEPS = Classes.h gui.h
GDEPS = $(patsubst %,$(IDIR)/%,$(_GDEPS))

_OBJ = Point.o Object3D.o Projection2D.o OrthoProjection.o PlaneProjection.o Wireframe.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_GOBJ = Main.o Maingui.o Projectgui.o Constructgui.o
GOBJ = $(patsubst %,$(OGDIR)/%,$(_GOBJ))

_BUILDS = main
BUILDS = $(patsubst %,$(BDIR)/%,$(_BUILDS))
TESTS = $(patsubst %,$(TDIR)/%,$(_BUILDS))

MKDIR = mkdir -p

OUT_DIR = bin/gui bin/source build

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(GTKFLAG)

$(OGDIR)/%.o: $(SDIR)/%.cpp $(GDEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(GTKFLAG)

all: directories $(BUILDS) $(TESTS)

directories: 
	$(MKDIR) $(OUT_DIR)

$(BDIR)/main: $(OBJ) $(GOBJ)
		$(CC) -o $@ $^ $(CFLAGS) $(GTKFLAG) $(LIBS) 
$(TDIR)/main: $(OBJ) $(GOBJ)
		$(CC) -o $@ $^ $(CFLAGS) $(GTKFLAG) $(LIBS) 
