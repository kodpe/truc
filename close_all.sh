#!/bin/bash
sleep $1
pkill gnome-system-mo
pkill gnome-system-monitor
pkill yokai
pkill terminator
rm -f /tmp/*.xpm
rm -f /sgoinfre/goinfre/Perso/sloquett/dcom/*
echo -e "\033[1;32mDone!\033[0m" && echo
