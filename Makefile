CC = gcc

TARGET = SM_shell
HEADER = my_header
OBJECTS = my_help.o my_ls.o

$(TARGET) : $(TARGET).o $(OBJECTS)
	$(CC) -o $(TARGET) $(TARGET).o $(OBJECTS)

$(TARGET).o : $(HEADER).h $(TARGET).c
	$(CC) -c -o $@ $(TARGET).c

my_help.o : my_help.c
	$(CC) -c -o $@ $^

my_ls.o : my_ls.c
	$(CC) -c -o $@ $^

clean : 
	rm -rf $(TARGET) $(TARGET).o
	rm -rf $(OBJECTS)
