# builds the watershed executable
all: watershed

watershed: watershed.o pointcloud.o util.o bmp.o
	gcc -g -o watershed watershed.o pointcloud.o util.o bmp.o

watershed.o: watershed.c pointcloud.h util.h
	gcc -g -c watershed.c

display: display.o pointcloud.o util.o bmp.o
	gcc -g -o display display.o pointcloud.o util.o bmp.o

display.o: display.c pointcloud.h util.h
	gcc -g -c display.c

pointcloud.o: pointcloud.c pointcloud.h util.h bmp.h
	gcc -g -c pointcloud.c

util.o: util.c util.h
	gcc -g -c util.c

bmp.o: bmp.c bmp.h
	gcc -g -c bmp.c

clean:
	rm -f *.o watershed display out.gif *.gif
