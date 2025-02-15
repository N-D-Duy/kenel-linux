#include <errno.h>
#include <fcntl.h>
#include <libinput.h>
#include <libudev.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wayland-client.h>
#include <wayland-server.h>

struct libinput *li;
double current_x = 0;
double current_y = 0;
static int open_restricted(const char *path, int flags, void *user_data) {
  int fd = open(path, flags);
  return fd < 0 ? -errno : fd;
}

static void close_restricted(int fd, void *user_data) { close(fd); }

const struct libinput_interface interface = {
    .open_restricted = open_restricted,
    .close_restricted = close_restricted,
};

int main() {
  struct udev *udev = udev_new();
  if (!udev) {
    fprintf(stderr, "Failed to initialize udev\n");
    return 1;
  }

  li = libinput_udev_create_context(&interface, NULL, udev);
  if (!li) {
    fprintf(stderr, "Failed to initialize libinput\n");
    udev_unref(udev);
    return 1;
  }

  if (libinput_udev_assign_seat(li, "seat0") != 0) {
    fprintf(stderr, "Failed to assign seat\n");
    libinput_unref(li);
    udev_unref(udev);
    return 1;
  }

  printf("Đang theo dõi tọa độ chuột. Nhấn Ctrl+C để dừng.\n");
  printf("----------------------------------------\n");

  while (1) {
    libinput_dispatch(li);
    struct libinput_event *event;
    while ((event = libinput_get_event(li)) != NULL) {
      enum libinput_event_type type = libinput_event_get_type(event);

      if (type == LIBINPUT_EVENT_POINTER_MOTION) {
        struct libinput_event_pointer *pointer_event =
            libinput_event_get_pointer_event(event);

        double dx = libinput_event_pointer_get_dx(pointer_event);
        double dy = libinput_event_pointer_get_dy(pointer_event);

        current_x += dx;
        current_y += dy;

        printf("\rX: %.2f / Y: %.2f", current_x, current_y);
        fflush(stdout);
      } else if (type == LIBINPUT_EVENT_POINTER_MOTION_ABSOLUTE) {
        struct libinput_event_pointer *pointer_event =
            libinput_event_get_pointer_event(event);

        current_x = libinput_event_pointer_get_absolute_x_transformed(
            pointer_event, 1920);
        current_y = libinput_event_pointer_get_absolute_y_transformed(
            pointer_event, 1080);

        printf("\rX: %.2f / Y: %.2f", current_x, current_y);
        fflush(stdout);
      }

      libinput_event_destroy(event);
    }
  }

  libinput_unref(li);
  udev_unref(udev);
  return 0;
}
