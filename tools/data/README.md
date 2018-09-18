## Data Setup Process ##
1.) Run process_xsdir.py in the directory that contains the xsdir file of
interest. This will create a file called database.xml.
2.) Run endl_downloader.sh in the directory that contains the database.xml
file. This will create a directory called endldata where all of the ENDL data
is stored.
3.) Run endltonative.py in the directory that contains the database.xml file.
This will create a file for each atomic number (e.g. endl_1_native.xml) in the
endldata directory.
4.) Run ...