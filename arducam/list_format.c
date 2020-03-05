#include "arducam_mipicamera.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define LOG(fmt, args...) fprintf(stderr, fmt "\n", ##args)

int main(int argc, char **argv) {
    CAMERA_INSTANCE camera_instance;
    struct camera_interface cam_interface = {
        .i2c_bus = 0,           // /dev/i2c-0  or /dev/i2c-1
        .camera_num = 0,        // mipi interface num
        .sda_pins = {28, 0},    // enable sda_pins[camera_num], disable sda_pins[camera_num ? 0 : 1]
        .scl_pins = {29, 1},    // enable scl_pins[camera_num], disable scl_pins[camera_num ? 0 : 1]
        .led_pins = {44, 44},
        .shutdown_pins ={45, 45},
    };
    int res = arducam_init_camera2(&camera_instance,cam_interface);
    if (res) {
        LOG("init camera status = %d", res);
        return -1;
    }
    struct format support_fmt;
    int index = 0;
    char fourcc[5];
    fourcc[4] = '\0';
    while (!arducam_get_support_formats(camera_instance, &support_fmt, index++)) {
        strncpy(fourcc, (char *)&support_fmt.pixelformat, 4);
        LOG("mode: %d, width: %d, height: %d, pixelformat: %s, desc: %s",
            support_fmt.mode, support_fmt.width, support_fmt.height, fourcc,
            support_fmt.description);
    }
    index = 0;
    struct camera_ctrl support_cam_ctrl;
    while (!arducam_get_support_controls(camera_instance, &support_cam_ctrl, index++)) {
        int value = 0;
        if (arducam_get_control(camera_instance, support_cam_ctrl.id, &value)) {
            LOG("Get ctrl %s fail.", support_cam_ctrl.desc);
        }
        LOG("index: %d, CID: 0x%08X, desc: %s, min: %d, max: %d, default: %d, current: %d",
            index - 1, support_cam_ctrl.id, support_cam_ctrl.desc, support_cam_ctrl.min_value,
            support_cam_ctrl.max_value, support_cam_ctrl.default_value, value);
    }
    res = arducam_close_camera(camera_instance);
    LOG("close camera status = %d", res);
    return 0;
}
