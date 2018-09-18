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

  printf "Getting ZA001000 data:\t"
  if [ -f ./eadl/ZA001000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA001000
    cd ../
  fi

  if [ -f ./epdl/ZA001000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA001000
    cd ../
  fi

  if [ -f ./eedl/ZA001000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA001000
    cd ../
  fi

  printf "Getting ZA002000 data:\t"
  if [ -f ./eadl/ZA002000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA002000
    cd ../
  fi

  if [ -f ./epdl/ZA002000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA002000
    cd ../
  fi

  if [ -f ./eedl/ZA002000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA002000
    cd ../
  fi

  printf "Getting ZA003000 data:\t"
  if [ -f ./eadl/ZA003000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA003000
    cd ../
  fi

  if [ -f ./epdl/ZA003000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA003000
    cd ../
  fi

  if [ -f ./eedl/ZA003000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA003000
    cd ../
  fi

  printf "Getting ZA004000 data:\t"
  if [ -f ./eadl/ZA004000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA004000
    cd ../
  fi

  if [ -f ./epdl/ZA004000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA004000
    cd ../
  fi

  if [ -f ./eedl/ZA004000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA004000
    cd ../
  fi

  printf "Getting ZA005000 data:\t"
  if [ -f ./eadl/ZA005000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA005000
    cd ../
  fi

  if [ -f ./epdl/ZA005000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA005000
    cd ../
  fi

  if [ -f ./eedl/ZA005000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA005000
    cd ../
  fi

  printf "Getting ZA006000 data:\t"
  if [ -f ./eadl/ZA006000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA006000
    cd ../
  fi

  if [ -f ./epdl/ZA006000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA006000
    cd ../
  fi

  if [ -f ./eedl/ZA006000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA006000
    cd ../
  fi

  printf "Getting ZA007000 data:\t"
  if [ -f ./eadl/ZA007000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA007000
    cd ../
  fi

  if [ -f ./epdl/ZA007000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA007000
    cd ../
  fi

  if [ -f ./eedl/ZA007000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA007000
    cd ../
  fi

  printf "Getting ZA008000 data:\t"
  if [ -f ./eadl/ZA008000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA008000
    cd ../
  fi

  if [ -f ./epdl/ZA008000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA008000
    cd ../
  fi

  if [ -f ./eedl/ZA008000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA008000
    cd ../
  fi

  printf "Getting ZA009000 data:\t"
  if [ -f ./eadl/ZA009000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA009000
    cd ../
  fi

  if [ -f ./epdl/ZA009000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA009000
    cd ../
  fi

  if [ -f ./eedl/ZA009000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA009000
    cd ../
  fi

  printf "Getting ZA010000 data:\t"
  if [ -f ./eadl/ZA010000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA010000
    cd ../
  fi

  if [ -f ./epdl/ZA010000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA010000
    cd ../
  fi

  if [ -f ./eedl/ZA010000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA010000
    cd ../
  fi

  printf "Getting ZA011000 data:\t"
  if [ -f ./eadl/ZA011000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA011000
    cd ../
  fi

  if [ -f ./epdl/ZA011000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA011000
    cd ../
  fi

  if [ -f ./eedl/ZA011000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA011000
    cd ../
  fi

  printf "Getting ZA012000 data:\t"
  if [ -f ./eadl/ZA012000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA012000
    cd ../
  fi

  if [ -f ./epdl/ZA012000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA012000
    cd ../
  fi

  if [ -f ./eedl/ZA012000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA012000
    cd ../
  fi

  printf "Getting ZA013000 data:\t"
  if [ -f ./eadl/ZA013000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA013000
    cd ../
  fi

  if [ -f ./epdl/ZA013000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA013000
    cd ../
  fi

  if [ -f ./eedl/ZA013000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA013000
    cd ../
  fi

  printf "Getting ZA014000 data:\t"
  if [ -f ./eadl/ZA014000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA014000
    cd ../
  fi

  if [ -f ./epdl/ZA014000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA014000
    cd ../
  fi

  if [ -f ./eedl/ZA014000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA014000
    cd ../
  fi

  printf "Getting ZA015000 data:\t"
  if [ -f ./eadl/ZA015000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA015000
    cd ../
  fi

  if [ -f ./epdl/ZA015000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA015000
    cd ../
  fi

  if [ -f ./eedl/ZA015000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA015000
    cd ../
  fi

  printf "Getting ZA016000 data:\t"
  if [ -f ./eadl/ZA016000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA016000
    cd ../
  fi

  if [ -f ./epdl/ZA016000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA016000
    cd ../
  fi

  if [ -f ./eedl/ZA016000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA016000
    cd ../
  fi

  printf "Getting ZA017000 data:\t"
  if [ -f ./eadl/ZA017000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA017000
    cd ../
  fi

  if [ -f ./epdl/ZA017000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA017000
    cd ../
  fi

  if [ -f ./eedl/ZA017000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA017000
    cd ../
  fi

  printf "Getting ZA018000 data:\t"
  if [ -f ./eadl/ZA018000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA018000
    cd ../
  fi

  if [ -f ./epdl/ZA018000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA018000
    cd ../
  fi

  if [ -f ./eedl/ZA018000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA018000
    cd ../
  fi

  printf "Getting ZA019000 data:\t"
  if [ -f ./eadl/ZA019000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA019000
    cd ../
  fi

  if [ -f ./epdl/ZA019000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA019000
    cd ../
  fi

  if [ -f ./eedl/ZA019000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA019000
    cd ../
  fi

  printf "Getting ZA020000 data:\t"
  if [ -f ./eadl/ZA020000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA020000
    cd ../
  fi

  if [ -f ./epdl/ZA020000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA020000
    cd ../
  fi

  if [ -f ./eedl/ZA020000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA020000
    cd ../
  fi

  printf "Getting ZA021000 data:\t"
  if [ -f ./eadl/ZA021000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA021000
    cd ../
  fi

  if [ -f ./epdl/ZA021000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA021000
    cd ../
  fi

  if [ -f ./eedl/ZA021000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA021000
    cd ../
  fi

  printf "Getting ZA022000 data:\t"
  if [ -f ./eadl/ZA022000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA022000
    cd ../
  fi

  if [ -f ./epdl/ZA022000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA022000
    cd ../
  fi

  if [ -f ./eedl/ZA022000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA022000
    cd ../
  fi

  printf "Getting ZA023000 data:\t"
  if [ -f ./eadl/ZA023000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA023000
    cd ../
  fi

  if [ -f ./epdl/ZA023000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA023000
    cd ../
  fi

  if [ -f ./eedl/ZA023000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA023000
    cd ../
  fi

  printf "Getting ZA024000 data:\t"
  if [ -f ./eadl/ZA024000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA024000
    cd ../
  fi

  if [ -f ./epdl/ZA024000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA024000
    cd ../
  fi

  if [ -f ./eedl/ZA024000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA024000
    cd ../
  fi

  printf "Getting ZA025000 data:\t"
  if [ -f ./eadl/ZA025000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA025000
    cd ../
  fi

  if [ -f ./epdl/ZA025000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA025000
    cd ../
  fi

  if [ -f ./eedl/ZA025000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA025000
    cd ../
  fi

  printf "Getting ZA026000 data:\t"
  if [ -f ./eadl/ZA026000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA026000
    cd ../
  fi

  if [ -f ./epdl/ZA026000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA026000
    cd ../
  fi

  if [ -f ./eedl/ZA026000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA026000
    cd ../
  fi

  printf "Getting ZA027000 data:\t"
  if [ -f ./eadl/ZA027000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA027000
    cd ../
  fi

  if [ -f ./epdl/ZA027000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA027000
    cd ../
  fi

  if [ -f ./eedl/ZA027000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA027000
    cd ../
  fi

  printf "Getting ZA028000 data:\t"
  if [ -f ./eadl/ZA028000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA028000
    cd ../
  fi

  if [ -f ./epdl/ZA028000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA028000
    cd ../
  fi

  if [ -f ./eedl/ZA028000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA028000
    cd ../
  fi

  printf "Getting ZA029000 data:\t"
  if [ -f ./eadl/ZA029000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA029000
    cd ../
  fi

  if [ -f ./epdl/ZA029000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA029000
    cd ../
  fi

  if [ -f ./eedl/ZA029000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA029000
    cd ../
  fi

  printf "Getting ZA030000 data:\t"
  if [ -f ./eadl/ZA030000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA030000
    cd ../
  fi

  if [ -f ./epdl/ZA030000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA030000
    cd ../
  fi

  if [ -f ./eedl/ZA030000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA030000
    cd ../
  fi

  printf "Getting ZA031000 data:\t"
  if [ -f ./eadl/ZA031000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA031000
    cd ../
  fi

  if [ -f ./epdl/ZA031000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA031000
    cd ../
  fi

  if [ -f ./eedl/ZA031000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA031000
    cd ../
  fi

  printf "Getting ZA032000 data:\t"
  if [ -f ./eadl/ZA032000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA032000
    cd ../
  fi

  if [ -f ./epdl/ZA032000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA032000
    cd ../
  fi

  if [ -f ./eedl/ZA032000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA032000
    cd ../
  fi

  printf "Getting ZA033000 data:\t"
  if [ -f ./eadl/ZA033000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA033000
    cd ../
  fi

  if [ -f ./epdl/ZA033000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA033000
    cd ../
  fi

  if [ -f ./eedl/ZA033000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA033000
    cd ../
  fi

  printf "Getting ZA034000 data:\t"
  if [ -f ./eadl/ZA034000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA034000
    cd ../
  fi

  if [ -f ./epdl/ZA034000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA034000
    cd ../
  fi

  if [ -f ./eedl/ZA034000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA034000
    cd ../
  fi

  printf "Getting ZA035000 data:\t"
  if [ -f ./eadl/ZA035000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA035000
    cd ../
  fi

  if [ -f ./epdl/ZA035000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA035000
    cd ../
  fi

  if [ -f ./eedl/ZA035000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA035000
    cd ../
  fi

  printf "Getting ZA036000 data:\t"
  if [ -f ./eadl/ZA036000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA036000
    cd ../
  fi

  if [ -f ./epdl/ZA036000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA036000
    cd ../
  fi

  if [ -f ./eedl/ZA036000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA036000
    cd ../
  fi

  printf "Getting ZA037000 data:\t"
  if [ -f ./eadl/ZA037000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA037000
    cd ../
  fi

  if [ -f ./epdl/ZA037000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA037000
    cd ../
  fi

  if [ -f ./eedl/ZA037000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA037000
    cd ../
  fi

  printf "Getting ZA038000 data:\t"
  if [ -f ./eadl/ZA038000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA038000
    cd ../
  fi

  if [ -f ./epdl/ZA038000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA038000
    cd ../
  fi

  if [ -f ./eedl/ZA038000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA038000
    cd ../
  fi

  printf "Getting ZA039000 data:\t"
  if [ -f ./eadl/ZA039000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA039000
    cd ../
  fi

  if [ -f ./epdl/ZA039000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA039000
    cd ../
  fi

  if [ -f ./eedl/ZA039000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA039000
    cd ../
  fi

  printf "Getting ZA040000 data:\t"
  if [ -f ./eadl/ZA040000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA040000
    cd ../
  fi

  if [ -f ./epdl/ZA040000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA040000
    cd ../
  fi

  if [ -f ./eedl/ZA040000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA040000
    cd ../
  fi

  printf "Getting ZA041000 data:\t"
  if [ -f ./eadl/ZA041000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA041000
    cd ../
  fi

  if [ -f ./epdl/ZA041000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA041000
    cd ../
  fi

  if [ -f ./eedl/ZA041000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA041000
    cd ../
  fi

  printf "Getting ZA042000 data:\t"
  if [ -f ./eadl/ZA042000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA042000
    cd ../
  fi

  if [ -f ./epdl/ZA042000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA042000
    cd ../
  fi

  if [ -f ./eedl/ZA042000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA042000
    cd ../
  fi

  printf "Getting ZA043000 data:\t"
  if [ -f ./eadl/ZA043000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA043000
    cd ../
  fi

  if [ -f ./epdl/ZA043000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA043000
    cd ../
  fi

  if [ -f ./eedl/ZA043000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA043000
    cd ../
  fi

  printf "Getting ZA044000 data:\t"
  if [ -f ./eadl/ZA044000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA044000
    cd ../
  fi

  if [ -f ./epdl/ZA044000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA044000
    cd ../
  fi

  if [ -f ./eedl/ZA044000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA044000
    cd ../
  fi

  printf "Getting ZA045000 data:\t"
  if [ -f ./eadl/ZA045000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA045000
    cd ../
  fi

  if [ -f ./epdl/ZA045000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA045000
    cd ../
  fi

  if [ -f ./eedl/ZA045000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA045000
    cd ../
  fi

  printf "Getting ZA046000 data:\t"
  if [ -f ./eadl/ZA046000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA046000
    cd ../
  fi

  if [ -f ./epdl/ZA046000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA046000
    cd ../
  fi

  if [ -f ./eedl/ZA046000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA046000
    cd ../
  fi

  printf "Getting ZA047000 data:\t"
  if [ -f ./eadl/ZA047000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA047000
    cd ../
  fi

  if [ -f ./epdl/ZA047000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA047000
    cd ../
  fi

  if [ -f ./eedl/ZA047000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA047000
    cd ../
  fi

  printf "Getting ZA048000 data:\t"
  if [ -f ./eadl/ZA048000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA048000
    cd ../
  fi

  if [ -f ./epdl/ZA048000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA048000
    cd ../
  fi

  if [ -f ./eedl/ZA048000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA048000
    cd ../
  fi

  printf "Getting ZA049000 data:\t"
  if [ -f ./eadl/ZA049000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA049000
    cd ../
  fi

  if [ -f ./epdl/ZA049000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA049000
    cd ../
  fi

  if [ -f ./eedl/ZA049000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA049000
    cd ../
  fi

  printf "Getting ZA050000 data:\t"
  if [ -f ./eadl/ZA050000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA050000
    cd ../
  fi

  if [ -f ./epdl/ZA050000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA050000
    cd ../
  fi

  if [ -f ./eedl/ZA050000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA050000
    cd ../
  fi

  printf "Getting ZA051000 data:\t"
  if [ -f ./eadl/ZA051000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA051000
    cd ../
  fi

  if [ -f ./epdl/ZA051000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA051000
    cd ../
  fi

  if [ -f ./eedl/ZA051000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA051000
    cd ../
  fi

  printf "Getting ZA052000 data:\t"
  if [ -f ./eadl/ZA052000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA052000
    cd ../
  fi

  if [ -f ./epdl/ZA052000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA052000
    cd ../
  fi

  if [ -f ./eedl/ZA052000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA052000
    cd ../
  fi

  printf "Getting ZA053000 data:\t"
  if [ -f ./eadl/ZA053000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA053000
    cd ../
  fi

  if [ -f ./epdl/ZA053000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA053000
    cd ../
  fi

  if [ -f ./eedl/ZA053000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA053000
    cd ../
  fi

  printf "Getting ZA054000 data:\t"
  if [ -f ./eadl/ZA054000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA054000
    cd ../
  fi

  if [ -f ./epdl/ZA054000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA054000
    cd ../
  fi

  if [ -f ./eedl/ZA054000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA054000
    cd ../
  fi

  printf "Getting ZA055000 data:\t"
  if [ -f ./eadl/ZA055000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA055000
    cd ../
  fi

  if [ -f ./epdl/ZA055000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA055000
    cd ../
  fi

  if [ -f ./eedl/ZA055000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA055000
    cd ../
  fi

  printf "Getting ZA056000 data:\t"
  if [ -f ./eadl/ZA056000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA056000
    cd ../
  fi

  if [ -f ./epdl/ZA056000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA056000
    cd ../
  fi

  if [ -f ./eedl/ZA056000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA056000
    cd ../
  fi

  printf "Getting ZA057000 data:\t"
  if [ -f ./eadl/ZA057000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA057000
    cd ../
  fi

  if [ -f ./epdl/ZA057000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA057000
    cd ../
  fi

  if [ -f ./eedl/ZA057000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA057000
    cd ../
  fi

  printf "Getting ZA058000 data:\t"
  if [ -f ./eadl/ZA058000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA058000
    cd ../
  fi

  if [ -f ./epdl/ZA058000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA058000
    cd ../
  fi

  if [ -f ./eedl/ZA058000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA058000
    cd ../
  fi

  printf "Getting ZA059000 data:\t"
  if [ -f ./eadl/ZA059000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA059000
    cd ../
  fi

  if [ -f ./epdl/ZA059000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA059000
    cd ../
  fi

  if [ -f ./eedl/ZA059000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA059000
    cd ../
  fi

  printf "Getting ZA060000 data:\t"
  if [ -f ./eadl/ZA060000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA060000
    cd ../
  fi

  if [ -f ./epdl/ZA060000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA060000
    cd ../
  fi

  if [ -f ./eedl/ZA060000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA060000
    cd ../
  fi

  printf "Getting ZA061000 data:\t"
  if [ -f ./eadl/ZA061000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA061000
    cd ../
  fi

  if [ -f ./epdl/ZA061000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA061000
    cd ../
  fi

  if [ -f ./eedl/ZA061000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA061000
    cd ../
  fi

  printf "Getting ZA062000 data:\t"
  if [ -f ./eadl/ZA062000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA062000
    cd ../
  fi

  if [ -f ./epdl/ZA062000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA062000
    cd ../
  fi

  if [ -f ./eedl/ZA062000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA062000
    cd ../
  fi

  printf "Getting ZA063000 data:\t"
  if [ -f ./eadl/ZA063000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA063000
    cd ../
  fi

  if [ -f ./epdl/ZA063000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA063000
    cd ../
  fi

  if [ -f ./eedl/ZA063000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA063000
    cd ../
  fi

  printf "Getting ZA064000 data:\t"
  if [ -f ./eadl/ZA064000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA064000
    cd ../
  fi

  if [ -f ./epdl/ZA064000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA064000
    cd ../
  fi

  if [ -f ./eedl/ZA064000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA064000
    cd ../
  fi

  printf "Getting ZA065000 data:\t"
  if [ -f ./eadl/ZA065000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA065000
    cd ../
  fi

  if [ -f ./epdl/ZA065000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA065000
    cd ../
  fi

  if [ -f ./eedl/ZA065000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA065000
    cd ../
  fi

  printf "Getting ZA066000 data:\t"
  if [ -f ./eadl/ZA066000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA066000
    cd ../
  fi

  if [ -f ./epdl/ZA066000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA066000
    cd ../
  fi

  if [ -f ./eedl/ZA066000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA066000
    cd ../
  fi

  printf "Getting ZA067000 data:\t"
  if [ -f ./eadl/ZA067000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA067000
    cd ../
  fi

  if [ -f ./epdl/ZA067000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA067000
    cd ../
  fi

  if [ -f ./eedl/ZA067000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA067000
    cd ../
  fi

  printf "Getting ZA068000 data:\t"
  if [ -f ./eadl/ZA068000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA068000
    cd ../
  fi

  if [ -f ./epdl/ZA068000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA068000
    cd ../
  fi

  if [ -f ./eedl/ZA068000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA068000
    cd ../
  fi

  printf "Getting ZA069000 data:\t"
  if [ -f ./eadl/ZA069000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA069000
    cd ../
  fi

  if [ -f ./epdl/ZA069000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA069000
    cd ../
  fi

  if [ -f ./eedl/ZA069000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA069000
    cd ../
  fi

  printf "Getting ZA070000 data:\t"
  if [ -f ./eadl/ZA070000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA070000
    cd ../
  fi

  if [ -f ./epdl/ZA070000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA070000
    cd ../
  fi

  if [ -f ./eedl/ZA070000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA070000
    cd ../
  fi

  printf "Getting ZA071000 data:\t"
  if [ -f ./eadl/ZA071000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA071000
    cd ../
  fi

  if [ -f ./epdl/ZA071000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA071000
    cd ../
  fi

  if [ -f ./eedl/ZA071000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA071000
    cd ../
  fi

  printf "Getting ZA072000 data:\t"
  if [ -f ./eadl/ZA072000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA072000
    cd ../
  fi

  if [ -f ./epdl/ZA072000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA072000
    cd ../
  fi

  if [ -f ./eedl/ZA072000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA072000
    cd ../
  fi

  printf "Getting ZA073000 data:\t"
  if [ -f ./eadl/ZA073000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA073000
    cd ../
  fi

  if [ -f ./epdl/ZA073000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA073000
    cd ../
  fi

  if [ -f ./eedl/ZA073000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA073000
    cd ../
  fi

  printf "Getting ZA074000 data:\t"
  if [ -f ./eadl/ZA074000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA074000
    cd ../
  fi

  if [ -f ./epdl/ZA074000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA074000
    cd ../
  fi

  if [ -f ./eedl/ZA074000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA074000
    cd ../
  fi

  printf "Getting ZA075000 data:\t"
  if [ -f ./eadl/ZA075000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA075000
    cd ../
  fi

  if [ -f ./epdl/ZA075000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA075000
    cd ../
  fi

  if [ -f ./eedl/ZA075000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA075000
    cd ../
  fi

  printf "Getting ZA076000 data:\t"
  if [ -f ./eadl/ZA076000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA076000
    cd ../
  fi

  if [ -f ./epdl/ZA076000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA076000
    cd ../
  fi

  if [ -f ./eedl/ZA076000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA076000
    cd ../
  fi

  printf "Getting ZA077000 data:\t"
  if [ -f ./eadl/ZA077000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA077000
    cd ../
  fi

  if [ -f ./epdl/ZA077000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA077000
    cd ../
  fi

  if [ -f ./eedl/ZA077000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA077000
    cd ../
  fi

  printf "Getting ZA078000 data:\t"
  if [ -f ./eadl/ZA078000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA078000
    cd ../
  fi

  if [ -f ./epdl/ZA078000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA078000
    cd ../
  fi

  if [ -f ./eedl/ZA078000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA078000
    cd ../
  fi

  printf "Getting ZA079000 data:\t"
  if [ -f ./eadl/ZA079000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA079000
    cd ../
  fi

  if [ -f ./epdl/ZA079000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA079000
    cd ../
  fi

  if [ -f ./eedl/ZA079000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA079000
    cd ../
  fi

  printf "Getting ZA080000 data:\t"
  if [ -f ./eadl/ZA080000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA080000
    cd ../
  fi

  if [ -f ./epdl/ZA080000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA080000
    cd ../
  fi

  if [ -f ./eedl/ZA080000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA080000
    cd ../
  fi

  printf "Getting ZA081000 data:\t"
  if [ -f ./eadl/ZA081000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA081000
    cd ../
  fi

  if [ -f ./epdl/ZA081000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA081000
    cd ../
  fi

  if [ -f ./eedl/ZA081000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA081000
    cd ../
  fi

  printf "Getting ZA082000 data:\t"
  if [ -f ./eadl/ZA082000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA082000
    cd ../
  fi

  if [ -f ./epdl/ZA082000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA082000
    cd ../
  fi

  if [ -f ./eedl/ZA082000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA082000
    cd ../
  fi

  printf "Getting ZA083000 data:\t"
  if [ -f ./eadl/ZA083000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA083000
    cd ../
  fi

  if [ -f ./epdl/ZA083000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA083000
    cd ../
  fi

  if [ -f ./eedl/ZA083000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA083000
    cd ../
  fi

  printf "Getting ZA084000 data:\t"
  if [ -f ./eadl/ZA084000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA084000
    cd ../
  fi

  if [ -f ./epdl/ZA084000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA084000
    cd ../
  fi

  if [ -f ./eedl/ZA084000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA084000
    cd ../
  fi

  printf "Getting ZA085000 data:\t"
  if [ -f ./eadl/ZA085000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA085000
    cd ../
  fi

  if [ -f ./epdl/ZA085000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA085000
    cd ../
  fi

  if [ -f ./eedl/ZA085000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA085000
    cd ../
  fi

  printf "Getting ZA086000 data:\t"
  if [ -f ./eadl/ZA086000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA086000
    cd ../
  fi

  if [ -f ./epdl/ZA086000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA086000
    cd ../
  fi

  if [ -f ./eedl/ZA086000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA086000
    cd ../
  fi

  printf "Getting ZA087000 data:\t"
  if [ -f ./eadl/ZA087000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA087000
    cd ../
  fi

  if [ -f ./epdl/ZA087000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA087000
    cd ../
  fi

  if [ -f ./eedl/ZA087000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA087000
    cd ../
  fi

  printf "Getting ZA088000 data:\t"
  if [ -f ./eadl/ZA088000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA088000
    cd ../
  fi

  if [ -f ./epdl/ZA088000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA088000
    cd ../
  fi

  if [ -f ./eedl/ZA088000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA088000
    cd ../
  fi

  printf "Getting ZA089000 data:\t"
  if [ -f ./eadl/ZA089000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA089000
    cd ../
  fi

  if [ -f ./epdl/ZA089000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA089000
    cd ../
  fi

  if [ -f ./eedl/ZA089000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA089000
    cd ../
  fi

  printf "Getting ZA090000 data:\t"
  if [ -f ./eadl/ZA090000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA090000
    cd ../
  fi

  if [ -f ./epdl/ZA090000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA090000
    cd ../
  fi

  if [ -f ./eedl/ZA090000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA090000
    cd ../
  fi

  printf "Getting ZA091000 data:\t"
  if [ -f ./eadl/ZA091000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA091000
    cd ../
  fi

  if [ -f ./epdl/ZA091000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA091000
    cd ../
  fi

  if [ -f ./eedl/ZA091000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA091000
    cd ../
  fi

  printf "Getting ZA092000 data:\t"
  if [ -f ./eadl/ZA092000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA092000
    cd ../
  fi

  if [ -f ./epdl/ZA092000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA092000
    cd ../
  fi

  if [ -f ./eedl/ZA092000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA092000
    cd ../
  fi

  printf "Getting ZA093000 data:\t"
  if [ -f ./eadl/ZA093000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA093000
    cd ../
  fi

  if [ -f ./epdl/ZA093000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA093000
    cd ../
  fi

  if [ -f ./eedl/ZA093000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA093000
    cd ../
  fi

  printf "Getting ZA094000 data:\t"
  if [ -f ./eadl/ZA094000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA094000
    cd ../
  fi

  if [ -f ./epdl/ZA094000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA094000
    cd ../
  fi

  if [ -f ./eedl/ZA094000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA094000
    cd ../
  fi

  printf "Getting ZA095000 data:\t"
  if [ -f ./eadl/ZA095000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA095000
    cd ../
  fi

  if [ -f ./epdl/ZA095000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA095000
    cd ../
  fi

  if [ -f ./eedl/ZA095000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA095000
    cd ../
  fi

  printf "Getting ZA096000 data:\t"
  if [ -f ./eadl/ZA096000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA096000
    cd ../
  fi

  if [ -f ./epdl/ZA096000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA096000
    cd ../
  fi

  if [ -f ./eedl/ZA096000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA096000
    cd ../
  fi

  printf "Getting ZA097000 data:\t"
  if [ -f ./eadl/ZA097000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA097000
    cd ../
  fi

  if [ -f ./epdl/ZA097000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA097000
    cd ../
  fi

  if [ -f ./eedl/ZA097000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA097000
    cd ../
  fi

  printf "Getting ZA098000 data:\t"
  if [ -f ./eadl/ZA098000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA098000
    cd ../
  fi

  if [ -f ./epdl/ZA098000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA098000
    cd ../
  fi

  if [ -f ./eedl/ZA098000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA098000
    cd ../
  fi

  printf "Getting ZA099000 data:\t"
  if [ -f ./eadl/ZA099000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA099000
    cd ../
  fi

  if [ -f ./epdl/ZA099000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA099000
    cd ../
  fi

  if [ -f ./eedl/ZA099000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA099000
    cd ../
  fi

  printf "Getting ZA100000 data:\t"
  if [ -f ./eadl/ZA100000 ]; then
    printf "EADL data already exists\t"
  else
    cd ./eadl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EADL/ZA100000
    cd ../
  fi

  if [ -f ./epdl/ZA100000 ]; then
    printf "EPDL data already exists\t"
  else
    cd ./epdl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EPDL/ZA100000
    cd ../
  fi

  if [ -f ./eedl/ZA100000 ]; then
    printf "EEDL data already exists\n"
  else
    cd ./eedl
    wget https://www-nds.iaea.org/epics/ENDL_bkp/EEDL/ZA100000
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

