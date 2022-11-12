#!/bin/bash
rm -rf dcom
mkdir dcom
./update_makefile.sh
clear

VALG="valgrind \
	--show-leak-kinds=all \
	--track-origins=yes \
	--leak-check=full \
"

EXEC="./yokai"

make -j && $VALG $EXEC

# make -j && $VALG $EXEC &

# sleep 1
# make -j && valgrind --leak-check=full ./yokai &

