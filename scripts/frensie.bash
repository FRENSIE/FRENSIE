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

# enter process queue (assumes that processes are ids are incremented)
function enter_process_queue() {
    min_pid=1000000000

    for pid in $(pgrep -d " " "$1"); do
	if [ "$min_pid" -gt "$pid" ]; then
    	    min_pid=$pid
    	fi
    done

    #echo "min:$min_pid this:$$"

    if [ $min_pid != $$ ]; then
	#echo "$$ still in queue"
	sleep 5
    	enter_process_queue "$1"
    fi
}

# enter the frensie-run process queue
function enter_frensie_run_process_queue() {
    enter_process_queue "frensie-run-"
}
