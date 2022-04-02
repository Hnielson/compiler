NAME=simple-compiler

all: compiler

run: compiler
	./$(NAME).exe

compiler:
	g++ *.cpp -o $(NAME).exe

# log: logging run

# logging:
# 	g++ -g -D LOGGING *.cpp -o $(NAME).exe

# gdb:
# 	g++ -g *.cpp -o $(NAME).exe

clean:
	rm *.o *.exe