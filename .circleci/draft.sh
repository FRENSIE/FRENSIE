#!/bin/bash

function is_draft() {
    required_env_vars=(
        "GITHUB_TOKEN"
        "CIRCLE_PROJECT_USERNAME"
        "CIRCLE_PR_REPONAME"
        "CIRCLE_PR_NUMBER"
        "CIRCLE_TOKEN"
        "CIRCLE_BUILD_NUM"
    )
    # check if required VAR are defined 
    for required_env_var in ${required_env_vars[@]}; do
        if [[ -z "${!required_env_var}" ]]; then
        printf "BAD ENVIRONMENT SETTINGS\n"
        printf "${required_env_var} not provided, but that doesn't mean we should skip CI.\n"
        exit 0
        fi
    done


    # Since we're piggybacking off of an existing OAuth var, tweak the var for our uses
    token=$(printf "${GITHUB_TOKEN}" | cut -d':' -f1)
    headers="Authorization: token $token"
    api_endpoint="https://api.github.com/repos/${CIRCLE_PROJECT_USERNAME}/${CIRCLE_PR_REPONAME}/pulls/${CIRCLE_PR_NUMBER}"
    # Fetch PR metadata from Github's API and parse fields from json
    github_res=$(curl --silent --header "${headers}" "${api_endpoint}" | jq '{mergeable_state: .mergeable_state, title: .title}')
    mergeable_state=$(printf "${github_res}" | jq '.mergeable_state')
    title=$(printf "${github_res}" | jq '.title' | tr '[:upper:]' '[:lower:]')
    if [[ "${title}" == "null" && "${mergeable_state}" == "null" ]]; then
        printf "Couldn't fetch info on PR, but that doesn't mean we should skip CI.\n"
        exit 0
    fi

    # Check for Draft
    draft_pr=0
    if [[ "${mergeable_state}" == "\"draft\"" ]]; then
        draft_pr=1
    fi
    # Check for Tittle SKIP Token
    for skip_token in '[wip]' '[WIP]'; do
        if [[ ${title} == *"${skip_token}"* ]]; then
        draft_pr=1
        fi
    done
    echo $draft_pr
}