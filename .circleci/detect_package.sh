#!/bin/bash


function check_file_path()
{
    base=`echo $1 | sed 's/\// /g' | cut -d" " -f1 `
    if [[ $base == "packages" ]];
    then
        package=`echo $1 | sed 's/\// /' | cut -d" " -f2 |sed "s|$2| |" | cut -d" " -f1 | sed 's/\//_/g'`
        echo $package 

    fi
}

# default main repo setup
# PR_NUMBER=$(echo "$CIRCLE_PULL_REQUEST" | sed "s/.*\/pull\///")
# API_GITHUB="https://api.github.com/repos/$CIRCLE_PROJECT_USERNAME/$CIRCLE_PROJECT_REPONAME"
# PR_REQUEST_URL="$API_GITHUB/pulls/$PR_NUMBER"
# PR_RESPONSE=$(curl "$PR_REQUEST_URL")
# PR_BASE_BRANCH=$(echo $PR_RESPONSE | tr '\r\n' ' ' | jq -e '.base.ref' | tr -d '"')
PR_BASE_BRANCH="master"
echo "Testing changelog against $PR_BASE_BRANCH branch"

master_repo="https://github.com/FRENSIE/FRENSIE.git"
default_branch=$PR_BASE_BRANCH

# setup temp remote 
git_remote_name=ci_changelog_`git log --pretty=format:'%h' -n 1`
git remote add ${git_remote_name} ${master_repo}
git fetch ${git_remote_name}

# diff against temp remote
#added_changelog_entry=$(git diff ${git_remote_name}/${default_branch} --name-only --exit-code |grep src |grep "\..pp")
source_package_files=$(git diff ${git_remote_name}/${default_branch} --name-only --exit-code |grep src)
test_package_files=$(git diff ${git_remote_name}/${default_branch} --name-only --exit-code |grep test)

# cleaning temp remote
git remote remove ${git_remote_name}

echo $source_package_files

for file in $source_package_files;
do
check_file_path $file "/src"
done

for file in $test_package_files;
do
check_file_path $file "/test"
done
