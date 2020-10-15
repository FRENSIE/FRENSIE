#!/bin/bash

source /root/frensie/.circleci/github_info.sh
source /root/frensie/.circleci/detect_package.sh
source /root/frensie/.circleci/skip_test.sh

draft_pr=`is_draft`

if [[ "${draft_pr}" == 1 ]]; then
    uniq_modified_pkg=`uniq_modified_pkg`
    for pkg in ${uniq_modified_pkg}; do
        make test-${pkg}
    done
else
    make test
fi

s_draft
draft=$(is_draft)
approved=$(is_approved)
rdy=$(is_ready)
echo "Draft: $draft_pr"
echo "Approved: $approved"
echo "Marked Rdy: $rdy"
if [[ "${draft}" == 1 ]]; then
    echo "In draft Mode"
    echo "Skipping test"
    skip_test
elif [[ "${rdy}" == 0 ]]; then 
    uniq_modified_pkg=`uniq_modified_pkg`
    echo "package to be build: $uniq_modified_pkg"
    for pkg in ${uniq_modified_pkg}; do
        echo "Draft only build the modified package"
        make test-${pkg}
    done
elif [[ "${rdy}" == 1 ]]; then 
    echo "package to be build: all"
    for pkg in ${uniq_modified_pkg}; do
        echo "make"
        make test
    done
fi