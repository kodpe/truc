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

# $VALG_SERVER $EXEC serveur &
# sleep 3
# $VALG_CLIENT $EXEC client &

terminator \
		--borderless \
		--title "server" \
		--geometry 800x450+0+1000 \
		--command="$VALG_SERVER $EXEC serveur && cat logs_server && zsh"
sleep 2

terminator \
		--borderless \
		--title "client" \
		--geometry 800x450+1700+1000 \
		--command="$VALG_CLIENT $EXEC client && cat logs_client && zsh"

sleep 12

terminator \
		--borderless \
		--geometry 800x220+850+1000 \
		--command="cd /tmp/ && ls -la *.xpm && zsh"

terminator \
		--borderless \
		--geometry 800x220+850+1220 \
		--command="cd /sgoinfre/goinfre/Perso/sloquett/dcom/ && ls -la && zsh"

echo Done
