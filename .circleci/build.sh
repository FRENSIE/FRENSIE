#!/bin/bash

source draft.sh
source detect_package.sh

draft_pr=`is_draft`

if [[ "${draft_pr}" == 1 ]]; then
    uniq_modified_pkg=`uniq_modified_pkg`
    for pkg in ${uniq_modified_pkg}; do
        make ${pkg}
    done
else
    make test
fi