CC := gcc
CFLAGS := -g -Wall -Werror

#we only need to make the executable
all:  splooshkaboom run

#make it from these files

splooshkaboom: src/main.o src/logic.o
	$(CC) -o $@ $^ 
	

#pattern match all .o files
src/%.o: src/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

#run the file
run: 
	./splooshkaboom

#clean everything

clean:
	rm -f splooshkaboom
	rm -f src/*.o