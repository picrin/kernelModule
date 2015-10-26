obj-m+=iva.o
all:
	make -C /lib/modules/4.2.3-200.fc22.x86_64/build/ M=$(PWD) modules
clean:
	make -C /lib/modules/4.2.3-200.fc22.x86_64/build/ M=$(PWD) clean
	
