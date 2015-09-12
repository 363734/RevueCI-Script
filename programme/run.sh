#!/bin/bash

## Go to script directory ##

DIR=$(dirname $0)
cd $DIR

## Copy the img folder ##

cp ./original/img/* ./generation/img

## Copy the META, NOMS & TRAME files ##

cp ./original/META.tex ./generation/META.tex
cp ./original/NOMS.tex ./generation/NOMS.tex
cp ./original/TRAME.tex ./generation/TRAME.tex

## Go to generation folder ##

cd ./generation

## Compile text processing program ##

gcc lagen.c

## Apply text processing to all acts ##

for i in {0..4}
do
	./a.out ../original/ACTE_$i.tex > ACTE_$i.tex -charset=utf-8
done

## Generation of the .pdf ##

pdflatex scen.tex
for i in {0..4}
do
	pdflatex ./scen_a$i.tex
done

## Copy last pdfs into main folder ##

cp *.pdf ./..

## Backup the main .pdf into the backup folder ##

cd ..

if [ -d "backup" ]
then            
	echo "backup directory already there"
else                                                                   
	mkdir backup                             
fi           

NOW=$(date +"%m-%d-%Y") 
cp ./generation/scen.pdf ./backup/scen_$NOW.pdf 

