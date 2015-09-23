# wait for other critical processes to finish before continuing
function wait_for_critical_procs() {
    
    for arg in $@; do
	if [ -n "$regex" ]; then
	    regex="$regex|$arg"
	else
	    regex="$arg"
	fi
    done
    
    while [ $(pgrep "$regex") > /dev/null ]; do
	sleep 5
    done
}

# wait for frensie critical processes to finish before continuing
function wait_for_frensie_critical_procs() {
    wait_for_critical_procs "facemc" "ctest"
}

# prevent multiple copies of the script from running
function prevent_multiple_instances() {
    for pid in $(pidof -x $0); do
	if [ $pid != $$ ]; then
	    exit 0
	fi
    done
}
