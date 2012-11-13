CC = g++
#CFLAGS = -Wextra -std=c++98 -pedantic -pedantic-errors -O0 -g
CFLAGS = -Wall -Wextra -std=c++98 -pedantic -pedantic-errors -O0 -g
LDFLAGS = -lm
SRC = tests Driver ArbolCategorias LinkLinkIt
OBJ = $(SRC:=.o)
EXE = linklinkit
TEST = testDiccTrie #testArbolCategorias testLinkLinkIt
#TEST := test/${TEST}
TEST := $(sort $(TEST))
TESTP = $(addprefix test/,$(TEST)) 


.phony: all clean

all: $(EXE) runTests

$(EXE): $(OBJ) 
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o $@

%.o: %.cpp %.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

tests.o: tests.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@	

test/testDiccTrie: test/testDiccTrie.cpp DiccTrie.h test/test.o
	$(CC) $(CFLAGS) $(LDFLAGS) test/testDiccTrie.cpp test/test.o -o $@

#-------------
#test/testFecha: test/testFecha.cpp Fecha.o test/test.o
#	$(CC) $(CFLAGS) $(LDFLAGS) test/testFecha.cpp Fecha.o test/test.o -o $@

#test/testMensaje: test/testMensaje.cpp Mensaje.o Fecha.o test/test.o
#	$(CC) $(CFLAGS) $(LDFLAGS) test/testMensaje.cpp Mensaje.o Fecha.o test/test.o -o $@

#test/testReglas: test/testReglas.cpp Reglas.o test/test.o
#	$(CC) $(CFLAGS) $(LDFLAGS) test/testReglas.cpp Reglas.o test/test.o -o $@

#test/testRedSocial: test/testRedSocial.cpp Reglas.o RedSocial.o Mensaje.o Fecha.o ListaOrd.o test/test.o
#	$(CC) $(CFLAGS) $(LDFLAGS) test/testRedSocial.cpp Reglas.o RedSocial.o Mensaje.o Fecha.o ListaOrd.o test/test.o -o $@

#-------------

#$(TEST): $(TEST).cpp DiccTrie.h test/test.o
#	$(CC) $(CFLAGS) $(LDFLAGS) $(TEST).cpp test/test.o -o $@

test.o: test/test.cpp test/test.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o test/$@

runTests: $(TESTP)
	@test/testDiccTrie
#	@test/testArbolCategorias
#	@test/testLinkLinkIt

clean:
	rm -f *.o 
	rm -f test/*.o
	rm -f $(EXE)
	rm -f $(TESTP)
