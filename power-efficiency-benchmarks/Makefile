INCLUDE_DIRS = 
LIB_DIRS = 
CC=gcc
CPP=g++

CDEFS=
CFLAGS= -O0 -g -fopenmp $(INCLUDE_DIRS) $(CDEFS)
LIBS= -lrt -lpthread
CPPLIBS= -L/usr/lib -lopencv_core -lopencv_flann -lopencv_video

HFILES= 
CFILES= 
CPPFILES= canny.cpp hough_circle.cpp hough_line.cpp pyrimage.cpp sobel.cpp

SRCS= ${HFILES} ${CFILES}
CPPOBJS= ${CPPFILES:.cpp=.o}

all:	canny hough_circle hough_line pyrimage sobel sharpen_grid sharpen hello_omp

clean:
	-rm -f *.o *.d
	-rm -f canny hough_circle hough_line pyrimage sobel sharpen_grid sharpen hello_omp

distclean:
	-rm -f *.o *.d

hello_omp: hello_omp.o
	$(CC) $(LDFLAGS) $(CFLAGS) -fopenmp -o $@ $@.o $(LIBS)

sharpen: sharpen.o
	$(CC) $(LDFLAGS) $(CFLAGS) -fopenmp -o $@ $@.o $(LIBS)

sharpen_grid: sharpen_grid.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $@.o $(LIBS)

canny: canny.o
	$(CPP) $(LDFLAGS) $(CFLAGS) -o $@ $@.o `pkg-config --libs opencv` $(CPPLIBS)

hough_circle: hough_circle.o
	$(CPP) $(LDFLAGS) $(CFLAGS) -o $@ $@.o `pkg-config --libs opencv` $(CPPLIBS)

hough_line: hough_line.o
	$(CPP) $(LDFLAGS) $(CFLAGS) -o $@ $@.o `pkg-config --libs opencv` $(CPPLIBS)

pyrimage: pyrimage.o
	$(CPP) $(LDFLAGS) $(CFLAGS) -o $@ $@.o `pkg-config --libs opencv` $(CPPLIBS)

sobel: sobel.o
	$(CPP) $(LDFLAGS) $(CFLAGS) -o $@ $@.o `pkg-config --libs opencv` $(CPPLIBS)

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<

.cpp.o:
	$(CPP) $(CFLAGS) -c $<
