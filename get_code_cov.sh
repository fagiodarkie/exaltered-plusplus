#!/bin/bash
for filename in `find . | egrep '\.cpp'`; 
do 
  gcov -n -o . $filename > /dev/null; 
done

bash <(curl -s https://codecov.io/bash)
