# This sample Makefile allows you to make an OpenGL application
#   whose source is exactly one .c file or one .cc file under Solaris.
#   check the location of the X libraries on your implementation.
#
# To use this Makefile, you type:
#
#        make xxxx
#                  
# where
#       xxxx.cc is the name of the c++-file you wish to compile 
#  or 
#       xxxx.c is the name of the c-file you wish to compile 
#       
# A binary named xxxx will be produced
# Libraries are assumed to be in the default search paths
# as are any required include files

#
# Modified by Prof. Chelberg to also allow you to make from a single
# c++ source file.  So if xxxx.cc is the sourcefile, you type make
# xxxx to produce the binary file.

# last-modified: Fri Oct 16 13:01:06 2015

# Assumes the following file exists in the proper place.
include /home/cs425/code-egs/Makefile.defs

# Next line says what options to use to compile programs
OPTIONS+=-Wall

animate: main.cc chair.o table.o Small_table.o room1.o room2.o
	$(CC) main.cc  $(InitShader) chair.o table.o Small_table.o room2.o room1.o $(OPTIONS) $(LDLIBS) -o cerebrate

chair.o: chair.h chair.cc
	$(CC) chair.cc -c $(OPTIONS)
	
table.o: table.h table.cc
	$(CC) table.cc -c $(OPTIONS)

Small_table.o: Small_table.h Small_table.cc
	$(CC) Small_table.cc -c $(OPTIONS)

room1.o: room1.cc room1.h
	$(CC) room1.cc -c $(OPTIONS)

room2.o: room2.cc room2.h
	$(CC) room2.cc -c $(OPTIONS)	
clean:
	rm cerebrate
	rm -f *.o