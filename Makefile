all: compile run 

compile:
	g++ -g main.cpp ./source_files/*.cpp -o main.out -lsfml-graphics -lsfml-window -lsfml-system 

run: 
	./main.out

clean: 
	rm ./main.out

showFilePersmission:
	ls -l main.out

setExecutable:
	chmod +x ./main.out
