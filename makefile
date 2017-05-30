CC = gcc
OBJS = mtm_escape.c mtm_escape.h company.o room.o order.o mtm_ex3.h set.h
EXEC = mtm_escape
DEBUG_FLAG = -g -DNDEBUG
COMP_FLAG = -std=c99 -Wall -pedantic-errors -Werror -L -lmtm

#$(EXEC) : $(OBJS)
#				$(CC) $(DEBUG_FLAG) $(OBJS) -o $@
mtm_escape: company.o escaper.o order.o room.o 
	gcc -o mtm_escape -std=c99 -Wall -pedantic-errors -Werror -g -DNDEBUG *.c -L. -lmtm
#	mtm_escape.c mtm_escape.h company.h order.h mtm_ex3.h set.h libmtm.a

company.o: company.c company.h order.h mtm_ex3.h set.h mtm_escape.h
escaper.o: escaper.c escaper.h order.h mtm_ex3.h set.h mtm_escape.h company.h
order.o: order.c order.h mtm_ex3.h set.h
room.o: room.c room.h order.h mtm_ex3.h set.h company.h mtm_escape.h
