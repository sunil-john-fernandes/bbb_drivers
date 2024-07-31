CC = $(CROSS_COMPILE)gcc

obj-m += hello_world.o
KDIR := /home/sunil/buildroot-2024.02.4/output/build/linux-custom/

all:
	$(MAKE) -C $(KDIR) M=$(PWD)

clean:
	-rm -f *.o
	-rm *.order
	-rm *.symvers
	-rm *.mod
	-rm *.mod.c
	-rm *.ko

