main: fun.o
	g++ -O3 -o main main.cpp  
fun: 
	g++ -O3 -c fun.cpp
clean:
	rm*.o main