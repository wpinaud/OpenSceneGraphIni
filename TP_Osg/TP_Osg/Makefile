CSRCS=TP_OSG.cpp 

CFLAGS =  -c -O3 -DNDEBUG -fPIC

INCLUDE = -I. -I/usr/include/ -I/usr/include/X11/ -I/usr/local/include/GL -I/usr/local/include/osg
LDLIBS = -lm -ldl -lGL -lGLU -lOpenThreads -lXext -lX11

LDFLAGS =  -L. -L/usr/lib -L/usr/X11R6/lib -L/usr/local/lib
LDOSG = -losg -losgViewer -losgSim -losgGA
COBJS=$(patsubst %.cpp,%.o,$(CSRCS))

CC = g++

EXE=$(patsubst %.cpp,%,$(CSRCS))

all: $(EXE)

$(EXE): % : %.o
	g++ -o $@ $< $(INCLUDE) $(INCOSG) $(LDFLAGS) $(LDLIBS) $(LDOSG)


$(COBJS): %.o : %.cpp 
	$(CC) $(INCOSG) $(CFLAGS) -o $@ $< 

clean: 
	rm $(COBJS) $(EXE