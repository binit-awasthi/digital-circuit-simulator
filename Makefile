all: compile run 

compile:
	g++ -g -Wall main.cpp ./source_files/*.cpp -o simulator.out -lsfml-graphics -lsfml-window -lsfml-system 

run: 
	./simulator.out

clean: 
	rm ./simulator.out

showFilePersmission:
	ls -l simulator.out

setExecutable:
	chmod +x ./simulator.out
