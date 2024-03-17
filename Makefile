
# create executable
librarySystem: allObjs
	g++ *.o -o librarySystem

# object creation recipes
item.o: ./src/item.cpp ./inc/item.hpp
	g++ -c ./src/item.cpp -I ./inc
book.o: ./src/book.cpp ./inc/book.hpp
	g++ -c ./src/book.cpp -I ./inc
library.o: ./src/library.cpp ./inc/library.hpp
	g++ -c ./src/library.cpp -I ./inc
person.o: ./src/person.cpp ./inc/person.hpp
	g++ -c ./src/person.cpp -I ./inc
main.o: ./src/main.cpp ./inc/main.hpp
	g++ -c ./src/main.cpp -I ./inc

# creates all objects
allObjs: item.o book.o library.o person.o main.o

clean:
	rm *.o librarySystem
