#!/usr/bin/env bash
umount /dev/shm && mount -t tmpfs shm /dev/shm
echo 44 > /sys/class/gpio/export || true
echo "out" > /sys/class/gpio/gpio44/direction
echo 1 > /sys/class/gpio/gpio44/value

while [[ true ]]; do
  ./MIPI_Camera/RPI/capture-dualcam && mv camera* /data
  sleep infinity
done
