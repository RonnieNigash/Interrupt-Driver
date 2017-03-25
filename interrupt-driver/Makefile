
CFLAGS = -O -g -I..

ifneq ($(KERNELRELEASE),) # kernel build system
obj-m	:= short.o

else

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD 	:= $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

endif

clean:
	rm -rf *.o *~


