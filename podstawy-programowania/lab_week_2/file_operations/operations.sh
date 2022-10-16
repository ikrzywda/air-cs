#!/bin/bash

# Prerequisites:
# make sure that delimiter between columns is two spaces

# Posortuj plik według pierwszej kolumny.
awk 'NR==1{print;}' source.txt > out.txt && tail -n +2 "source.txt" | sort >> out.txt

# Zamień wszystkie wystąpienia 'Green Note' na 'Blue Note'.
sed 's/Green\ Note/Blue\ Note/g' source.txt | cat

# Usuń kolumnę 'Cat nr'.
awk -F'[[:space:]][[:space:]]+' '{temp=$2;$2=$3;$3=temp; print;}' source.txt

# Zamień miejscami kolumny 'A-side' i 'B-side'
awk -F'[[:space:]][[:space:]]+' '{$3=""; print;}' source.txt

# Przekształć plik do postaci:
awk -F'[[:space:]][[:space:]]+' '{printf "%-10s & %-30s & %-30s & %-30s & %s \\\\ \\hline\n", $1, $2, $3, $4, $5}' source.txt