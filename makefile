#CC = gcc
#OBJS = mtm_escape.c mtm_escape.h company.o room.o order.o mtm_ex3.h set.h
#EXEC = system
#DEBUG_FLAG = -g -DNDEBUG
#COMP_FLAG = -std=c99 -Wall -pedantic-errors -Werror -L -lmtm


mtm_escape: system.o  company.o escaper.o room.o order.o faculty.o common.o
	gcc system.o libmtm.a common.o escaper.o company.o room.o order.o faculty.o -o mtm_escape

system.o: system.c system.h escaper.h set.h common.h mtm_ex3.h faculty.h list.h company.h room.h order.h
	gcc -c system.c escaper.c company.c room.c  order.c  faculty.c common.c -L. -lmtm -std=c99 -Wall -pedantic-errors -Werror -g -DNDEBUG

company.o: company.c company.h set.h common.h mtm_ex3.h
	gcc -c company.c

escaper.o: escaper.c escaper.h set.h common.h mtm_ex3.h
	gcc -c escaper.c

room.o: room.c room.h set.h mtm_ex3.h
	gcc -c room.c

order.o: order.c order.h list.h common.h mtm_ex3.h
	gcc -c order.c

faculty.o: faculty.c faculty.h list.h mtm_ex3.h
	gcc -c faculty.c

common.o: common.c common.h mtm_ex3.h
	gcc -c common.c
