#!/bin/bash
rm -rf dcom
mkdir dcom
./update_makefile.sh
clear

VALG="valgrind \
	--show-leak-kinds=all \
	--track-origins=yes \
	--leak-check=full \
	--log-file=logs \
"

EXEC="./yokai"

make -j && $VALG $EXEC serveur &
sleep 5
$EXEC client &
echo Done

# make -j && $VALG $EXEC &

# sleep 1
# make -j && valgrind --leak-check=full ./yokai &

