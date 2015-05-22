//
//  arm_usb.c
//
//  Created by Rod Schmidt on 5/21/15.
//
//

#include "arm_usb.h"
#include <libusb-1.0/libusb.h>
#include "erl_comm.h"

#define ARM_VENDOR		0x1267
#define ARM_PRODUCT	0
#define CMD_DATALEN	3

static libusb_device * find_arm(libusb_device **devs)
{
	libusb_device *dev;
	int i = 0;

	while ((dev = devs[i++]) != NULL) {
		struct libusb_device_descriptor desc;
		if (libusb_get_device_descriptor(dev, &desc) < 0) {
			fprintf(stderr, "failed to get device descriptor");
			return NULL;
		}

		if (desc.idVendor == ARM_VENDOR && desc.idProduct == ARM_PRODUCT) {
			return dev;
		}
	}

	return NULL;
}

void process_command(byte *buf, int bytes_read)
{
	if (bytes_read != 3) {
		exit(1);
	}

	int status = libusb_init(NULL);
	if (status < 0) {
		fprintf(stderr, "failed to initialize libusb\n");
		return;
	}

	libusb_set_debug(NULL, 2);

	libusb_device **devs;
	ssize_t cnt = libusb_get_device_list(NULL, &devs);
	if (cnt < 0) {
		return;
	}

	libusb_device *dev = find_arm(devs);
	if (!dev) {
		fprintf(stderr, "Robot Arm not found\n");
		return;
	}

	struct libusb_device_handle *devh = NULL;
	status = libusb_open(dev,&devh);
	if (status != 0) {
		fprintf(stderr, "Error opening device\n");
		libusb_free_device_list(devs, 1);
		libusb_exit(NULL);
		return;
	}

	unsigned char cmd[] = {buf[0], buf[1], buf[2]};

	// fprintf(stderr, "Sending %02X %02X %02X\n",
	// 		(int)cmd[0], (int)cmd[1], (int)cmd[2]);

	int bytesTransferred = libusb_control_transfer(devh,
								 0x40, 		// uint8_t bmRequestType,
								 6, 		// uint8_t bRequest,
								 0x100, 	// uint16_t wValue,
								 0,			// uint16_t wIndex,
								 cmd,
								 CMD_DATALEN,
								 0
								 );

	if (bytesTransferred < 0) {
		fprintf(stderr, "Write err %d.\n", bytesTransferred);
	}
	else if (bytesTransferred < CMD_DATALEN) {
		fprintf(stderr, "Only wrote %d bytes\n", bytesTransferred);
	}

	libusb_close(devh);
	libusb_free_device_list(devs, 1);
	libusb_exit(NULL);
}

int main(int ac, char **av)
{
	while (1) {
		if (input_available() > 0) {
			byte buf[100];
			int bytes_read = read_cmd(buf);
			process_command(buf, bytes_read);
		}
	}

	return 0;
}
