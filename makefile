IDIR =./include
CC=g++
CFLAGS=-I$(IDIR)
GLFLAGS= -lglut -lGL -lGLU
GTK= `pkg-config gtkmm-3.0 --cflags --libs`

ODIR =./bin
LDIR =./lib
SDIR =./src
BDIR =./build

LIBS=-lm

_DEPS = Classes.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Point.o Object3D.o Projection2D.o OrthoProjection.o Main.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

ESS = ./bin/Point.o ./bin/Main.o

_BUILDS = point object3d projection2d ortho main
BUILDS = $(patsubst %,$(BDIR)/%,$(_BUILDS))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(BUILDS)

$(BDIR)/point: $(ESS)
		$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(BDIR)/object3d: $(ESS) ./bin/Object3D.o ./bin/OrthoProjection.o
		$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(BDIR)/projection2d: $(ESS) ./bin/Projection2D.o ./bin/OrthoProjection.o
		$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(BDIR)/ortho: $(ESS) ./bin/OrthoProjection.o
		$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(BDIR)/main: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS) $(GLFLAGS) $(LIBS) 
