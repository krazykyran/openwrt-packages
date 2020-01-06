#
# Makefile for the kernel serial device drivers.
#

ccflags-$(CONFIG_GPIOLIB)					+= -DCONFIG_GPIOLIB
ccflags-$(CONFIG_SERIAL_SC16IS7XX_SPI)		+= -DCONFIG_SERIAL_SC16IS7XX_SPI
ccflags-$(CONFIG_SERIAL_SC16IS7XX_I2C)		+= -DCONFIG_SERIAL_SC16IS7XX_I2C

obj-$(CONFIG_SERIAL_CORE)					+= serial_core.o
obj-$(CONFIG_SERIAL_SC16IS7XX_CORE)			+= sc16is7xx.o
