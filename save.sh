#!/bin/bash
make -j fclean
git add .
git commit -am save
git push
make -j
clear
ls
echo "done!"
