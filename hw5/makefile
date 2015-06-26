all:read write
cc=gcc 
CFLAGS=-g -Wall -ansi
read_obj=read.o
write_obj=write.o
read:$(read_obj)
	$(cc)-o$@ $(read_obj)
write:$(write_obj)
		$(cc)-o$@ $(write_obj)
dep: $(read_obj:.o=.c) $(write_obj:.o=.c)
	$(cc) -MM $^ > depend
%.c:%.o
	$(cc)$(CFLAGS)-c-o$@ $<
clean:
	rm *.o
