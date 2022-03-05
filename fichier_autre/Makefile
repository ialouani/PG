GNUCOMPILER=cc
#creation des 2 points o.
BIN=exec11
BIN2=exec22
all: test1 test2 test3 memory_check clean
memory_check: test1 test2
	valgrind --track-origins=yes ./exec11
	valgrind --track-origins=yes ./exec22
test1: build
test2: build2
LDFLAGS=
test3: compilation.sh
	./compilation.sh 3
FOLDER=./
exec11: ${FOLDER}/test_a_part.c ${FOLDER}/tout.h
	${GNUCOMPILER} -std=c99 $^ -o $@ ${LDFLAGS}
exec22: ${FOLDER}/tout.c ${FOLDER}/tout.h
	${GNUCOMPILER} -std=c99 $^ -o $@ ${LDFLAGS}
build: ${BIN}
	@for e in ${BIN};do \
	echo $${e}; ./$${e}; \
	done
build2: ${BIN2}
	@for e in ${BIN2};do \
	echo $${e}; ./$${e}; \
	done
clean:
	rm -f *.c~ *.cpp~ *.sh~ Makefile~ exec11 exec22 exec1 exec2 exec3  
