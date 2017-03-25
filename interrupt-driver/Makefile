
CFLAGS = -Wall -O -g -I.. 

ifneq ($(KERNELRELEASE),) # kernel build system
obj-m	:= short.o

else

PWD 	:= $(shell pwd)
KERNELDIR ?= $(PWD)/linux-2-6-10/build # untracked directory with linux kernel 2.6.10

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

endif

clean:
	rm -rf *.o *~


