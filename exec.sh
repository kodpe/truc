#!/bin/bash
clear
rm -f /sgoinfre/goinfre/Perso/sloquett/dcom/*
./update_makefile.sh

VALG="valgrind \
	--show-leak-kinds=all \
	--track-origins=yes \
	--leak-check=full \
	--log-file=logs \
"

EXEC="./yokai"

make -j && $VALG $EXEC serveur &

exit

sleep 5
$EXEC client &
echo Done

# make -j && $VALG $EXEC &

# sleep 1
# make -j && valgrind --leak-check=full ./yokai &

