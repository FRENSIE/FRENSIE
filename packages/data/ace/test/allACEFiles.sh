#!/bin/bash

# list=$( find $1 -name "*nc" | cut -d"/" -f8 ) $1 is the first command line argument, e.g. /home/software/mcnpdata/xdata/endf71x/
# ./allACEFiles.sh /home/software/mcnpdata/xdata/endf71x/
# cut command to split by / and take the 8th split commponent

list=$( find /home/software/mcnpdata/xdata/endf71x/ -name "*nc")

for item in ${list}; do
    echo $item
    #./execuatble --test_isotope_ace_table_name= --test_isotope_ace_file_name= 
done

# WORFLOW PLAN
# get full file path (need this for command line arg)
# cut to get table name  (need this for second command line arg)
# let default do its job for filestartline
# can give relative path as argument