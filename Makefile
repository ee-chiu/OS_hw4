para = hw4_1_1 hw4_1_2 hw4_2

all: 	${para}

hw4_1_1:	hw4_1_1.cpp
			g++ -o hw4_1_1 hw4_1_1.cpp -lpthread

hw4_1_2:	hw4_1_2.cpp
			g++ -o hw4_1_2 hw4_1_2.cpp -lpthread

hw4_2:		hw4_2.cpp
			g++ -o hw4_2 hw4_2.cpp -lpthread