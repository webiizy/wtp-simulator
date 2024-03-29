/*
 *  USB LED driver for the NETGEAR WNDR3700
 *
 *  Copyright (C) 2009 Gabor Juhos <juhosg@openwrt.org>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */

#include <linux/leds.h>
#include <linux/module.h>
#include <linux/platform_device.h>

#include <asm/mach-ar71xx/ar71xx.h>

#define DRIVER_NAME	"wndr3700-led-usb"

static void wndr3700_usb_led_set(struct led_classdev *cdev,
				 enum led_brightness brightness)
{
	if (brightness)
		ar71xx_device_start(RESET_MODULE_GE1_PHY);
	else
		ar71xx_device_stop(RESET_MODULE_GE1_PHY);
}

static enum led_brightness wndr3700_usb_led_get(struct led_classdev *cdev)
{
	return ar71xx_device_stopped(RESET_MODULE_GE1_PHY) ? LED_OFF : LED_FULL;
}

static struct led_classdev wndr3700_usb_led = {
	.name = "wndr3700:green:usb",
	.brightness_set = wndr3700_usb_led_set,
	.brightness_get = wndr3700_usb_led_get,
};

static int __devinit wndr3700_usb_led_probe(struct platform_device *pdev)
{
	return led_classdev_register(&pdev->dev, &wndr3700_usb_led);
}

static int __devexit wndr3700_usb_led_remove(struct platform_device *pdev)
{
	led_classdev_unregister(&wndr3700_usb_led);
	return 0;
}

static struct platform_driver wndr3700_usb_led_driver = {
	.probe = wndr3700_usb_led_probe,
	.remove = __devexit_p(wndr3700_usb_led_remove),
	.driver = {
		.name = DRIVER_NAME,
		.owner = THIS_MODULE,
	},
};

static int __init wndr3700_usb_led_init(void)
{
	return platform_driver_register(&wndr3700_usb_led_driver);
}

static void __exit wndr3700_usb_led_exit(void)
{
	platform_driver_unregister(&wndr3700_usb_led_driver);
}

module_init(wndr3700_usb_led_init);
module_exit(wndr3700_usb_led_exit);

MODULE_DESCRIPTION("USB LED driver for the NETGEAR WNDR3700");
MODULE_AUTHOR("Gabor Juhos <juhosg@openwrt.org>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRIVER_NAME);
