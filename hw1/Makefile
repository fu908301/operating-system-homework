all:main
cc=gcc 
CFLAGS=-g -Wall -ansi
main_obj=shell.o main.o
main:$(main_obj)
	$(cc)-o$@ $(main_obj)
dep: $(main_obj:.o=.c)
	$(cc) -MM $^ > depend
%.c:%.o
	$(cc)$(CFLAGS)-c-o$@ $<
clean:
	rm *.o
