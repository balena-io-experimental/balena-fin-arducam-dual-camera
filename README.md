# balena-fin-arducam-dual-camera
simple application for testing 2 arducam MIPI modules connected to dual-camera enabled balenaFin

## Requirements

balenaFin dual camera mode [enabled](https://www.balena.io/fin/1.1/docs/developers/#Dual-camera-mode)

## Configuration variables

* __RESIN_HOST_CONFIG_gpu_mem__ = `396` _this covers the most demanding 16MP scenario, can be lowered all the way down to 64 based on the camera and resolution you are targeting.  A good middleground would be `144` )_
* __BALENA_HOST_CONFIG_dtparam__ = `"i2c_vc=on"` _instructs the VideoCore to leave i2c-0 to ARM (therefore userspace). Make also sure the_ `Define DT parameters` _option is NOT active_
* __BALENA_HOST_CONFIG_start_x__ = `1` _required to enable camera access_

## Usage

Everytime the `arducam` service is started it snaps a picture from both camera interfaces and saves them in a shared volume the `webserver` service exposes via a static file web server. Simply point to the device Ip address or enable publicURL to brows the pictures taken. To snap again, restart the `arducam` service.
