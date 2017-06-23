test.exe: test.o graph.o visual.o networkflow.o costflow.o
	g++ test.o graph.o visual.o networkflow.o costflow.o -o test.exe -g
test.o: test.cpp graph.h networkflow.h costflow.h graph.h
	g++ -c test.cpp -o test.o
graph.o: graph.cpp graph.h
	g++ -c graph.cpp -o graph.o
visual.o: visual.cpp visual.h graph.h
	g++ -c visual.cpp -o visual.o -g
networkflow: networkflow.cpp networkflow.h graph.h
	g++ -c networkflow.cpp -o networkflow.o
costflow: costflow.cpp costflow.h graph.h
	g++ -c costflow.cpp -o costflow.o
clear:
	del *.o *.exe
