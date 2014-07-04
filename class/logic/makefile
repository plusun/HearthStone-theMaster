OBJECT = deck.o test.o

test: $(OBJECT)
	gcc -o test $(OBJECT)
deck.o: deck.cpp deck.h
	gcc -c deck.cpp
player.o: player.cpp player.h
	gcc -c player.cpp
test.o: test.cpp
	gcc -c test.cpp
.PHONY: clean
clean:
	rm *.o
