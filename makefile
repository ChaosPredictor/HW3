CC = gcc
OBJS = system.o common.o escaper.o company.o room.o order.o faculty.o
EXEC = mtm_escap
DEBUG_FLAG = -g -DNDEBUG
COMP_FLAG = -std=c99 -Wall -pedantic-errors -Werror -L -lmtm

$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) libmtm.a -o $@

system.o: system.c system.h escaper.h set.h common.h mtm_ex3.h faculty.h list.h company.h room.h order.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

company.o: company.c company.h set.h common.h mtm_ex3.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

escaper.o: escaper.c escaper.h set.h common.h mtm_ex3.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
	
room.o: room.c room.h set.h mtm_ex3.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
	
order.o: order.c order.h list.h common.h mtm_ex3.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
	
faculty.o: faculty.c faculty.h list.h mtm_ex3.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
	
common.o: common.c common.h mtm_ex3.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

clean:
	rm -f $(OBJS) $(EXEC)
