CC = gcc

TARGET = SM_sh
HEADER = my_header
HELP = my_help

$(TARGET) : $(TARGET).o $(HELP).o
	$(CC) -o $(TARGET) $(TARGET).o $(HELP).o

$(TARGET).o : $(HEADER).h $(TARGET).c
	$(CC) -c -o $@ $(TARGET).c

$(HELP).o : $(HELP).c
	$(CC) -c -o $@ $(HELP).c

clean : 
	rm -rf $(TARGET)
	rm -rf *.o
