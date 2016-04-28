#!/usr/bin/env python

import sys, getopt, os

def main(argv):
	directory = './'
	try:
		opts, args = getopt.getopt(argv,"hd:",["help","output_directory="])
	except getopt.GetoptError:
		print 'endl.py -d <output_directory>'
		sys.exit(2)
	for opt, arg in opts:
		if opt == '-h':
			print 'endl.py -d <output_directory>'
			sys.exit()
		elif opt in ("-d", "--output_directory"):
			directory = arg
			if not os.path.exists( directory ):
				print directory,'is not a valid directory'
				sys.exit(2)

	print 'The output directory is:', directory

	elemental_information = [["H" ,  "00",   "1000"],
		                     ["He",  "00",   "2000"],
		                     ["Li",  "00",   "3000"],
		                     ["Be",  "00",   "4000"],
		                     ["B" ,  "00",   "5000"],
		                     ["C" ,  "00",   "6000"],
		                     ["N" ,  "00",   "7000"],
		                     ["O" ,  "00",   "8000"],
		                     ["F" ,  "00",   "9000"],
		                     ["Ne",  "0",   "10000"],
		                     ["Na",  "0",   "11000"],
		                     ["Mg",  "0",   "12000"],
		                     ["Al",  "0",   "13000"],
		                     ["Si",  "0",   "14000"],
		                     ["P" ,  "0",   "15000"],
		                     ["S" ,  "0",   "16000"],
		                     ["Cl",  "0",   "17000"],
		                     ["Ar",  "0",   "18000"],
		                     ["K" ,  "0",   "19000"],
		                     ["Ca",  "0",   "20000"],
		                     ["Sc",  "0",   "21000"],
		                     ["Ti",  "0",   "22000"],
		                     ["V" ,  "0",   "23000"],
		                     ["Cr",  "0",   "24000"],
		                     ["Mn",  "0",   "25000"],
		                     ["Fe",  "0",   "26000"],
		                     ["Co",  "0",   "27000"],
		                     ["Ni",  "0",   "28000"],
		                     ["Cu",  "0",   "29000"],
		                     ["Zn",  "0",   "30000"],
		                     ["Ga",  "0",   "31000"],
		                     ["Ge",  "0",   "32000"],
		                     ["As",  "0",   "33000"],
		                     ["Se",  "0",   "34000"],
		                     ["Br",  "0",   "35000"],
		                     ["Kr",  "0",   "36000"],
		                     ["Rb",  "0",   "37000"],
		                     ["Sr",  "0",   "38000"],
		                     ["Y" ,  "0",   "39000"],
		                     ["Zr",  "0",   "40000"],
		                     ["Nb",  "0",   "41000"],
		                     ["Mo",  "0",   "42000"],
		                     ["Tc",  "0",   "43000"],
		                     ["Ru",  "0",   "44000"],
		                     ["Rh",  "0",   "45000"],
		                     ["Pd",  "0",   "46000"],
		                     ["Ag",  "0",   "47000"],
		                     ["Cd",  "0",   "48000"],
		                     ["In",  "0",   "49000"],
		                     ["Sn",  "0",   "50000"],
		                     ["Sb",  "0",   "51000"],
		                     ["Te",  "0",   "52000"],
		                     ["I" ,  "0",   "53000"],
		                     ["Xe",  "0",   "54000"],
		                     ["Cs",  "0",   "55000"],
		                     ["Ba",  "0",   "56000"],
		                     ["La",  "0",   "57000"],
		                     ["Ce",  "0",   "58000"],
		                     ["Pr",  "0",   "59000"],
		                     ["Nd",  "0",   "60000"],
		                     ["Pm",  "0",   "61000"],
		                     ["Sm",  "0",   "62000"],
		                     ["Eu",  "0",   "63000"],
		                     ["Gd",  "0",   "64000"],
		                     ["Tb",  "0",   "65000"],
		                     ["Dy",  "0",   "66000"],
		                     ["Ho",  "0",   "67000"],
		                     ["Er",  "0",   "68000"],
		                     ["Tm",  "0",   "69000"],
		                     ["Yb",  "0",   "70000"],
		                     ["Lu",  "0",   "71000"],
		                     ["Hf",  "0",   "72000"],
		                     ["Ta",  "0",   "73000"],
		                     ["W" ,  "0",   "74000"],
		                     ["Re",  "0",   "75000"],
		                     ["Os",  "0",   "76000"],
		                     ["Ir",  "0",   "77000"],
		                     ["Pt",  "0",   "78000"],
		                     ["Au",  "0",   "79000"],
		                     ["Hg",  "0",   "80000"],
		                     ["Tl",  "0",   "81000"],
		                     ["Pb",  "0",   "82000"],
		                     ["Bi",  "0",   "83000"],
		                     ["Po",  "0",   "84000"],
		                     ["At",  "0",   "85000"],
		                     ["Rn",  "0",   "86000"],
		                     ["Fr",  "0",   "87000"],
		                     ["Ra",  "0",   "88000"],
		                     ["Ac",  "0",   "89000"],
		                     ["Th",  "0",   "90000"],
		                     ["Pa",  "0",   "91000"],
		                     ["U" ,  "0",   "92000"],
		                     ["Np",  "0",   "93000"],
		                     ["Pu",  "0",   "94000"],
		                     ["Am",  "0",   "95000"],
		                     ["Cm",  "0",   "96000"],
		                     ["Bk",  "0",   "97000"],
		                     ["Cf",  "0",   "98000"],
		                     ["Es",  "0",   "99000"],
		                     ["Fm",  "",   "100000"]]

	# ENDL.SH Header Information
	endl_file = open('endl.sh','w')

	endl_file.write( "#!/bin/bash\n" )
	endl_file.write( "##---------------------------------------------------------------------------##\n" )
	endl_file.write( "## ENDL Data Downloader\n" )
	endl_file.write( "##---------------------------------------------------------------------------##\n\n" )
	endl_file.write( "# Set data directory path.\n" )

	endl_file.write( "if [ -d \"" + directory + "\" ]; then\n" )

	ENDL_DATA_PATH = "/home/software/mcnpdata/endldata"
	EADL_DATA_PATH = ENDL_DATA_PATH + "/eadl"
	EPDL_DATA_PATH = ENDL_DATA_PATH + "/epdl"
	EEDL_DATA_PATH = ENDL_DATA_PATH + "/eedl"


	endl_file.write( "cd " + directory + "\n\n" )
	endl_file.write( "if [ ! -d ./endldata ]; then\n" )
	endl_file.write( "  mkdir ./endldata\n" )
	endl_file.write( "fi\n\n" )
	endl_file.write( "cd ./endldata\n\n" )

	endl_file.write( "if [ ! -d ./eadl ]; then\n" )
	endl_file.write( "  mkdir eadl\n" )
	endl_file.write( "fi\n\n" )

	endl_file.write( "if [ ! -d ./epdl ]; then\n" )
	endl_file.write( "  mkdir epdl\n" )
	endl_file.write( "fi\n\n" )

	endl_file.write( "if [ ! -d ./eedl ]; then\n" )
	endl_file.write( "  mkdir eedl\n" )
	endl_file.write( "fi\n\n" )


	for i in range( 0, len(elemental_information) ):
		ELEMENT = "za" + elemental_information[i][1] + elemental_information[i][2]
		endl_file.write( "echo \"Getting " + ELEMENT + " data\"\n" )
		
		endl_file.write( "if [ -f ./eadl/" + ELEMENT + " ]; then\n" )
		endl_file.write( "  echo \"EADL " + ELEMENT + " data already exists\"\n" )
		endl_file.write( "else \n" )
		endl_file.write( "  cd ./eadl \n" )
		endl_file.write( "  wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EADL.ELEMENTS/" +
		                 ELEMENT + "\n" )
		endl_file.write( "  cd ../\n" )
		endl_file.write( "fi\n\n" )

		endl_file.write( "if [ -f ./epdl/" + ELEMENT + " ]; then\n" )
		endl_file.write( "  echo \"EPDL " + ELEMENT + " data already exists\"\n" )
		endl_file.write( "else\n" )
		endl_file.write( "  cd ./epdl\n" )
		endl_file.write( "  wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EPDL.ELEMENTS/" +
		                 ELEMENT + "\n" )
		endl_file.write( "  cd ../\n" )
		endl_file.write( "fi\n\n" )

		endl_file.write( "if [ -f ./eedl/" + ELEMENT + " ]; then\n" )
		endl_file.write( "  echo \"EEDL " + ELEMENT + " data already exists\"\n" )
		endl_file.write( "else\n" )
		endl_file.write( "  cd ./eedl\n" )
		endl_file.write( "  wget http://www.nndc.bnl.gov/endf/epics2014/ENDL/EEDL.ELEMENTS/" +
		                 ELEMENT + "\n" )
		endl_file.write( "  cd ../\n" )
		endl_file.write( "fi\n\n" )

	endl_file.write( "fi\n\n" )

	endl_file.close()

if __name__ == "__main__":
   main(sys.argv[1:])

