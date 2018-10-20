CC = cc
YFLAGS = -d
OBJS = vapor.o code.o init.o symbol.o
TOBJS = vtoc ctov

vapor:	$(OBJS) $(TOBJS)
		$(CC) $(OBJS) -lm -o vapor

vapor.o code.o init.o symbol.o:	vapor.h

code.o init.o symbol.o:	vapor.h y.tab.h

clean:
	rm -f $(OBJS) y.tab.[ch]
