#!/bin/bash

# list=$( find $1 -name "*nc" | cut -d"/" -f8 ) $1 is the first command line argument, e.g. /home/software/mcnpdata/xdata/endf71x/
# ./allACEFiles.sh /home/software/mcnpdata/xdata/endf71x/
# cut command to split by / and take the 8th split commponent

# list of paths
list_of_paths=$( find /home/software/mcnpdata/xdata/endf71x/ -name "*nc")

# make list of table names


for item in ${list_of_paths}; do
    echo ${item} 
    table_name=$(echo "${item}" | cut -d"/" -f8 ) # cut item to get table name
    echo ${table_name}
    #./path-to-execuatble/ --test_isotope_ace_file_name=item --test_isotope_ace_table_name=table_name
done



# WORFLOW PLAN
# get full file path (need this for command line arg)
# cut to get table name  (need this for second command line arg)
# let default do its job for filestartline
# can give relative path as argument
# something like  ./execuatble --test_isotope_ace_table_name= --test_isotope_ace_file_name= 
