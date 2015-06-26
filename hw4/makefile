all:test
cc=gcc 
CFLAGS=-g -Wall -ansi
test_obj=mm.o test.o
test:$(test_obj)
	$(cc)-o$@ $(test_obj)
dep: $(test_obj:.o=.c)
	$(cc) -MM $^ > depend
%.c:%.o
	$(cc)$(CFLAGS)-c-o$@ $<
clean:
	rm *.o
