CC = gcc
CFAGS = -lstdc++
%: %.cc
	$(CC) -o $@ $< -lstdc++ -std=c++17 -fsanitize=undefined,address
clean: 
	rm -f *.o
