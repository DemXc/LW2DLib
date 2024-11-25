TARGET = lw2d_program
SRCS = src/lw2d.c src/main.c
CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lglfw -lGL -lm
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

src/%.o: src/%.c src/lw2d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)
