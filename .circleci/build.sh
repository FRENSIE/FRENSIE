#!/bin/bash

source /root/frensie/.circleci/draft.sh
source /root/frensie/.circleci/detect_package.sh

draft_pr=`is_draft`
echo "Draft: $draft_pr"
if [[ "${draft_pr}" == 1 ]]; then
    uniq_modified_pkg=`uniq_modified_pkg`
    for pkg in ${uniq_modified_pkg}; do
        echo "make $pkg; make ${pkg}-test"
        make ${pkg}
        make ${pkg}_tests
    done
else
    make
fi