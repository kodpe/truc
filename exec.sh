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
echo
if [ $? -eq 0 ]; then
	echo "make success!"
else
	echo -e "\033[1;31mmake failure!\033[0m"; exit
fi
sleep 1

gnome-system-monitor 2>/dev/null &

terminator \
		--borderless \
		--geometry 800x450+0+1000 \
		--command="$VALG_SERVER $EXEC serveur; cat logs_server; zsh" 2>/dev/null &
sleep 2

terminator \
		--borderless \
		--geometry 800x450+1700+1000 \
		--command="$VALG_CLIENT $EXEC client; cat logs_client; zsh" 2>/dev/null &

sleep 12

terminator \
		--borderless \
		--geometry 800x120+850+1150 \
		--command="cd /tmp/ && ls -la *.xpm; zsh" 2>/dev/null &

terminator \
		--borderless \
		--geometry 800x120+850+1300 \
		--command="cd /sgoinfre/goinfre/Perso/sloquett/dcom/; ls -l; zsh" 2>/dev/null &

echo Done
#exit

echo "             auto close in $1 sec"
sleep $1
./close_all.sh
echo Done
