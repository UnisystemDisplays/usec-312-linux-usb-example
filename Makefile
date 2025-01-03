CFLAGS  = -g -Wall -Wextra -Wno-unused-function -Wno-unused-parameter
LDFLAGS = -lm

usec-312-linux-usb-example:
	$(CC) -o usec-312-linux-usb-example main.c usec_dev.c $(CFLAGS) $(LDFLAGS)

clean:
	rm -f usec-312-linux-usb-example *.o *~
