#!/bin/bash

# tools to check diff vs reference branch, and extract list of modfied package names

# check if the file is in a valid package and form the package name
function check_file_path()
{
    base=`echo $1 | sed 's/\// /g' | cut -d" " -f1 `
    if [[ $base == "packages" ]]; then
        package=`echo $1 | sed 's/\// /' | cut -d" " -f2 |sed "s|$2| |" | cut -d" " -f1 | sed 's/\//_/g'`
        echo $package
    fi
}

#retrieve the list of modified packages
function modified_pkg() {
    # default main repo setup
    PR_NUMBER=$(echo "$CIRCLE_PULL_REQUEST" | sed "s/.*\/pull\///")
    API_GITHUB="https://api.github.com/repos/$CIRCLE_PROJECT_USERNAME/$CIRCLE_PROJECT_REPONAME"
    PR_REQUEST_URL="$API_GITHUB/pulls/$PR_NUMBER"
    PR_RESPONSE=$(curl "$PR_REQUEST_URL")
    PR_BASE_BRANCH=$(echo $PR_RESPONSE | tr '\r\n' ' ' | jq -e '.base.ref' | tr -d '"')
    PR_BASE_BRANCH="master"

    master_repo="https://github.com/FRENSIE/FRENSIE.git"
    default_branch=$PR_BASE_BRANCH

    # setup temp remote 
    git_remote_name=ci_changelog_`git log --pretty=format:'%h' -n 1`
    git remote add ${git_remote_name} ${master_repo}
    git fetch ${git_remote_name} --quiet

    # diff against temp remote
    #added_changelog_entry=$(git diff ${git_remote_name}/${default_branch} --name-only --exit-code |grep src |grep "\..pp")
    source_package_files=$(git diff ${git_remote_name}/${default_branch} --name-only --exit-code |grep src)
    test_package_files=$(git diff ${git_remote_name}/${default_branch} --name-only --exit-code |grep test)

    # cleaning temp remote
    git remote remove ${git_remote_name}

    # check modified sources
    for file in $source_package_files; do
        check_file_path $file "/src"
    done

    # check modified tests
    for file in $test_package_files; do
        check_file_path $file "/test"
    done
}

# make it a list of unique packages
function uniq_modified_pkg() {
    pkgs=`modified_pkg |sort -u |uniq`
    echo $pkgs
}
