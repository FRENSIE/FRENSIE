## Data Setup Process ##
NOTE: The frensie bin directory must be added to PATH and the frensie python
lib directory must be added to PYTHONPATH for the following commands to work.

## Manual Process

1.) Run `process_xsdir.py -o --xsdir=xsdir --log_file=process_xsdir_log.txt` in the directory that contains the xsdir file of
interest. This will create a file called database.xml.
3.) Run `endl_downloader.py -a > endl_downloader.sh`
4.) Run `bash ./endl_downloader.sh -d ./`. This will create a directory called
endldata where all of the ENDL data is stored.
3.) Run `endl_to_native_endl.py -a` in the directory that contains the
database.xml
file. This will create a file for each atomic number (e.g. endl_native_1.xml)
in the endldata directory.
4.) Run `mkdir native; mkdir native/epr` in the directory that contains the
database.xml file
5.) Run `generate_native_epr.py -o --log_file=generate_native_epr_log.out`
in the directory that contains the database.xml file

## Automatic Process

1.) Run `generate_database.sh`
