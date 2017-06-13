CC = gcc
OBJS =  mtm_escape.o system.o common.o escaper.o company.o room.o order.o \
faculty.o
OBJS_TEST =  mtm_escape_tests.o common_test.o faculty_test.o company_test.o \
room_test.o escaper_test.o order_test.o system_test.o system.o common.o \
escaper.o company.o room.o order.o faculty.o
OBJS_LIST_TEST = list_mtm1_test.o list_mtm1.o
EXEC = mtm_escape
DEBUG_FLAG = -g -DNDEBUG
COMP_FLAG = -std=c99 -Wall -pedantic-errors -Werror -L -lmtm

$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) libmtm.a -o $@

mtm_escape.o: mtm_escape.c mtm_escape.h common.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

system.o: system.c system.h escaper.h set.h common.h mtm_ex3.h faculty.h \
list.h company.h room.h order.h
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

mtm_escape_tests: $(OBJS_TEST) 
	$(CC) $(DEBUG_FLAG) $(OBJS_TEST) libmtm.a -o $@

common_test.o: ./tests/common_test.c ./tests/common_test.h order.c
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) ./tests/common_test.c

faculty_test.o: ./tests/faculty_test.c ./tests/faculty_test.h faculty.c
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) ./tests/faculty_test.c	

company_test.o: ./tests/company_test.c ./tests/company_test.h company.c
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) ./tests/company_test.c

room_test.o: ./tests/room_test.c ./tests/room_test.h room.c
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) ./tests/room_test.c

escaper_test.o: ./tests/escaper_test.c ./tests/escaper_test.h escaper.c
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) ./tests/escaper_test.c

order_test.o: ./tests/order_test.c ./tests/order_test.h order.c
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) ./tests/order_test.c

system_test.o: ./tests/system_test.c ./tests/system_test.h system.c
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) ./tests/system_test.c

list_test: $(OBJS_LIST_TEST)
	$(CC) $(DEBUG_FLAG) $(OBJS_LIST_TEST) libmtm.a -o $@

list_mtm1_test.o: ./tests/list_mtm1_test.c
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) ./tests/list_mtm1_test.c 

list_mtm1.o: ./list_mtm/list_mtm1.c ./list_mtm/list_mtm1.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) ./list_mtm/list_mtm1.c

clean:
	rm -f $(OBJS) $(EXEC)
