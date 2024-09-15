# ./stat 
stat: pointcloud.o
	gcc pointcloud.o -o stat   

# Builds pointcloud.o
pointcloud.o: pointcloud.c pointcloud.h
	gcc -c pointcloud.c        

# Make clean 
clean:
	rm -f *.o stat             
