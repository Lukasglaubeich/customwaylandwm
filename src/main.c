#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wayland-server.h>

static struct wl_display *display = NULL;

// bind handler for wl_compositor
static void bind_compositor(struct wl_client *client, void *data,
                            uint32_t version, uint32_t id) {
    struct wl_resource *res = wl_resource_create(client,
        &wl_compositor_interface, version, id);
    // no methods to implement yet
}

// bind handler for wl_shm
static void bind_shm(struct wl_client *client, void *data,
                     uint32_t version, uint32_t id) {
    struct wl_resource *res = wl_resource_create(client,
        &wl_shm_interface, version, id);
    // advertise only ARGB8888; add more formats if you care
    wl_shm_send_format(res, WL_SHM_FORMAT_ARGB8888);
}

static void handle_signal(int sig) {
    if (display) wl_display_destroy(display);
    exit(0);
}

int main(int argc, char *argv[]) {
    signal(SIGINT, handle_signal);

    display = wl_display_create();
    if (!display) {
        fprintf(stderr, "Failed to create display\n");
        return 1;
    }

    // export compositor and shm globals
    wl_global_create(display, &wl_compositor_interface, 4,
                     NULL, bind_compositor);
    wl_global_create(display, &wl_shm_interface, 1,
                     NULL, bind_shm);

    const char *sock = wl_display_add_socket_auto(display);
    if (!sock) {
        fprintf(stderr, "Failed to add socket\n");
        wl_display_destroy(display);
        return 1;
    }

    printf("WAYLAND_DISPLAY=%s  hit Ctrl+C to quit\n", sock);
    setenv("WAYLAND_DISPLAY", sock, 1);

    // this runs the dispatch loop internally
    wl_display_run(display);

    wl_display_destroy(display);
    return 0;
}
