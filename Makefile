
all = gtqalc

CC = gcc

CFLAGS = -Wall			 	\
	-DG_DISABLE_DEPRECATED 	 	\
	-DGDK_DISABLE_DEPRECATED 	\
	-DGDK_PIXBUF_DISABLE_DEPRECATED \
	-DGTK_DISABLE_DEPRECATED	\

CFLAGS += $(shell pkg-config gtk+-2.0 --cflags)
LIBS = $(shell pkg-config gtk+-2.0 --libs)

OBJS = box.o gtqalc.o

.o:
	$(CC) $(CFLAGS) -c $< -o $@

gtqalc: $(OBJS)
	$(CC) $(LIBS) $(OBJS) -o $@

clean: 
	rm -f *.o gtqalc

