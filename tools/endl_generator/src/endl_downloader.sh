#!/bin/bash
##---------------------------------------------------------------------------##
## ENDL Data Downloader
##---------------------------------------------------------------------------##

# Set data directory path.
#echo -n "Enter cross_section.xml directory: > "
#read cross_section_directory
while getopts d: option
do case "${option}"
in
d) cross_section_directory=${OPTARG};;
esac
done
if [ -d "$cross_section_directory" ]; then
  cd $cross_section_directory

  if [ ! -d ./endldata ]; then
    mkdir ./endldata
  fi

  cd ./endldata

  if [ ! -d ./eadl ]; then
    mkdir eadl
  fi

  if [ ! -d ./epdl ]; then
    mkdir epdl
  fi

  if [ ! -d ./eedl ]; then
    mkdir eedl
  fi

  printf "Getting za001000 data:\t"
  if [ -f ./eadl/za001000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za001000
    cd ../
  fi

  if [ -f ./epdl/za001000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za001000
    cd ../
  fi

  if [ -f ./eedl/za001000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za001000
    cd ../
  fi

  printf "Getting za002000 data:\t"
  if [ -f ./eadl/za002000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za002000
    cd ../
  fi

  if [ -f ./epdl/za002000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za002000
    cd ../
  fi

  if [ -f ./eedl/za002000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za002000
    cd ../
  fi

  printf "Getting za003000 data:\t"
  if [ -f ./eadl/za003000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za003000
    cd ../
  fi

  if [ -f ./epdl/za003000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za003000
    cd ../
  fi

  if [ -f ./eedl/za003000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za003000
    cd ../
  fi

  printf "Getting za004000 data:\t"
  if [ -f ./eadl/za004000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za004000
    cd ../
  fi

  if [ -f ./epdl/za004000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za004000
    cd ../
  fi

  if [ -f ./eedl/za004000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za004000
    cd ../
  fi

  printf "Getting za005000 data:\t"
  if [ -f ./eadl/za005000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za005000
    cd ../
  fi

  if [ -f ./epdl/za005000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za005000
    cd ../
  fi

  if [ -f ./eedl/za005000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za005000
    cd ../
  fi

  printf "Getting za006000 data:\t"
  if [ -f ./eadl/za006000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za006000
    cd ../
  fi

  if [ -f ./epdl/za006000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za006000
    cd ../
  fi

  if [ -f ./eedl/za006000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za006000
    cd ../
  fi

  printf "Getting za007000 data:\t"
  if [ -f ./eadl/za007000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za007000
    cd ../
  fi

  if [ -f ./epdl/za007000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za007000
    cd ../
  fi

  if [ -f ./eedl/za007000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za007000
    cd ../
  fi

  printf "Getting za008000 data:\t"
  if [ -f ./eadl/za008000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za008000
    cd ../
  fi

  if [ -f ./epdl/za008000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za008000
    cd ../
  fi

  if [ -f ./eedl/za008000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za008000
    cd ../
  fi

  printf "Getting za009000 data:\t"
  if [ -f ./eadl/za009000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za009000
    cd ../
  fi

  if [ -f ./epdl/za009000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za009000
    cd ../
  fi

  if [ -f ./eedl/za009000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za009000
    cd ../
  fi

  printf "Getting za010000 data:\t"
  if [ -f ./eadl/za010000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za010000
    cd ../
  fi

  if [ -f ./epdl/za010000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za010000
    cd ../
  fi

  if [ -f ./eedl/za010000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za010000
    cd ../
  fi

  printf "Getting za011000 data:\t"
  if [ -f ./eadl/za011000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za011000
    cd ../
  fi

  if [ -f ./epdl/za011000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za011000
    cd ../
  fi

  if [ -f ./eedl/za011000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za011000
    cd ../
  fi

  printf "Getting za012000 data:\t"
  if [ -f ./eadl/za012000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za012000
    cd ../
  fi

  if [ -f ./epdl/za012000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za012000
    cd ../
  fi

  if [ -f ./eedl/za012000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za012000
    cd ../
  fi

  printf "Getting za013000 data:\t"
  if [ -f ./eadl/za013000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za013000
    cd ../
  fi

  if [ -f ./epdl/za013000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za013000
    cd ../
  fi

  if [ -f ./eedl/za013000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za013000
    cd ../
  fi

  printf "Getting za014000 data:\t"
  if [ -f ./eadl/za014000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za014000
    cd ../
  fi

  if [ -f ./epdl/za014000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za014000
    cd ../
  fi

  if [ -f ./eedl/za014000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za014000
    cd ../
  fi

  printf "Getting za015000 data:\t"
  if [ -f ./eadl/za015000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za015000
    cd ../
  fi

  if [ -f ./epdl/za015000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za015000
    cd ../
  fi

  if [ -f ./eedl/za015000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za015000
    cd ../
  fi

  printf "Getting za016000 data:\t"
  if [ -f ./eadl/za016000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za016000
    cd ../
  fi

  if [ -f ./epdl/za016000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za016000
    cd ../
  fi

  if [ -f ./eedl/za016000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za016000
    cd ../
  fi

  printf "Getting za017000 data:\t"
  if [ -f ./eadl/za017000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za017000
    cd ../
  fi

  if [ -f ./epdl/za017000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za017000
    cd ../
  fi

  if [ -f ./eedl/za017000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za017000
    cd ../
  fi

  printf "Getting za018000 data:\t"
  if [ -f ./eadl/za018000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za018000
    cd ../
  fi

  if [ -f ./epdl/za018000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za018000
    cd ../
  fi

  if [ -f ./eedl/za018000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za018000
    cd ../
  fi

  printf "Getting za019000 data:\t"
  if [ -f ./eadl/za019000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za019000
    cd ../
  fi

  if [ -f ./epdl/za019000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za019000
    cd ../
  fi

  if [ -f ./eedl/za019000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za019000
    cd ../
  fi

  printf "Getting za020000 data:\t"
  if [ -f ./eadl/za020000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za020000
    cd ../
  fi

  if [ -f ./epdl/za020000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za020000
    cd ../
  fi

  if [ -f ./eedl/za020000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za020000
    cd ../
  fi

  printf "Getting za021000 data:\t"
  if [ -f ./eadl/za021000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za021000
    cd ../
  fi

  if [ -f ./epdl/za021000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za021000
    cd ../
  fi

  if [ -f ./eedl/za021000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za021000
    cd ../
  fi

  printf "Getting za022000 data:\t"
  if [ -f ./eadl/za022000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za022000
    cd ../
  fi

  if [ -f ./epdl/za022000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za022000
    cd ../
  fi

  if [ -f ./eedl/za022000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za022000
    cd ../
  fi

  printf "Getting za023000 data:\t"
  if [ -f ./eadl/za023000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za023000
    cd ../
  fi

  if [ -f ./epdl/za023000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za023000
    cd ../
  fi

  if [ -f ./eedl/za023000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za023000
    cd ../
  fi

  printf "Getting za024000 data:\t"
  if [ -f ./eadl/za024000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za024000
    cd ../
  fi

  if [ -f ./epdl/za024000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za024000
    cd ../
  fi

  if [ -f ./eedl/za024000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za024000
    cd ../
  fi

  printf "Getting za025000 data:\t"
  if [ -f ./eadl/za025000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za025000
    cd ../
  fi

  if [ -f ./epdl/za025000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za025000
    cd ../
  fi

  if [ -f ./eedl/za025000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za025000
    cd ../
  fi

  printf "Getting za026000 data:\t"
  if [ -f ./eadl/za026000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za026000
    cd ../
  fi

  if [ -f ./epdl/za026000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za026000
    cd ../
  fi

  if [ -f ./eedl/za026000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za026000
    cd ../
  fi

  printf "Getting za027000 data:\t"
  if [ -f ./eadl/za027000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za027000
    cd ../
  fi

  if [ -f ./epdl/za027000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za027000
    cd ../
  fi

  if [ -f ./eedl/za027000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za027000
    cd ../
  fi

  printf "Getting za028000 data:\t"
  if [ -f ./eadl/za028000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za028000
    cd ../
  fi

  if [ -f ./epdl/za028000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za028000
    cd ../
  fi

  if [ -f ./eedl/za028000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za028000
    cd ../
  fi

  printf "Getting za029000 data:\t"
  if [ -f ./eadl/za029000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za029000
    cd ../
  fi

  if [ -f ./epdl/za029000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za029000
    cd ../
  fi

  if [ -f ./eedl/za029000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za029000
    cd ../
  fi

  printf "Getting za030000 data:\t"
  if [ -f ./eadl/za030000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za030000
    cd ../
  fi

  if [ -f ./epdl/za030000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za030000
    cd ../
  fi

  if [ -f ./eedl/za030000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za030000
    cd ../
  fi

  printf "Getting za031000 data:\t"
  if [ -f ./eadl/za031000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za031000
    cd ../
  fi

  if [ -f ./epdl/za031000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za031000
    cd ../
  fi

  if [ -f ./eedl/za031000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za031000
    cd ../
  fi

  printf "Getting za032000 data:\t"
  if [ -f ./eadl/za032000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za032000
    cd ../
  fi

  if [ -f ./epdl/za032000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za032000
    cd ../
  fi

  if [ -f ./eedl/za032000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za032000
    cd ../
  fi

  printf "Getting za033000 data:\t"
  if [ -f ./eadl/za033000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za033000
    cd ../
  fi

  if [ -f ./epdl/za033000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za033000
    cd ../
  fi

  if [ -f ./eedl/za033000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za033000
    cd ../
  fi

  printf "Getting za034000 data:\t"
  if [ -f ./eadl/za034000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za034000
    cd ../
  fi

  if [ -f ./epdl/za034000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za034000
    cd ../
  fi

  if [ -f ./eedl/za034000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za034000
    cd ../
  fi

  printf "Getting za035000 data:\t"
  if [ -f ./eadl/za035000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za035000
    cd ../
  fi

  if [ -f ./epdl/za035000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za035000
    cd ../
  fi

  if [ -f ./eedl/za035000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za035000
    cd ../
  fi

  printf "Getting za036000 data:\t"
  if [ -f ./eadl/za036000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za036000
    cd ../
  fi

  if [ -f ./epdl/za036000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za036000
    cd ../
  fi

  if [ -f ./eedl/za036000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za036000
    cd ../
  fi

  printf "Getting za037000 data:\t"
  if [ -f ./eadl/za037000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za037000
    cd ../
  fi

  if [ -f ./epdl/za037000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za037000
    cd ../
  fi

  if [ -f ./eedl/za037000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za037000
    cd ../
  fi

  printf "Getting za038000 data:\t"
  if [ -f ./eadl/za038000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za038000
    cd ../
  fi

  if [ -f ./epdl/za038000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za038000
    cd ../
  fi

  if [ -f ./eedl/za038000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za038000
    cd ../
  fi

  printf "Getting za039000 data:\t"
  if [ -f ./eadl/za039000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za039000
    cd ../
  fi

  if [ -f ./epdl/za039000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za039000
    cd ../
  fi

  if [ -f ./eedl/za039000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za039000
    cd ../
  fi

  printf "Getting za040000 data:\t"
  if [ -f ./eadl/za040000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za040000
    cd ../
  fi

  if [ -f ./epdl/za040000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za040000
    cd ../
  fi

  if [ -f ./eedl/za040000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za040000
    cd ../
  fi

  printf "Getting za041000 data:\t"
  if [ -f ./eadl/za041000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za041000
    cd ../
  fi

  if [ -f ./epdl/za041000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za041000
    cd ../
  fi

  if [ -f ./eedl/za041000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za041000
    cd ../
  fi

  printf "Getting za042000 data:\t"
  if [ -f ./eadl/za042000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za042000
    cd ../
  fi

  if [ -f ./epdl/za042000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za042000
    cd ../
  fi

  if [ -f ./eedl/za042000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za042000
    cd ../
  fi

  printf "Getting za043000 data:\t"
  if [ -f ./eadl/za043000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za043000
    cd ../
  fi

  if [ -f ./epdl/za043000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za043000
    cd ../
  fi

  if [ -f ./eedl/za043000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za043000
    cd ../
  fi

  printf "Getting za044000 data:\t"
  if [ -f ./eadl/za044000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za044000
    cd ../
  fi

  if [ -f ./epdl/za044000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za044000
    cd ../
  fi

  if [ -f ./eedl/za044000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za044000
    cd ../
  fi

  printf "Getting za045000 data:\t"
  if [ -f ./eadl/za045000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za045000
    cd ../
  fi

  if [ -f ./epdl/za045000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za045000
    cd ../
  fi

  if [ -f ./eedl/za045000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za045000
    cd ../
  fi

  printf "Getting za046000 data:\t"
  if [ -f ./eadl/za046000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za046000
    cd ../
  fi

  if [ -f ./epdl/za046000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za046000
    cd ../
  fi

  if [ -f ./eedl/za046000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za046000
    cd ../
  fi

  printf "Getting za047000 data:\t"
  if [ -f ./eadl/za047000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za047000
    cd ../
  fi

  if [ -f ./epdl/za047000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za047000
    cd ../
  fi

  if [ -f ./eedl/za047000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za047000
    cd ../
  fi

  printf "Getting za048000 data:\t"
  if [ -f ./eadl/za048000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za048000
    cd ../
  fi

  if [ -f ./epdl/za048000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za048000
    cd ../
  fi

  if [ -f ./eedl/za048000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za048000
    cd ../
  fi

  printf "Getting za049000 data:\t"
  if [ -f ./eadl/za049000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za049000
    cd ../
  fi

  if [ -f ./epdl/za049000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za049000
    cd ../
  fi

  if [ -f ./eedl/za049000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za049000
    cd ../
  fi

  printf "Getting za050000 data:\t"
  if [ -f ./eadl/za050000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za050000
    cd ../
  fi

  if [ -f ./epdl/za050000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za050000
    cd ../
  fi

  if [ -f ./eedl/za050000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za050000
    cd ../
  fi

  printf "Getting za051000 data:\t"
  if [ -f ./eadl/za051000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za051000
    cd ../
  fi

  if [ -f ./epdl/za051000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za051000
    cd ../
  fi

  if [ -f ./eedl/za051000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za051000
    cd ../
  fi

  printf "Getting za052000 data:\t"
  if [ -f ./eadl/za052000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za052000
    cd ../
  fi

  if [ -f ./epdl/za052000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za052000
    cd ../
  fi

  if [ -f ./eedl/za052000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za052000
    cd ../
  fi

  printf "Getting za053000 data:\t"
  if [ -f ./eadl/za053000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za053000
    cd ../
  fi

  if [ -f ./epdl/za053000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za053000
    cd ../
  fi

  if [ -f ./eedl/za053000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za053000
    cd ../
  fi

  printf "Getting za054000 data:\t"
  if [ -f ./eadl/za054000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za054000
    cd ../
  fi

  if [ -f ./epdl/za054000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za054000
    cd ../
  fi

  if [ -f ./eedl/za054000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za054000
    cd ../
  fi

  printf "Getting za055000 data:\t"
  if [ -f ./eadl/za055000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za055000
    cd ../
  fi

  if [ -f ./epdl/za055000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za055000
    cd ../
  fi

  if [ -f ./eedl/za055000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za055000
    cd ../
  fi

  printf "Getting za056000 data:\t"
  if [ -f ./eadl/za056000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za056000
    cd ../
  fi

  if [ -f ./epdl/za056000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za056000
    cd ../
  fi

  if [ -f ./eedl/za056000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za056000
    cd ../
  fi

  printf "Getting za057000 data:\t"
  if [ -f ./eadl/za057000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za057000
    cd ../
  fi

  if [ -f ./epdl/za057000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za057000
    cd ../
  fi

  if [ -f ./eedl/za057000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za057000
    cd ../
  fi

  printf "Getting za058000 data:\t"
  if [ -f ./eadl/za058000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za058000
    cd ../
  fi

  if [ -f ./epdl/za058000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za058000
    cd ../
  fi

  if [ -f ./eedl/za058000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za058000
    cd ../
  fi

  printf "Getting za059000 data:\t"
  if [ -f ./eadl/za059000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za059000
    cd ../
  fi

  if [ -f ./epdl/za059000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za059000
    cd ../
  fi

  if [ -f ./eedl/za059000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za059000
    cd ../
  fi

  printf "Getting za060000 data:\t"
  if [ -f ./eadl/za060000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za060000
    cd ../
  fi

  if [ -f ./epdl/za060000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za060000
    cd ../
  fi

  if [ -f ./eedl/za060000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za060000
    cd ../
  fi

  printf "Getting za061000 data:\t"
  if [ -f ./eadl/za061000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za061000
    cd ../
  fi

  if [ -f ./epdl/za061000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za061000
    cd ../
  fi

  if [ -f ./eedl/za061000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za061000
    cd ../
  fi

  printf "Getting za062000 data:\t"
  if [ -f ./eadl/za062000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za062000
    cd ../
  fi

  if [ -f ./epdl/za062000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za062000
    cd ../
  fi

  if [ -f ./eedl/za062000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za062000
    cd ../
  fi

  printf "Getting za063000 data:\t"
  if [ -f ./eadl/za063000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za063000
    cd ../
  fi

  if [ -f ./epdl/za063000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za063000
    cd ../
  fi

  if [ -f ./eedl/za063000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za063000
    cd ../
  fi

  printf "Getting za064000 data:\t"
  if [ -f ./eadl/za064000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za064000
    cd ../
  fi

  if [ -f ./epdl/za064000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za064000
    cd ../
  fi

  if [ -f ./eedl/za064000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za064000
    cd ../
  fi

  printf "Getting za065000 data:\t"
  if [ -f ./eadl/za065000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za065000
    cd ../
  fi

  if [ -f ./epdl/za065000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za065000
    cd ../
  fi

  if [ -f ./eedl/za065000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za065000
    cd ../
  fi

  printf "Getting za066000 data:\t"
  if [ -f ./eadl/za066000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za066000
    cd ../
  fi

  if [ -f ./epdl/za066000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za066000
    cd ../
  fi

  if [ -f ./eedl/za066000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za066000
    cd ../
  fi

  printf "Getting za067000 data:\t"
  if [ -f ./eadl/za067000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za067000
    cd ../
  fi

  if [ -f ./epdl/za067000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za067000
    cd ../
  fi

  if [ -f ./eedl/za067000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za067000
    cd ../
  fi

  printf "Getting za068000 data:\t"
  if [ -f ./eadl/za068000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za068000
    cd ../
  fi

  if [ -f ./epdl/za068000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za068000
    cd ../
  fi

  if [ -f ./eedl/za068000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za068000
    cd ../
  fi

  printf "Getting za069000 data:\t"
  if [ -f ./eadl/za069000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za069000
    cd ../
  fi

  if [ -f ./epdl/za069000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za069000
    cd ../
  fi

  if [ -f ./eedl/za069000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za069000
    cd ../
  fi

  printf "Getting za070000 data:\t"
  if [ -f ./eadl/za070000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za070000
    cd ../
  fi

  if [ -f ./epdl/za070000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za070000
    cd ../
  fi

  if [ -f ./eedl/za070000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za070000
    cd ../
  fi

  printf "Getting za071000 data:\t"
  if [ -f ./eadl/za071000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za071000
    cd ../
  fi

  if [ -f ./epdl/za071000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za071000
    cd ../
  fi

  if [ -f ./eedl/za071000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za071000
    cd ../
  fi

  printf "Getting za072000 data:\t"
  if [ -f ./eadl/za072000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za072000
    cd ../
  fi

  if [ -f ./epdl/za072000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za072000
    cd ../
  fi

  if [ -f ./eedl/za072000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za072000
    cd ../
  fi

  printf "Getting za073000 data:\t"
  if [ -f ./eadl/za073000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za073000
    cd ../
  fi

  if [ -f ./epdl/za073000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za073000
    cd ../
  fi

  if [ -f ./eedl/za073000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za073000
    cd ../
  fi

  printf "Getting za074000 data:\t"
  if [ -f ./eadl/za074000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za074000
    cd ../
  fi

  if [ -f ./epdl/za074000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za074000
    cd ../
  fi

  if [ -f ./eedl/za074000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za074000
    cd ../
  fi

  printf "Getting za075000 data:\t"
  if [ -f ./eadl/za075000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za075000
    cd ../
  fi

  if [ -f ./epdl/za075000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za075000
    cd ../
  fi

  if [ -f ./eedl/za075000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za075000
    cd ../
  fi

  printf "Getting za076000 data:\t"
  if [ -f ./eadl/za076000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za076000
    cd ../
  fi

  if [ -f ./epdl/za076000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za076000
    cd ../
  fi

  if [ -f ./eedl/za076000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za076000
    cd ../
  fi

  printf "Getting za077000 data:\t"
  if [ -f ./eadl/za077000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za077000
    cd ../
  fi

  if [ -f ./epdl/za077000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za077000
    cd ../
  fi

  if [ -f ./eedl/za077000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za077000
    cd ../
  fi

  printf "Getting za078000 data:\t"
  if [ -f ./eadl/za078000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za078000
    cd ../
  fi

  if [ -f ./epdl/za078000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za078000
    cd ../
  fi

  if [ -f ./eedl/za078000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za078000
    cd ../
  fi

  printf "Getting za079000 data:\t"
  if [ -f ./eadl/za079000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za079000
    cd ../
  fi

  if [ -f ./epdl/za079000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za079000
    cd ../
  fi

  if [ -f ./eedl/za079000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za079000
    cd ../
  fi

  printf "Getting za080000 data:\t"
  if [ -f ./eadl/za080000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za080000
    cd ../
  fi

  if [ -f ./epdl/za080000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za080000
    cd ../
  fi

  if [ -f ./eedl/za080000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za080000
    cd ../
  fi

  printf "Getting za081000 data:\t"
  if [ -f ./eadl/za081000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za081000
    cd ../
  fi

  if [ -f ./epdl/za081000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za081000
    cd ../
  fi

  if [ -f ./eedl/za081000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za081000
    cd ../
  fi

  printf "Getting za082000 data:\t"
  if [ -f ./eadl/za082000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za082000
    cd ../
  fi

  if [ -f ./epdl/za082000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za082000
    cd ../
  fi

  if [ -f ./eedl/za082000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za082000
    cd ../
  fi

  printf "Getting za083000 data:\t"
  if [ -f ./eadl/za083000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za083000
    cd ../
  fi

  if [ -f ./epdl/za083000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za083000
    cd ../
  fi

  if [ -f ./eedl/za083000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za083000
    cd ../
  fi

  printf "Getting za084000 data:\t"
  if [ -f ./eadl/za084000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za084000
    cd ../
  fi

  if [ -f ./epdl/za084000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za084000
    cd ../
  fi

  if [ -f ./eedl/za084000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za084000
    cd ../
  fi

  printf "Getting za085000 data:\t"
  if [ -f ./eadl/za085000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za085000
    cd ../
  fi

  if [ -f ./epdl/za085000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za085000
    cd ../
  fi

  if [ -f ./eedl/za085000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za085000
    cd ../
  fi

  printf "Getting za086000 data:\t"
  if [ -f ./eadl/za086000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za086000
    cd ../
  fi

  if [ -f ./epdl/za086000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za086000
    cd ../
  fi

  if [ -f ./eedl/za086000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za086000
    cd ../
  fi

  printf "Getting za087000 data:\t"
  if [ -f ./eadl/za087000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za087000
    cd ../
  fi

  if [ -f ./epdl/za087000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za087000
    cd ../
  fi

  if [ -f ./eedl/za087000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za087000
    cd ../
  fi

  printf "Getting za088000 data:\t"
  if [ -f ./eadl/za088000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za088000
    cd ../
  fi

  if [ -f ./epdl/za088000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za088000
    cd ../
  fi

  if [ -f ./eedl/za088000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za088000
    cd ../
  fi

  printf "Getting za089000 data:\t"
  if [ -f ./eadl/za089000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za089000
    cd ../
  fi

  if [ -f ./epdl/za089000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za089000
    cd ../
  fi

  if [ -f ./eedl/za089000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za089000
    cd ../
  fi

  printf "Getting za090000 data:\t"
  if [ -f ./eadl/za090000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za090000
    cd ../
  fi

  if [ -f ./epdl/za090000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za090000
    cd ../
  fi

  if [ -f ./eedl/za090000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za090000
    cd ../
  fi

  printf "Getting za091000 data:\t"
  if [ -f ./eadl/za091000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za091000
    cd ../
  fi

  if [ -f ./epdl/za091000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za091000
    cd ../
  fi

  if [ -f ./eedl/za091000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za091000
    cd ../
  fi

  printf "Getting za092000 data:\t"
  if [ -f ./eadl/za092000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za092000
    cd ../
  fi

  if [ -f ./epdl/za092000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za092000
    cd ../
  fi

  if [ -f ./eedl/za092000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za092000
    cd ../
  fi

  printf "Getting za093000 data:\t"
  if [ -f ./eadl/za093000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za093000
    cd ../
  fi

  if [ -f ./epdl/za093000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za093000
    cd ../
  fi

  if [ -f ./eedl/za093000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za093000
    cd ../
  fi

  printf "Getting za094000 data:\t"
  if [ -f ./eadl/za094000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za094000
    cd ../
  fi

  if [ -f ./epdl/za094000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za094000
    cd ../
  fi

  if [ -f ./eedl/za094000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za094000
    cd ../
  fi

  printf "Getting za095000 data:\t"
  if [ -f ./eadl/za095000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za095000
    cd ../
  fi

  if [ -f ./epdl/za095000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za095000
    cd ../
  fi

  if [ -f ./eedl/za095000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za095000
    cd ../
  fi

  printf "Getting za096000 data:\t"
  if [ -f ./eadl/za096000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za096000
    cd ../
  fi

  if [ -f ./epdl/za096000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za096000
    cd ../
  fi

  if [ -f ./eedl/za096000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za096000
    cd ../
  fi

  printf "Getting za097000 data:\t"
  if [ -f ./eadl/za097000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za097000
    cd ../
  fi

  if [ -f ./epdl/za097000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za097000
    cd ../
  fi

  if [ -f ./eedl/za097000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za097000
    cd ../
  fi

  printf "Getting za098000 data:\t"
  if [ -f ./eadl/za098000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za098000
    cd ../
  fi

  if [ -f ./epdl/za098000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za098000
    cd ../
  fi

  if [ -f ./eedl/za098000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za098000
    cd ../
  fi

  printf "Getting za099000 data:\t"
  if [ -f ./eadl/za099000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za099000
    cd ../
  fi

  if [ -f ./epdl/za099000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za099000
    cd ../
  fi

  if [ -f ./eedl/za099000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za099000
    cd ../
  fi

  printf "Getting za100000 data:\t"
  if [ -f ./eadl/za100000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/za100000
    cd ../
  fi

  if [ -f ./epdl/za100000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/za100000
    cd ../
  fi

  if [ -f ./eedl/za100000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/za100000
    cd ../
  fi

  printf "\nThe ENDL Library has been downloaded!\n"
  printf "To process the ENDL Library into an xml format run the endltoxml tool!\n\n"
  printf "  endltoxml --cross_sec_dir=$cross_section_directory\n\n"
else
  printf "\nERROR: Invalid cross_section_directory!\n"
  printf "\nERROR: Invalid cross_section_directory!\n"
  printf "  endl_downloader.sh -d cross_section_directory\n\n"
fi

