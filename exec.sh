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
# rm -f /sgoinfre/goinfre/Perso/sloquett/dcom/*
./update_makefile.sh
make -j 
if [ $? -eq 0 ]; then
	echo "make success!"
else
	echo "make failure!"; exit
fi

# $VALG_SERVER $EXEC serveur &
# sleep 3
# $VALG_CLIENT $EXEC client &

terminator \
		--borderless \
		--title "server" \
		--geometry 800x450+0+990 \
		--command="$VALG_SERVER $EXEC serveur && cat logs_server && zsh"
sleep 3

terminator \
		--borderless \
		--title "client" \
		--geometry 800x450+1300+990 \
		--command="$VALG_CLIENT $EXEC client && cat logs_client && zsh"

echo Done
