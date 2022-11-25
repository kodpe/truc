#!/bin/bash
make -j fclean
git add .
git commit -am save
git push
sleep 1
echo -e "\033[1;33mDone!\033[0m"
make -j
