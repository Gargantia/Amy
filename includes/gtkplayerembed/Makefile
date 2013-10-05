SRCS=gtkplayer.c gtkplayertester.c
OBJS=gtkplayer.o gtkplayertester.o
CFLAGS= -g -I. `pkg-config --libs --cflags gtk+-2.0`
LDFLAGS= `pkg-config --libs --cflags gtk+-2.0`

all: clean gtkplayertester
$(OBJS):
	$(CC) -c $(SRCS) $(CFLAGS)
gtkplayertester: $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)
clean:
	if [ -f gtkplayertester ]; then rm gtkplayertester; fi;\
	touch dumb.o; rm *o;
