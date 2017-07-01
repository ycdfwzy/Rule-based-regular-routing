test.exe: test.o graph.o visual.o networkflow.o maxflow.o costflow.o greedy.o
	g++ test.o graph.o visual.o networkflow.o maxflow.o costflow.o greedy.o -o test.exe -O2
test.o: test.cpp graph.h costflow.h graph.h
	g++ -c test.cpp -o test.o -O2
graph.o: graph.cpp graph.h
	g++ -c graph.cpp -o graph.o -O2
visual.o: visual.cpp visual.h graph.h
	g++ -c visual.cpp -o visual.o -O2
networkflow.o: networkflow.cpp networkflow.h graph.h
	g++ -c networkflow.cpp -o networkflow.o -O2
maxflow.o: maxflow.cpp maxflow.h graph.h
	g++ -c maxflow.cpp -o maxflow.o -O2
costflow.o: costflow.cpp costflow.h graph.h
	g++ -c costflow.cpp -o costflow.o -O2
greedy.o: greedy.cpp greedy.h
	g++ -c greedy.cpp -o greedy.o -O2
clear:
	del *.o *.exe
