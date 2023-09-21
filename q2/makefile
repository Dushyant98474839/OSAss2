all: p1 p2 p3 main run graph graph2

main: main.c
	gcc main.c -o main
	

p1: p1.c
	gcc p1.c -o p1

p2: p2.c
	gcc p2.c -o p2

p3: p3.c
	gcc p3.c -o p3

run: main
	 ./main

graph:
	python3 graph.py
graph2:
	python3 graph_bar.py