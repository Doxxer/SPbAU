#!/bin/bash
# Закодируйте файл, заменив в нем каждый символ на следующий по ASCII таблице.

sed -ir 's/^.*$/bash nextSymbol.sh "&"/geI' text.txt
