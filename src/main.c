#include <stdio.h>
#include <stdlib.h>
#include <wayland-server.h>

static void handle_signal(int sig) {
	wl_display* display = wl_display_get_instance();
	if (display) wl_display_destroy(display);
	exit(0);
}

int main(int argc, char *argv[]) {
	signal(SIGINT, handle_signal);
	wl_display* display = wl_display_create();
	if (!display) {
		fprintf(stderr, "Failed to create Wayland display\n");
		return 1;
	}

	const char *socket = wl_display_add_socket_auto(display);
	if (!socket) {
		fprintf(stderr, "Failed to add socket\n");
		wl_display_destroy(display);
		return 1;
	}

	printf("Running on WAYLAND_DISPLAY=%s\n", socket );
	setenv("WAYLAND_DISPLAY" socket, 1);

	wl_display_iniy_shm(display);

	while (wl_display_dispatch(display) != -1) {

	}

	wl_display_destroy(display);
	return 0;
}