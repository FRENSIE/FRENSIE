## Data Setup Process ##
1.) Run `process_xsdir.py` in the directory that contains the xsdir file of
interest. This will create a file called database.xml.
2.) Copy the scripts/endl_downloader.py script to the directory that contains
the xsdir file
3.) Run `python ./endl_downloader.py -a > endl_downloader.sh`
4.) Run `bash ./endl_downloader.sh -d ./`. This will create a directory called
endldata where all of the ENDL data is stored.
3.) Run `endl_to_native_endl.py -a` in the directory that contains the database.xml
file. This will create a file for each atomic number (e.g. endl_native_1.xml)
in the endldata directory.
4.) Run 