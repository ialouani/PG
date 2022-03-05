#!/bin/bash
echo "__________ADD/REMOVE sans assert"
echo -n ""
gcc test_a_part.c -o exec1 && ./exec1 #test_a_part.c tests sans assert add/rmv
#testant surtout la structure
echo -n ""
echo -n ""
echo "2ieme test (tests de structure tous sentinel.h avec ASSERT:____________"
var1=$(./exec2)
echo "     *****************Ok!; tests structurels passent."
echo -n ""
echo -n ""
gcc tout.c -o exec2 && ./exec2
#testant la structure un peu plus de fonctions en tests unitaires() triviaux
#=>fonctionnel>dernier_--[]/;// 
echo -n ""
echo -n ""
echo "3ieme test (tests fonctionnels tous set.h --application au set implementee suivant sentinel.h prototypes de fonctions et defintion type incomplet de structure dans set.h) avec ASSERT(toutes les fonctions restantes càd.):____________"
gcc -DSENTINEL ../set/test_set_func.c ../sentinel/set_sentinel.c -o exec3 && ./exec3 #-DSENTINEL IMPORTANT!!!!!
echo "    *****************Ok!; tests fonctionnels passent."
echo -n ""
echo -n ""
echo -n "test generalise sans etre guide sans separation de fichiers :"
#application des tests fonctionnels direct car les structurels passent
#en terminal via l'affichage des executions par make make test2 make test3
#via BIN BIN2 BIN3 (BIN=sentinel_struc && test: build && build: ${BIN}
#@for e in ${BIN};do \
#    echo $${e}; ./$${e}; \
#    done

echo -n "*******s'entrainer sans valgrind tout au debut..///*********************"
if [ $1 == 3 ];then
    rm -f exec1
    rm -f exec2
    rm -f exec3
    rm -f a.out
    rm -f *.sh~ *.h~
fi
