#!/bin/bash

source /root/frensie/.circleci/draft.sh
source /root/frensie/.circleci/detect_package.sh

is_draft
echo "Draft: $draft_pr"
if [[ "${draft_pr}" == 1 ]]; then
    echo "In draft Mode"
    uniq_modified_pkg=`uniq_modified_pkg`
    for pkg in ${uniq_modified_pkg}; do
        echo "make $pkg; make ${pkg}-test"
        make ${pkg}
        make ${pkg}-tests
    done
else
    make
fi