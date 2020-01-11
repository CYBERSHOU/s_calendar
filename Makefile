CC = gcc
CCF = -Wall

MAIN = calendar_main
FILE = calendar

.PHONY: clean debug debug_clean debug_make

all: files
	$(CC) $(CCF) $(FILE).o $(MAIN).o -o $(MAIN)

run: all
	./$(MAIN)

files:
	$(CC) -c $(FILE).c $(MAIN).c $(CCF)

clean:
	rm -vf *.o $(MAIN)

#Debug


#EOF
