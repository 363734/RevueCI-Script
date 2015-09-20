:: Windows version of the run.sh script.
:: This script is much simpler, and does not re-compile the program, nor does it attempt to create the backup directory.

@echo off :: supress Windows prompt output (command names etc.)

:: Go to script directory
set DIR=%~dp0
cd "%DIR%"

:: Copy the IMG folder
xcopy /y original\img\* generation\img

:: Copy the META, NOMS and TRAME files
xcopy /y original\META.tex generation\META.tex
xcopy /y original\TRAME.tex generation\TRAME.tex
xcopy /y original\NOMS.tex generation\NOMS.tex

:: Go to the generation folder
cd generation

:: Do not compile text processing program (lagen.exe) :-p
:: But still, apply text processing to all acts
 :: change encoding of redirected files to UTF-8
chcp 65001
FOR /L %%I IN (0,1,4) DO lagen.exe ../original/ACTE_%%I.tex > ACTE_%%I.tex 

:: Generation of the .pdf
pdflatex scen.tex
FOR /L %%I IN (0,1,4) DO pdflatex scen_a%%I.tex

:: Copy last pdfs into main folder
xcopy /y *.pdf ..

:: Backup the main pdf into the backup folder
cd ..

:: for that, put date in the same form as on Linux (joyful batch code)
:: WARNING: this uses the European convention for dates! 
for /f "tokens=1,2,3 delims=/" %%a in ("%date:~5,10%") do set day=%%a&set month=%%b&set year=%%c

:: finally, do the copy!
copy /y generation\scen.pdf backup\scen_%month%-%day%-%year%.pdf
