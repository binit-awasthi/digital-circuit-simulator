all: compile run 

compile:
	g++ -g -Wall main.cpp ./source_files/*.cpp -o simulator -I/path_to_include_directory -L/path_to_bin -lsfml-graphics -lsfml-window -lsfml-system 

run: 
	./simulator

clean: 
	rm ./simulator

showFilePersmission:
	ls -l simulator

setExecutable:
	chmod +x ./simulator
