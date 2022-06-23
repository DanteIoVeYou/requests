CC=g++
FLAG=-std=c++11
SRC=unittest.cpp
req:$(SRC)
	$(CC) -o $@ $^ $(FLAG)
.PHONY:clean 
clean:
	rm -f req 
