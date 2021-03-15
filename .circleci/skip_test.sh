#!/bin/bash

skip_test() {
    required_env_vars=(
        "CIRCLE_PROJECT_USERNAME"
        "CIRCLE_TOKEN"
        "CIRCLE_BUILD_NUM"
    )
    for required_env_var in ${required_env_vars[@]}; do
        if [[ -z "${!required_env_var}" ]]; then
        printf "BAD ENVIRONMENT SETTINGS\n"
        printf "${required_env_var} not provided, but that doesn't mean we should skip CI.\n"
        exit 0
        fi
    done

    printf "Attempting to cancel any running jobs"
    FORMAT_PARAM="-H \"Content-Type: application/json\""
    AUTH_PARAMS="--header  \"Circle-Token: ${CIRCLE_TOKEN}\""
    CMD="curl -X"
    CI_API_BASE_URL="https://circleci.com/api/v2"
    CI_PRJ_URL="${CI_API_BASE_URL}/project/gh/${CIRCLE_PROJECT_USERNAME}/${CIRCLE_PROJECT_REPONAME}"
    CI_JOB_URL="${CI_PRJ_URL}/job/${CIRCLE_BUILD_NUM}"
    # Get the Id of the Workflow to Cancel
    MSG=$(${CMD} GET "${CI_JOB_URL}" $FORMAT_PARAM -H "Circle-Token: ${CIRCLE_TOKEN}")
    WKF_ID=$(echo $MSG | tr '\r\n' ' ' | jq  ".latest_workflow.id" | tr -d '"')

    # Cancel the Workflow based on its Id
    printf "Canceling WORKFLOW: test"
    CI_WKF_CANCEL_URL="${CI_API_BASE_URL}/workflow/${WKF_ID}/cancel"
    curl -X POST "${CI_WKF_CANCEL_URL}" -H "Circle-Token: ${CIRCLE_TOKEN}"
    exit 0
}