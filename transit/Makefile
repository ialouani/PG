SET_DIR = set
SEN_DIR = sentinel
DYN_DIR = dynamic
LNK_DIR = link


BIN = sentinel_struc #sentinel_func
BIN2 = dynamic_struc #dynamic_func
BIN3 = test_link #tests unitaires de la structure intermediaire link
#en premier../////

CC ?= cc
CPPFLAGS = -I ${SET_DIR} -I ${SEN_DIR} -I ${DYN_DIR} -I ${LNK_DIR}
CFLAGS =  -std=c99 -g
LDFLAGS =

.PHONY: all test build clean

all: build test

build: ${BIN}
build2: ${BIN2}
build3: ${BIN3}

test: build
	@for e in ${BIN}; do \
	echo $${e}; ./$${e}; \
	done
test2: build2
	@for e in ${BIN2}; do \
	echo $${e}; ./$${e}; \
	done
test3: build3
	@for e in ${BIN3}; do \
	echo $${e}; ./$${e}; \
	done

clean:
	rm -f *.o ${BIN} ${BIN2} ${BIN3} *~ sentinel_func dynamic_func link_func link_struc test_link link_struc af_sentinel af_dynamic af_link


# Impl sentinel

set_sentinel.o: ${SEN_DIR}/set_sentinel.c ${SEN_DIR}/set_sentinel.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${SEN_DIR}/set_sentinel.c -c

test_sentinel_struc.o: ${SEN_DIR}/test_sentinel_struc.c ${SEN_DIR}/set_sentinel.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${SEN_DIR}/test_sentinel_struc.c -c

sentinel_struc: test_sentinel_struc.o set_sentinel.o
	${CC} test_sentinel_struc.o set_sentinel.o -o $@ ${LDFLAGS}

#pour l'exercice 12
test_sentinel_func.o: ${SET_DIR}/test_set_func.c ${SEN_DIR}/set_sentinel.h
	${CC} ${CPPFLAGS} ${CFLAGS} -DSENTINEL ${SET_DIR}/test_set_func.c -c -o $@

sentinel_func: test_sentinel_func.o set_sentinel.o
	${CC} test_sentinel_func.o set_sentinel.o -o $@ ${LDFLAGS}

# Impl dynamic

set_dynamic.o: ${DYN_DIR}/set_dynamic.c ${DYN_DIR}/set_dynamic.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${DYN_DIR}/set_dynamic.c -c

test_dynamic_struc.o: ${DYN_DIR}/test_dynamic_struc.c ${DYN_DIR}/set_dynamic.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${DYN_DIR}/test_dynamic_struc.c -c

dynamic_struc: test_dynamic_struc.o set_dynamic.o
	${CC} test_dynamic_struc.o set_dynamic.o -o $@ ${LDFLAGS}

#pour l'exercice 12
test_dynamic_func.o: ${SET_DIR}/test_set_func.c ${DYN_DIR}/set_dynamic.h
	${CC} ${CPPFLAGS} ${CFLAGS} -DDYNAMIC ${SET_DIR}/test_set_func.c -c -o $@

dynamic_func: test_dynamic_func.o set_dynamic.o
	${CC} test_dynamic_func.o set_dynamic.o -o $@ ${LDFLAGS}




#link

link.o: ${LNK_DIR}/link.c ${LNK_DIR}/link.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${LNK_DIR}/link.c -c

test_link.o : ${LNK_DIR}/test_link.c ${LNK_DIR}/link.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${LNK_DIR}/test_link.c -c

test_link: test_link.o link.o #voir COMMENTAIRE ci-dessous. 
	${CC} test_link.o link.o -o $@ ${LDFLAGS}
#------------tests de la mise en ouvre du chainage via le type abstrait LINK.



#Impl EN UTILISANT LE TYPE --SET-- PRECEDEMMENT:::::
set_link.o: ${LNK_DIR}/set_link.c ${LNK_DIR}/set_link.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${LNK_DIR}/set_link.c -c

test_link_struc.o : ${LNK_DIR}/test_link_struc.c ${LNK_DIR}/set_link.h ${LNK_DIR}/link.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${LNK_DIR}/test_link_struc.c -c

link_struc: test_link_struc.o set_link.o  link.o #voir COMMENTAIRE ci-dessous. 
	${CC} test_link_struc.o set_link.o  link.o -o $@ ${LDFLAGS}
#pour l'instant(tests dans la forge)
##tests unitaires part1 (voir fichier ./link/test_link_struc.c).
#----------------Application au set : ensemble tad VIA :  link.

#Et pour l'exo12. AUSSI../////(tests fonctionnels pour la partie set_link)
#commane avant pour les 2 targets: dynamic_func et sentinel_func.

test_link_func.o: ${SET_DIR}/test_set_func.c ${LNK_DIR}/set_link.h
	${CC} ${CPPFLAGS} ${CFLAGS} -DLINK ${SET_DIR}/test_set_func.c -c -o $@

link_func: test_link_func.o set_link.o link.o
	${CC} test_link_func.o set_link.o link.o -o $@ ${LDFLAGS}




#--------------------------------------------------------------------------
#:::
af_sentinel: ./set/affectation.c ./sentinel/set_sentinel.c
	gcc -std=c99 -g ${CPPFLAGS} -DSENTINEL $^ -o $@ ${LDFLAGS}
af_dynamic: ./set/affectation.c ./dynamic/set_dynamic.c
	gcc -std=c99 -g ${CPPFLAGS} -DDYNAMIC $^ -o $@ ${LDFLAGS}
af_link: ./set/affectation.c ./link/set_link.c ./link/link.c
	gcc -std=c99 -g ${CPPFLAGS} -DLINK $^ -o $@ ${LDFLAGS}


#
#ajouter pour executer vite ./sentinel_func et tester separement
#l'ajout et la suppression dans l'ensemble implémenté en tableau de sentinelle.
#clean2:
#	rm -f test_add_dfcl sentinel_func sentinel_struc exec1 exec2 exec3 a.out
#test_add_dfcl: test_a_part.c sentinel/set_sentinel.c
#gcc test_a_part.c sentinel/set_sentinel.c -o test_add_dfcl
#add_exec: test_add_dfcl
#./test_add_dfcl
#test_procedures: sentinel_func
#./sentinel_func
#fin___ajout.
#
#c'etait avant.
