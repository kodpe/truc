#!/bin/bash

EXEC="./yokai"

VALG="valgrind \
	--show-leak-kinds=all \
	--track-origins=yes \
	--leak-check=full \
	--log-file=logs \
"

VALG_SERVER="valgrind \
	--show-leak-kinds=all \
	--track-origins=yes \
	--leak-check=full \
	--log-file=logs_server \
"

VALG_CLIENT="valgrind \
	--show-leak-kinds=all \
	--track-origins=yes \
	--leak-check=full \
	--log-file=logs_client \
"

clear
rm -f /tmp/*.xpm
rm -f /sgoinfre/goinfre/Perso/sloquett/dcom/*
./update_makefile.sh
make -j 
if [ $? -eq 0 ]; then
	echo "make success!"
else
	echo "make failure!"; exit
fi

$VALG_SERVER $EXEC serveur
