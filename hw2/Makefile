all:main
cc=gcc 
CFLAGS=-pthread
main_obj=main.o
main:$(main_obj)
	$(cc) $(CFLAGS) -o $@ $(main_obj)
dep: $(main_obj:.o=.c)
	$(cc) -MM $^ > depend
%.c:%.o
	$(cc)$(CFLAGS)-c-o$@ $<
clean:
	rm *.o
