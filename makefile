test.exe: test.o graph.o networkflow.o costflow.o
	g++ test.o graph.o networkflow.o costflow.o -o test.exe
test.o: test.cpp graph.h networkflow.h costflow.h
	g++ -c test.cpp -o test.o
graph.o: graph.cpp graph.h
	g++ -c graph.cpp -o graph.o
networkflow: networkflow.cpp networkflow.h
	g++ -c networkflow.cpp -o networkflow.o
costflow: costflow.cpp costflow.h
	g++ -c costflow.cpp -o costflow.o
clear:
	del *.o *.exe
