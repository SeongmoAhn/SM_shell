CC = gcc

TARGET = SM_shell
HEADER = my_header
OBJECTS = my_help.o

$(TARGET) : $(TARGET).o $(OBJECTS)
	$(CC) -o $(TARGET) $(TARGET).o $(OBJECTS)

$(TARGET).o : $(HEADER).h $(TARGET).c
	$(CC) -c -o $@ $(TARGET).c

my_help.o : my_help.c
	$(CC) -c -o $@ $^

clean : 
	rm -rf $(TARGET)
	rm -rf $(OBJECTS)
