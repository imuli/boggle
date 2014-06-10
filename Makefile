
boggle: main.o random.o board.o
	gcc -o boggle $^

%.o: %.c boggle.h
	gcc -g -c -o $@ $<

clean:
	rm *.o boggle
