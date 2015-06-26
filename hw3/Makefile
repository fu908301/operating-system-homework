all:main
cc=g++ 
CFLAGS=-g -Wall -ansi -pthread
main_obj=main.o
main:$(main_obj)
	$(cc) $(CFLAGS) -o $@ $(main_obj)
dep: $(main_obj:.o=.cpp)
	$(cc) -MM $^ > depend
%.c:%.o
	$(cc)$(CFLAGS)-c-o$@ $<
clean:
	rm *.o
