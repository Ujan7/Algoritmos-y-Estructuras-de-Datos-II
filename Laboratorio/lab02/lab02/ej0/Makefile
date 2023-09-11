CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -g

TARGET = myprogram
SRCS = main.c fixstring.c
OBJS = $(SRCS:.c=.o)
HDRS = fixstring.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

target:
	@echo "The current target is: $(TARGET)"

sources:
	@echo "The current source files are: $(SRCS)"

headers:
	@echo "The current header files are: $(HDRS)"
