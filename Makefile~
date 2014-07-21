FLAGS=-g


ic: teste1.o EasyBMP.o
	g++ $(FLAGS) -o ic teste1.o EasyBMP.o

teste1.o: teste1.cpp
	g++ $(FLAGS) -c teste1.cpp

EasyBMP.o: EasyBMP_BMP.h EasyBMP.cpp EasyBMP_DataStructures.h EasyBMP.h EasyBMP_VariousBMPutilities.h
	g++ $(FLAGS) -c EasyBMP.cpp


