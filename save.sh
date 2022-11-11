#!/bin/bash
rm -rf dcom
make -j fclean
git add .
git commit -am save
git push
