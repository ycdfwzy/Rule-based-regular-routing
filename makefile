test.exe: test.o graph.o visual.o networkflow.o costflow.o
	g++ test.o graph.o visual.o networkflow.o costflow.o -o test.exe -O2
test.o: test.cpp graph.h networkflow.h costflow.h graph.h
	g++ -c test.cpp -o test.o -O2
graph.o: graph.cpp graph.h
	g++ -c graph.cpp -o graph.o -O2
visual.o: visual.cpp visual.h graph.h
	g++ -c visual.cpp -o visual.o -O2
networkflow: networkflow.cpp networkflow.h graph.h
	g++ -c networkflow.cpp -o networkflow.o -O2
costflow: costflow.cpp costflow.h graph.h
	g++ -c costflow.cpp -o costflow.o -O2
clear:
	del *.o *.exe
