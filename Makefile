CC = gcc
CFLAGS = $(shell pkg-config --cflags wayland-server) -O2 -Wall
LDFLAGS = $(shell pkg-config --libs wayland-server)

SRC = src/main.c
OUT = customwm

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC) $(LDFLAGS)

clean:
	rm -f $(OUT)
