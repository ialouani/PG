SET_DIR = set
SEN_DIR = sentinel
DYN_DIR = dynamic
LNK_DIR = link

#**********************************executables des tests structurels/unitaires:
BIN1 = sentinel_struc #sentinel_func(+)<.
BIN2 = dynamic_struc #dynamic_func(+)<.
BIN30 = test_link #tests unitaires de la structure intermediaire link
#en premier../////
BIN3= link_struc #link_func(+)<.(de meme BIEN SUR)


#**********************************executables des tests fonctionnels des 3:
BIN_21=sentinel_func
BIN_22=dynamic_func
BIN_23=link_func
#les executables des 3 tests fonctionnels suivant un seul fichier unique
#set/est_set_func.c parametre par la donnee de la macro en ligne de compilation
#i.e. au moment de la compilation.

#*************
CC ?= cc
CPPFLAGS = -I ${SET_DIR} -I ${SEN_DIR} -I ${DYN_DIR} -I ${LNK_DIR}
CFLAGS =  -std=c99 -g
LDFLAGS =
#*************
.PHONY: all test build clean

all: build 


build: build_executables1 build_executables2
test: tests_structurels tests_fonctionnels

build_executables1: build1 build2 build30 build3 #target build de compilation de codes
#relatifs aux tests structurels des 2 implementations y compris les tests
#unitaires du type link..
tests_structurels: test1 test2 test30 test3 #execution automatique de tous les tests
#structurels des 3 implémentations y compris les tests utitaires passagers du
#type link dans l'implémentation de link/set_link.c.
#************Passons au target general de tests fonctionnels des 3:
build_executables2: build_21 build_22 build_23
tests_fonctionnels: test_21 test_22 test_23

build_21: ${BIN_21}
build_22: ${BIN_22}
build_23: ${BIN_23}

#remarque un ${??} avec ?? un target permet depuis un target l'appelant de
#faire un make dessus.
test_21: build_21
	@for e in ${BIN_21};do \
	echo $${e}; ./$${e}; \
	done
test_22: build_22
	@for e in ${BIN_22};do \
	echo $${e}; ./$${e}; \
	done
test_23: build_23
	@for e in ${BIN_23};do \
	echo $${e}; ./$${e}; \
	done

build1: ${BIN1}
build2: ${BIN2}
build30: ${BIN30} #<=>make test_link puis un tagret en dependance avec build30
#peut iterer sur ce qu'on a faut un make dessus cad. l'executable BIN30
#a partir de @for e in ${BIN30};do\ et ainsi de suite..///
build3: ${BIN3}

test1: build1
	@for e in ${BIN1}; do \
	echo $${e}; ./$${e}; \
	done
test2: build2
	@for e in ${BIN2}; do \
	echo $${e}; ./$${e}; \
	done
test30: build30
	@for e in ${BIN30}; do \
	echo $${e}; ./$${e}; \
	done
test3: build3
	@for e in ${BIN3}; do \
	echo $${e}; ./$${e}; \
	done

clean:
	rm -f *.o ${BIN1} ${BIN2} ${BIN30} ${BIN3} ${BIN_21} ${BIN_22} ${BIN_23} *~ sentinel_func dynamic_func link_func #par mesure de surete car les 3
#derniers exeutables en ${..} correspondent respectivement à :
# 		  sentinel_func/dynamic_func/link_func. (-f evite la suppression
#multiple en passant une erreur)


# Impl sentinel

set_sentinel.o: ${SEN_DIR}/set_sentinel.c ${SEN_DIR}/set_sentinel.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${SEN_DIR}/set_sentinel.c -c

test_sentinel_struc2.o: ${SEN_DIR}/test_sentinel_struc2.c ${SEN_DIR}/set_sentinel.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${SEN_DIR}/test_sentinel_struc2.c -c

sentinel_struc: test_sentinel_struc2.o set_sentinel.o
	${CC} test_sentinel_struc2.o set_sentinel.o -o $@ ${LDFLAGS}

#pour l'exercice 12
test_sentinel_func2.o: ${SET_DIR}/test_set_func2.c ${SEN_DIR}/set_sentinel.h
	${CC} ${CPPFLAGS} ${CFLAGS} -DSENTINEL ${SET_DIR}/test_set_func2.c -c -o $@

sentinel_func1: test_sentinel_func2.o set_sentinel.o
	${CC} test_sentinel_func2.o set_sentinel.o -o $@ ${LDFLAGS}
sentinel_func: test_fun1 #approche generaliste masquer
#a la compilation en gcc -c des tests les details de la struct set.


# Impl dynamic

set_dynamic.o: ${DYN_DIR}/set_dynamic.c ${DYN_DIR}/set_dynamic.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${DYN_DIR}/set_dynamic.c -c

test_dynamic_struc2.o: ${DYN_DIR}/test_dynamic_struc2.c ${DYN_DIR}/set_dynamic.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${DYN_DIR}/test_dynamic_struc2.c -c

dynamic_struc: test_dynamic_struc2.o set_dynamic.o
	${CC} test_dynamic_struc2.o set_dynamic.o -o $@ ${LDFLAGS}

#pour l'exercice 12
test_dynamic_func.o: ${SET_DIR}/test_set_func.c ${DYN_DIR}/set_dynamic.h
	${CC} ${CPPFLAGS} ${CFLAGS} -DDYNAMIC ${SET_DIR}/test_set_func.c -c -o $@

dynamic_func2: test_dynamic_func.o set_dynamic.o
	${CC} test_dynamic_func.o set_dynamic.o -o $@ ${LDFLAGS}
dynamic_func: test_fun2



#link

link.o: ${LNK_DIR}/link.c ${LNK_DIR}/link.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${LNK_DIR}/link.c -c

test_link.o : ${LNK_DIR}/test_link.c ${LNK_DIR}/link.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${LNK_DIR}/test_link.c -c

test_link: test_link.o link.o #voir COMMENTAIRE ci-dessous. 
	${CC} test_link.o link.o -o $@ ${LDFLAGS}
#------------tests de la mise en ouvre du chainage via le type abstrait LINK.



#Impl EN UTILISANT LE TYPE --LINK-- PRECEDEMMENT:::::
set_link.o: ${LNK_DIR}/set_link.c ${LNK_DIR}/set_link.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${LNK_DIR}/set_link.c -c

test_link_struc2.o : ${LNK_DIR}/test_link_struc2.c ${LNK_DIR}/set_link.h ${LNK_DIR}/link.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${LNK_DIR}/test_link_struc2.c -c

link_struc: test_link_struc2.o set_link.o  link.o #voir COMMENTAIRE ci-dessous. 
	${CC} test_link_struc2.o set_link.o  link.o -o $@ ${LDFLAGS}
#pour l'instant(tests dans la forge)
##tests unitaires part1 (voir fichier ./link/test_link_struc.c).
#----------------Application au set : ensemble tad VIA :  link.

#Et pour l'exo12. AUSSI../////(tests fonctionnels pour la partie set_link)
#comme avant pour les 2 targets: dynamic_func et sentinel_func.(autre chose
#ici)

test_link_func.o: ${SET_DIR}/test_set_func.c ${LNK_DIR}/set_link.h
	${CC} ${CPPFLAGS} ${CFLAGS} -DLINK ${SET_DIR}/test_set_func.c -c -o $@

link_func2: test_link_func.o set_link.o link.o
	${CC} test_link_func.o set_link.o link.o -o $@ ${LDFLAGS}
link_func: test_fun3



#--------------------------------------------------------------------------
#*****************TD3: ecriture des choses pas prises en compte sur thor
VAR1= -I ${SEN_DIR}
VAR2= -I ${DYN_DIR}
VAR3= -I ${LNK_DIR}
affectation_sentinel.o: ${SET_DIR}/affectation.c ${SET_DIR}/set.h
	gcc ${VAR1} -c -DSENTINEL $< -o $@
affectation_dynamique.o: ${SET_DIR}/affectation.c ${SET_DIR}/set.h
	gcc ${VAR2} -c -DDYNAMIC $< -o $@
affectation_link.o: ${SET_DIR}/affectation.c ${SET_DIR}/set.h
	gcc ${VAR3} -c -DLINK $< -o $@
af_sentinel: affectation_sentinel.o ${SEN_DIR}/set_sentinel.c
	${CC} ${CPPFLAGS} $^ -o $@ ${LDFLAGS}
af_dynamic: affectation_dynamique.o ${DYN_DIR}/set_dynamic.c
	${CC} ${CPPFLAGS} $^ -o $@ ${LDFLAGS}
af_link: affectation_link.o ${LNK_DIR}/set_link.c ${LNK_DIR}/link.c 
	${CC} ${CPPFLAGS} $^ -o $@ ${LDFLAGS}
#l'avantage de $"@";$"<";$"^";$"?";$"+" est de pouvoir recopier pour
#refaire la meme chose sans changer ceci contrairement a l'autre
#rapproche -1ligne dans le nom des repertoires/set_??.c et affectation_??.o.
af_1__exec: af_sentinel
#1ere maniere(*) de le faire make -> execution automatique
	./af_sentinel
#2ieme maniere: make ?? ce ?? prendra logiquement le .o mais la il devrait
#prendre un target pour cible donc ca serait vu l'evoquation des termes .o
#build11 telque: build11: ${af_one} pour designer une execution avec
#af_one dans le makefile:->> af_one=af_sentinel.
#remarque: affectation teste pour tous -> dans le folder: set. (./set).///
#voir ci-dessus pour la maniere fiable++ de faire (*).
af_one=af_sentinel
build11: ${af_one}
af2_1__exec: build11
	@for e in ${af_one};do \
	echo $${e}; ./$${e} ; \
	done
af_2__exec: af_dynamic
	./af_dynamic
#1ere approche; refaisons la deuxieme mais avec link cette fois.
af_3=af_link
build33: ${af_three}
af_3__exec: build33 #necessite un pre-appel a af_link par le Make d'ABORD.(**)
	@for ee in ${af_3};do \
	echo $${ee}; ./$${ee} ; \
	done
af: af_sentinel af_dynamic af_link #(**): eviter des problemes d'execution
#via le Makefile.
#pas besoin ICI..
#g3: af
#	valgrind ./af_sentinel && valgrind ./af_dynamic && valgrind ./af_link
clean3:
	rm -f *.o af_sentinel af_dynamic af_link af_sentinel2 af_dynamic2 af_link2 a.out
affectation.o: ./set/affectation2.c ${SET_DIR}/set.h
	gcc -c ${CPPFLAGS} $< -o $@
af_sentinel2: affectation.o ${SEN_DIR}/set_sentinel.c
	gcc ${CPPFLAGS} $^ -o $@
af_dynamic2: affectation.o ${DYN_DIR}/set_dynamic.c
	gcc ${CPPFLAGS} $^ -o $@
af_link2: affectation.o ${LNK_DIR}/set_link.c ./link/link.c
	gcc ${CPPFLAGS} $^ -o $@
af2: af_sentinel2 af_dynamic2 af_link2
#*****************************GENERALISATION:
#>>compilation d'1 seul fois du fichier des tests fonctionnels
#car le type struct set(*NN) est cache (via des void* RECCONUS)
#+exec en le linkant aux differents fichiers contenant les implementations
#des fonctions .
test_set_fun.o: ${SET_DIR}/test_set_func.c
	gcc -c -std=c99 -g $< -o $@ ${LDFLAGS}
test_set_fun2.o: ${SET_DIR}/test_set_func2.c
	gcc -c -std=c99 -g $< -o $@ ${LDFLAGS}
test_fun1: test_set_fun2.o ./sentinel/set_sentinel.c
	gcc -std=c99 -g $^ -o sentinel_func
test_fun2: test_set_fun2.o ./dynamic/set_dynamic.c
	gcc -std=c99 -g $^ -o dynamic_func
test_fun3: test_set_fun2.o ./link/set_link.c ./link/link.c
	gcc -std=c99 -g $^ -o link_func
#attention a l'oubli d'un make clean_all pour tester successivement(.(//\\).|||)
#les 2 approches.
test_fun1__exec: test_fun1
	./test_fun1
test_fun2__exec: test_fun2
	./test_fun2
test_fun3__exec: test_fun3
	./test_fun3
clean33:
	rm -f test_fun1 test_fun2 test_fun3
clean_all: clean clean3 clean33
	rm -f dynamic_func2 sentinel_func2 link_func2 sentinel_func1

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




#-----------------------------------------------------------------------------
#------------------------------------------------------------------------------
