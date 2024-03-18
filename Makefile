CC = g++
CFLAGS = -I ./inc -std=c++17

.PHONY: all
all: uiComponents librarySystem

# create executable
librarySystem: item.o book.o library.o person.o main.o mainwindow.o
	@$(CC) $^ -o $@
	@echo "building is done"

# object creation recipes
%.o: ./src/%.cpp ./inc/%.hpp
	@$(CC) -c $< $(CFLAGS)

# ui component headers
uiComponents: ./ui/%.ui
	@uic $< -o ./inc/ui_%.hpp

.PHONY: clean
clean:
	rm *.o librarySystem

# $@ is for output file
# $< is for the very first dependency
# $^ is for all dependencies