
boggle: main.o random.o board.o
	cc -o boggle $^

%.o: %.c boggle.h
	cc -g -c -o $@ $<

clean:
	rm *.o boggle
