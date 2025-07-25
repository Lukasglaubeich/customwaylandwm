CC = gcc
CFLAGS = `pkg-config --cflags wayland-server` -02 -Wall
LDFLAGS = `pkg-config --libs wayland-server`

SRC = src/main.c
OUT = customwm

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC) $(LDFLAGS)


clean:
	rm -rf $(OUT)