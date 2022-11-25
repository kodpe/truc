#!/bin/bash
make -j fclean
git add .
git commit -am save
git push
make -j
clear
ls -la
echo -e "\033[1;33mDone!\033[0m"
