CC := gcc
CFLAGS := -g -Wall -Werror
LDFLAGS := -lncurses

#we only need to make the executable
all:  splooshkaboom

#make it from these files

splooshkaboom: src/main.o src/logic.o
	$(CC) -o $@ $^ $(LDFLAGS)
	

#pattern match all .o files
src/%.o: src/%.c
	$(CC) -o $@ -c $< $(CFLAGS)


#clean everything

clean:
	rm -f splooshkaboom
	rm -f src/*.o