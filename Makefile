CC := gcc
CFLAGS := -g -Wall -Werror

#we only need to make the executable
all:  splooshkaboom

#make it from these files
splooshkaboom: main.o logic.o

#pattern match all .o files
%.o: src/%.c
	$(CC) -o $@ -c $< $(CFLAGS)