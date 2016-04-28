#!/bin/bash 
##---------------------------------------------------------------------------## 
## EEDL Data Downloader and xsdir file writer 
##---------------------------------------------------------------------------## 
 
# Export a python script to convert relative paths to absolute paths. 
EEDL_DATA_PATH=/home/software/endldata/eedl 
EEDL_XSDIR_FILE=xsdir 
 
if [ ! -d "$EEDL_DATA_PATH" ]; then 
mkdir $EEDL_DATA_PATH 
fi 
 
cd $EEDL_DATA_PATH 
 
if [ -d "$EEDL_DATA_PATH/H" ]; then 
echo "$EEDL_DATA_PATH/H already exists" 
else 
mkdir H && cd H && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za001000 
cd ../ && echo "1000 $EEDL_DATA_PATH/H" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/He" ]; then 
echo "$EEDL_DATA_PATH/He already exists" 
else 
mkdir He && cd He && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za002000 
cd ../ && echo "2000 $EEDL_DATA_PATH/He" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Li" ]; then 
echo "$EEDL_DATA_PATH/Li already exists" 
else 
mkdir Li && cd Li && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za003000 
cd ../ && echo "3000 $EEDL_DATA_PATH/Li" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Be" ]; then 
echo "$EEDL_DATA_PATH/Be already exists" 
else 
mkdir Be && cd Be && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za004000 
cd ../ && echo "4000 $EEDL_DATA_PATH/Be" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/B" ]; then 
echo "$EEDL_DATA_PATH/B already exists" 
else 
mkdir B && cd B && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za005000 
cd ../ && echo "5000 $EEDL_DATA_PATH/B" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/C" ]; then 
echo "$EEDL_DATA_PATH/C already exists" 
else 
mkdir C && cd C && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za006000 
cd ../ && echo "6000 $EEDL_DATA_PATH/C" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/N" ]; then 
echo "$EEDL_DATA_PATH/N already exists" 
else 
mkdir N && cd N && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za007000 
cd ../ && echo "7000 $EEDL_DATA_PATH/N" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/O" ]; then 
echo "$EEDL_DATA_PATH/O already exists" 
else 
mkdir O && cd O && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za008000 
cd ../ && echo "8000 $EEDL_DATA_PATH/O" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/F" ]; then 
echo "$EEDL_DATA_PATH/F already exists" 
else 
mkdir F && cd F && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za009000 
cd ../ && echo "9000 $EEDL_DATA_PATH/F" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Ne" ]; then 
echo "$EEDL_DATA_PATH/Ne already exists" 
else 
mkdir Ne && cd Ne && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za010000 
cd ../ && echo "10000 $EEDL_DATA_PATH/Ne" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Na" ]; then 
echo "$EEDL_DATA_PATH/Na already exists" 
else 
mkdir Na && cd Na && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za011000 
cd ../ && echo "11000 $EEDL_DATA_PATH/Na" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Mg" ]; then 
echo "$EEDL_DATA_PATH/Mg already exists" 
else 
mkdir Mg && cd Mg && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za012000 
cd ../ && echo "12000 $EEDL_DATA_PATH/Mg" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Al" ]; then 
echo "$EEDL_DATA_PATH/Al already exists" 
else 
mkdir Al && cd Al && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za013000 
cd ../ && echo "13000 $EEDL_DATA_PATH/Al" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Si" ]; then 
echo "$EEDL_DATA_PATH/Si already exists" 
else 
mkdir Si && cd Si && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za014000 
cd ../ && echo "14000 $EEDL_DATA_PATH/Si" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/P" ]; then 
echo "$EEDL_DATA_PATH/P already exists" 
else 
mkdir P && cd P && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za015000 
cd ../ && echo "15000 $EEDL_DATA_PATH/P" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/S" ]; then 
echo "$EEDL_DATA_PATH/S already exists" 
else 
mkdir S && cd S && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za016000 
cd ../ && echo "16000 $EEDL_DATA_PATH/S" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Cl" ]; then 
echo "$EEDL_DATA_PATH/Cl already exists" 
else 
mkdir Cl && cd Cl && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za017000 
cd ../ && echo "17000 $EEDL_DATA_PATH/Cl" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Ar" ]; then 
echo "$EEDL_DATA_PATH/Ar already exists" 
else 
mkdir Ar && cd Ar && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za018000 
cd ../ && echo "18000 $EEDL_DATA_PATH/Ar" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/K" ]; then 
echo "$EEDL_DATA_PATH/K already exists" 
else 
mkdir K && cd K && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za019000 
cd ../ && echo "19000 $EEDL_DATA_PATH/K" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Ca" ]; then 
echo "$EEDL_DATA_PATH/Ca already exists" 
else 
mkdir Ca && cd Ca && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za020000 
cd ../ && echo "20000 $EEDL_DATA_PATH/Ca" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Sc" ]; then 
echo "$EEDL_DATA_PATH/Sc already exists" 
else 
mkdir Sc && cd Sc && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za021000 
cd ../ && echo "21000 $EEDL_DATA_PATH/Sc" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Ti" ]; then 
echo "$EEDL_DATA_PATH/Ti already exists" 
else 
mkdir Ti && cd Ti && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za022000 
cd ../ && echo "22000 $EEDL_DATA_PATH/Ti" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/V" ]; then 
echo "$EEDL_DATA_PATH/V already exists" 
else 
mkdir V && cd V && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za023000 
cd ../ && echo "23000 $EEDL_DATA_PATH/V" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Cr" ]; then 
echo "$EEDL_DATA_PATH/Cr already exists" 
else 
mkdir Cr && cd Cr && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za024000 
cd ../ && echo "24000 $EEDL_DATA_PATH/Cr" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Mn" ]; then 
echo "$EEDL_DATA_PATH/Mn already exists" 
else 
mkdir Mn && cd Mn && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za025000 
cd ../ && echo "25000 $EEDL_DATA_PATH/Mn" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Fe" ]; then 
echo "$EEDL_DATA_PATH/Fe already exists" 
else 
mkdir Fe && cd Fe && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za026000 
cd ../ && echo "26000 $EEDL_DATA_PATH/Fe" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Co" ]; then 
echo "$EEDL_DATA_PATH/Co already exists" 
else 
mkdir Co && cd Co && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za027000 
cd ../ && echo "27000 $EEDL_DATA_PATH/Co" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Ni" ]; then 
echo "$EEDL_DATA_PATH/Ni already exists" 
else 
mkdir Ni && cd Ni && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za028000 
cd ../ && echo "28000 $EEDL_DATA_PATH/Ni" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Cu" ]; then 
echo "$EEDL_DATA_PATH/Cu already exists" 
else 
mkdir Cu && cd Cu && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za029000 
cd ../ && echo "29000 $EEDL_DATA_PATH/Cu" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Zn" ]; then 
echo "$EEDL_DATA_PATH/Zn already exists" 
else 
mkdir Zn && cd Zn && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za030000 
cd ../ && echo "30000 $EEDL_DATA_PATH/Zn" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Ga" ]; then 
echo "$EEDL_DATA_PATH/Ga already exists" 
else 
mkdir Ga && cd Ga && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za031000 
cd ../ && echo "31000 $EEDL_DATA_PATH/Ga" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Ge" ]; then 
echo "$EEDL_DATA_PATH/Ge already exists" 
else 
mkdir Ge && cd Ge && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za032000 
cd ../ && echo "32000 $EEDL_DATA_PATH/Ge" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/As" ]; then 
echo "$EEDL_DATA_PATH/As already exists" 
else 
mkdir As && cd As && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za033000 
cd ../ && echo "33000 $EEDL_DATA_PATH/As" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Se" ]; then 
echo "$EEDL_DATA_PATH/Se already exists" 
else 
mkdir Se && cd Se && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za034000 
cd ../ && echo "34000 $EEDL_DATA_PATH/Se" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Br" ]; then 
echo "$EEDL_DATA_PATH/Br already exists" 
else 
mkdir Br && cd Br && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za035000 
cd ../ && echo "35000 $EEDL_DATA_PATH/Br" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Kr" ]; then 
echo "$EEDL_DATA_PATH/Kr already exists" 
else 
mkdir Kr && cd Kr && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za036000 
cd ../ && echo "36000 $EEDL_DATA_PATH/Kr" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Rb" ]; then 
echo "$EEDL_DATA_PATH/Rb already exists" 
else 
mkdir Rb && cd Rb && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za037000 
cd ../ && echo "37000 $EEDL_DATA_PATH/Rb" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Sr" ]; then 
echo "$EEDL_DATA_PATH/Sr already exists" 
else 
mkdir Sr && cd Sr && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za038000 
cd ../ && echo "38000 $EEDL_DATA_PATH/Sr" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Y" ]; then 
echo "$EEDL_DATA_PATH/Y already exists" 
else 
mkdir Y && cd Y && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za039000 
cd ../ && echo "39000 $EEDL_DATA_PATH/Y" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Zr" ]; then 
echo "$EEDL_DATA_PATH/Zr already exists" 
else 
mkdir Zr && cd Zr && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za040000 
cd ../ && echo "40000 $EEDL_DATA_PATH/Zr" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Nb" ]; then 
echo "$EEDL_DATA_PATH/Nb already exists" 
else 
mkdir Nb && cd Nb && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za041000 
cd ../ && echo "41000 $EEDL_DATA_PATH/Nb" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Mo" ]; then 
echo "$EEDL_DATA_PATH/Mo already exists" 
else 
mkdir Mo && cd Mo && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za042000 
cd ../ && echo "42000 $EEDL_DATA_PATH/Mo" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Tc" ]; then 
echo "$EEDL_DATA_PATH/Tc already exists" 
else 
mkdir Tc && cd Tc && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za043000 
cd ../ && echo "43000 $EEDL_DATA_PATH/Tc" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Ru" ]; then 
echo "$EEDL_DATA_PATH/Ru already exists" 
else 
mkdir Ru && cd Ru && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za044000 
cd ../ && echo "44000 $EEDL_DATA_PATH/Ru" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Rh" ]; then 
echo "$EEDL_DATA_PATH/Rh already exists" 
else 
mkdir Rh && cd Rh && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za045000 
cd ../ && echo "45000 $EEDL_DATA_PATH/Rh" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Pd" ]; then 
echo "$EEDL_DATA_PATH/Pd already exists" 
else 
mkdir Pd && cd Pd && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za046000 
cd ../ && echo "46000 $EEDL_DATA_PATH/Pd" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Ag" ]; then 
echo "$EEDL_DATA_PATH/Ag already exists" 
else 
mkdir Ag && cd Ag && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za047000 
cd ../ && echo "47000 $EEDL_DATA_PATH/Ag" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Cd" ]; then 
echo "$EEDL_DATA_PATH/Cd already exists" 
else 
mkdir Cd && cd Cd && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za048000 
cd ../ && echo "48000 $EEDL_DATA_PATH/Cd" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/In" ]; then 
echo "$EEDL_DATA_PATH/In already exists" 
else 
mkdir In && cd In && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za049000 
cd ../ && echo "49000 $EEDL_DATA_PATH/In" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Sn" ]; then 
echo "$EEDL_DATA_PATH/Sn already exists" 
else 
mkdir Sn && cd Sn && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za050000 
cd ../ && echo "50000 $EEDL_DATA_PATH/Sn" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Sb" ]; then 
echo "$EEDL_DATA_PATH/Sb already exists" 
else 
mkdir Sb && cd Sb && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za051000 
cd ../ && echo "51000 $EEDL_DATA_PATH/Sb" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Te" ]; then 
echo "$EEDL_DATA_PATH/Te already exists" 
else 
mkdir Te && cd Te && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za052000 
cd ../ && echo "52000 $EEDL_DATA_PATH/Te" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/I" ]; then 
echo "$EEDL_DATA_PATH/I already exists" 
else 
mkdir I && cd I && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za053000 
cd ../ && echo "53000 $EEDL_DATA_PATH/I" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Xe" ]; then 
echo "$EEDL_DATA_PATH/Xe already exists" 
else 
mkdir Xe && cd Xe && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za054000 
cd ../ && echo "54000 $EEDL_DATA_PATH/Xe" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Cs" ]; then 
echo "$EEDL_DATA_PATH/Cs already exists" 
else 
mkdir Cs && cd Cs && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za055000 
cd ../ && echo "55000 $EEDL_DATA_PATH/Cs" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Ba" ]; then 
echo "$EEDL_DATA_PATH/Ba already exists" 
else 
mkdir Ba && cd Ba && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za056000 
cd ../ && echo "56000 $EEDL_DATA_PATH/Ba" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/La" ]; then 
echo "$EEDL_DATA_PATH/La already exists" 
else 
mkdir La && cd La && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za057000 
cd ../ && echo "57000 $EEDL_DATA_PATH/La" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Ce" ]; then 
echo "$EEDL_DATA_PATH/Ce already exists" 
else 
mkdir Ce && cd Ce && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za058000 
cd ../ && echo "58000 $EEDL_DATA_PATH/Ce" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Pr" ]; then 
echo "$EEDL_DATA_PATH/Pr already exists" 
else 
mkdir Pr && cd Pr && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za059000 
cd ../ && echo "59000 $EEDL_DATA_PATH/Pr" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Nd" ]; then 
echo "$EEDL_DATA_PATH/Nd already exists" 
else 
mkdir Nd && cd Nd && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za060000 
cd ../ && echo "60000 $EEDL_DATA_PATH/Nd" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Pm" ]; then 
echo "$EEDL_DATA_PATH/Pm already exists" 
else 
mkdir Pm && cd Pm && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za061000 
cd ../ && echo "61000 $EEDL_DATA_PATH/Pm" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Sm" ]; then 
echo "$EEDL_DATA_PATH/Sm already exists" 
else 
mkdir Sm && cd Sm && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za062000 
cd ../ && echo "62000 $EEDL_DATA_PATH/Sm" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Eu" ]; then 
echo "$EEDL_DATA_PATH/Eu already exists" 
else 
mkdir Eu && cd Eu && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za063000 
cd ../ && echo "63000 $EEDL_DATA_PATH/Eu" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Gd" ]; then 
echo "$EEDL_DATA_PATH/Gd already exists" 
else 
mkdir Gd && cd Gd && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za064000 
cd ../ && echo "64000 $EEDL_DATA_PATH/Gd" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Tb" ]; then 
echo "$EEDL_DATA_PATH/Tb already exists" 
else 
mkdir Tb && cd Tb && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za065000 
cd ../ && echo "65000 $EEDL_DATA_PATH/Tb" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Dy" ]; then 
echo "$EEDL_DATA_PATH/Dy already exists" 
else 
mkdir Dy && cd Dy && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za066000 
cd ../ && echo "66000 $EEDL_DATA_PATH/Dy" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Ho" ]; then 
echo "$EEDL_DATA_PATH/Ho already exists" 
else 
mkdir Ho && cd Ho && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za067000 
cd ../ && echo "67000 $EEDL_DATA_PATH/Ho" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Er" ]; then 
echo "$EEDL_DATA_PATH/Er already exists" 
else 
mkdir Er && cd Er && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za068000 
cd ../ && echo "68000 $EEDL_DATA_PATH/Er" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Tm" ]; then 
echo "$EEDL_DATA_PATH/Tm already exists" 
else 
mkdir Tm && cd Tm && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za069000 
cd ../ && echo "69000 $EEDL_DATA_PATH/Tm" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Yb" ]; then 
echo "$EEDL_DATA_PATH/Yb already exists" 
else 
mkdir Yb && cd Yb && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za070000 
cd ../ && echo "70000 $EEDL_DATA_PATH/Yb" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Lu" ]; then 
echo "$EEDL_DATA_PATH/Lu already exists" 
else 
mkdir Lu && cd Lu && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za071000 
cd ../ && echo "71000 $EEDL_DATA_PATH/Lu" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Hf" ]; then 
echo "$EEDL_DATA_PATH/Hf already exists" 
else 
mkdir Hf && cd Hf && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za072000 
cd ../ && echo "72000 $EEDL_DATA_PATH/Hf" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Ta" ]; then 
echo "$EEDL_DATA_PATH/Ta already exists" 
else 
mkdir Ta && cd Ta && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za073000 
cd ../ && echo "73000 $EEDL_DATA_PATH/Ta" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/W" ]; then 
echo "$EEDL_DATA_PATH/W already exists" 
else 
mkdir W && cd W && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za074000 
cd ../ && echo "74000 $EEDL_DATA_PATH/W" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Re" ]; then 
echo "$EEDL_DATA_PATH/Re already exists" 
else 
mkdir Re && cd Re && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za075000 
cd ../ && echo "75000 $EEDL_DATA_PATH/Re" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Os" ]; then 
echo "$EEDL_DATA_PATH/Os already exists" 
else 
mkdir Os && cd Os && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za076000 
cd ../ && echo "76000 $EEDL_DATA_PATH/Os" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Ir" ]; then 
echo "$EEDL_DATA_PATH/Ir already exists" 
else 
mkdir Ir && cd Ir && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za077000 
cd ../ && echo "77000 $EEDL_DATA_PATH/Ir" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Pt" ]; then 
echo "$EEDL_DATA_PATH/Pt already exists" 
else 
mkdir Pt && cd Pt && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za078000 
cd ../ && echo "78000 $EEDL_DATA_PATH/Pt" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Au" ]; then 
echo "$EEDL_DATA_PATH/Au already exists" 
else 
mkdir Au && cd Au && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za079000 
cd ../ && echo "79000 $EEDL_DATA_PATH/Au" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Hg" ]; then 
echo "$EEDL_DATA_PATH/Hg already exists" 
else 
mkdir Hg && cd Hg && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za080000 
cd ../ && echo "80000 $EEDL_DATA_PATH/Hg" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Tl" ]; then 
echo "$EEDL_DATA_PATH/Tl already exists" 
else 
mkdir Tl && cd Tl && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za081000 
cd ../ && echo "81000 $EEDL_DATA_PATH/Tl" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Pb" ]; then 
echo "$EEDL_DATA_PATH/Pb already exists" 
else 
mkdir Pb && cd Pb && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za082000 
cd ../ && echo "82000 $EEDL_DATA_PATH/Pb" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Bi" ]; then 
echo "$EEDL_DATA_PATH/Bi already exists" 
else 
mkdir Bi && cd Bi && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za083000 
cd ../ && echo "83000 $EEDL_DATA_PATH/Bi" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Po" ]; then 
echo "$EEDL_DATA_PATH/Po already exists" 
else 
mkdir Po && cd Po && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za084000 
cd ../ && echo "84000 $EEDL_DATA_PATH/Po" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/At" ]; then 
echo "$EEDL_DATA_PATH/At already exists" 
else 
mkdir At && cd At && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za085000 
cd ../ && echo "85000 $EEDL_DATA_PATH/At" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Rn" ]; then 
echo "$EEDL_DATA_PATH/Rn already exists" 
else 
mkdir Rn && cd Rn && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za086000 
cd ../ && echo "86000 $EEDL_DATA_PATH/Rn" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Fr" ]; then 
echo "$EEDL_DATA_PATH/Fr already exists" 
else 
mkdir Fr && cd Fr && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za087000 
cd ../ && echo "87000 $EEDL_DATA_PATH/Fr" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Ra" ]; then 
echo "$EEDL_DATA_PATH/Ra already exists" 
else 
mkdir Ra && cd Ra && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za088000 
cd ../ && echo "88000 $EEDL_DATA_PATH/Ra" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Ac" ]; then 
echo "$EEDL_DATA_PATH/Ac already exists" 
else 
mkdir Ac && cd Ac && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za089000 
cd ../ && echo "89000 $EEDL_DATA_PATH/Ac" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Th" ]; then 
echo "$EEDL_DATA_PATH/Th already exists" 
else 
mkdir Th && cd Th && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za090000 
cd ../ && echo "90000 $EEDL_DATA_PATH/Th" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Pa" ]; then 
echo "$EEDL_DATA_PATH/Pa already exists" 
else 
mkdir Pa && cd Pa && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za091000 
cd ../ && echo "91000 $EEDL_DATA_PATH/Pa" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/U" ]; then 
echo "$EEDL_DATA_PATH/U already exists" 
else 
mkdir U && cd U && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za092000 
cd ../ && echo "92000 $EEDL_DATA_PATH/U" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Np" ]; then 
echo "$EEDL_DATA_PATH/Np already exists" 
else 
mkdir Np && cd Np && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za093000 
cd ../ && echo "93000 $EEDL_DATA_PATH/Np" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Pu" ]; then 
echo "$EEDL_DATA_PATH/Pu already exists" 
else 
mkdir Pu && cd Pu && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za094000 
cd ../ && echo "94000 $EEDL_DATA_PATH/Pu" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Am" ]; then 
echo "$EEDL_DATA_PATH/Am already exists" 
else 
mkdir Am && cd Am && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za095000 
cd ../ && echo "95000 $EEDL_DATA_PATH/Am" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Cm" ]; then 
echo "$EEDL_DATA_PATH/Cm already exists" 
else 
mkdir Cm && cd Cm && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za096000 
cd ../ && echo "96000 $EEDL_DATA_PATH/Cm" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Bk" ]; then 
echo "$EEDL_DATA_PATH/Bk already exists" 
else 
mkdir Bk && cd Bk && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za097000 
cd ../ && echo "97000 $EEDL_DATA_PATH/Bk" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Cf" ]; then 
echo "$EEDL_DATA_PATH/Cf already exists" 
else 
mkdir Cf && cd Cf && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za098000 
cd ../ && echo "98000 $EEDL_DATA_PATH/Cf" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Es" ]; then 
echo "$EEDL_DATA_PATH/Es already exists" 
else 
mkdir Es && cd Es && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za099000 
cd ../ && echo "99000 $EEDL_DATA_PATH/Es" >> xsdir.txt 
fi 
 
if [ -d "$EEDL_DATA_PATH/Fm" ]; then 
echo "$EEDL_DATA_PATH/Fm already exists" 
else 
mkdir Fm && cd Fm && wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za100000 
cd ../ && echo "100000 $EEDL_DATA_PATH/Fm" >> xsdir.txt 
fi 
 
