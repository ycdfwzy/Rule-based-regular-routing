test.exe: test.o graph.o visual.o networkflow.o costflow.o greedy.o
	g++ test.o graph.o visual.o networkflow.o costflow.o greedy.o -o test.exe -g
test.o: test.cpp graph.h networkflow.h costflow.h graph.h
	g++ -c test.cpp -o test.o -g
graph.o: graph.cpp graph.h
	g++ -c graph.cpp -o graph.o -g
visual.o: visual.cpp visual.h graph.h
	g++ -c visual.cpp -o visual.o -g
networkflow.o: networkflow.cpp networkflow.h graph.h
	g++ -c networkflow.cpp -o networkflow.o -g
costflow.o: costflow.cpp costflow.h graph.h
	g++ -c costflow.cpp -o costflow.o -g
greedy.o: greedy.cpp greedy.h
	g++ -c greedy.cpp -o greedy.o -g
clear:
	del *.o *.exe
