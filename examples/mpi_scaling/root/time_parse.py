#!/usr/local/bin/python

# File prefix
file_prefix = "MPI_Strong_"

# File suffix
file_suffix = ".txt"

# Array of number of cores for simulations
core_numbers = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]

# Output file name
output_file_name = file_prefix + "Summary" + file_suffix

output_file = open(output_file_name, 'w')

for i in range(0, len(core_numbers)):
    input_file = open(file_prefix + str(core_numbers[i]) + file_suffix, 'r')
    line = input_file.readline()
    
    found_time = False;
    time = "";
    
    for x in range (0, 50): 
        line = input_file.readline()
        
        if (len(line) > 1 and line.split()[0] == "Simulation"):
            time = line.split()[3]
        
    output_file.write(str(core_numbers[i]) + "  " + time + "\n" )
    input_file.close()
    
output_file.close()


