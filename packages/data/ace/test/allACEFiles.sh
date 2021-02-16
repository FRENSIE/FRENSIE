#! bin/bash/

cd /home/software/mcnpdata/xdata/endf71x
find . -name "*nc" | xargs my_test_executable #not sure about the best way to use this, do i store it in something or do I just pipe it 


# search into each directory
# run find and give only file name

# also i probably need to trim this somehow to get just the ace file name before giving to xargs
# maybe the test builds the executable and then runs this script which keeps executing the executable with different command line args (is this even how this works?)