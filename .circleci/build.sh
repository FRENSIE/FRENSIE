#!/bin/bash

source /root/frensie/.circleci/github_info.sh
source /root/frensie/.circleci/detect_package.sh

is_draft
draft=$(is_draft)
approved=$(is_approved)
rdy=$(is_ready)
echo "Draft: $draft_pr"
echo "Approved: $approved"
echo "Marked Rdy: $rdy"
if [[ "${is_ready}" == 0 ]]; then 
    uniq_modified_pkg=`uniq_modified_pkg`
    echo "package to be build: $uniq_modified_pkg"
    for pkg in ${uniq_modified_pkg}; do
        echo "Only build the modified package"
        make ${pkg}
        make ${pkg}_tests
    done
elif [[ "${is_ready}" == 1 ]]; then 
    echo "package to be build: all"
    for pkg in ${uniq_modified_pkg}; do
        echo "make"
        make 
    done
fi