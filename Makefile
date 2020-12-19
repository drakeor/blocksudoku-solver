IDIR =eigen/
CC=g++
CFLAGS=-I$(IDIR)
OBJ = main.o
ODIR=obj

%.o: %.cpp $(DEPS)
	$(CC) -c -o $(ODIR)/$@ $< $(CFLAGS)

bssolve: $(OBJ)
	mkdir -p $(ODIR)
	$(CC) -o $@ $(ODIR)/$^ $(CFLAGS)

clean:
	rm -rf $(ODIR)