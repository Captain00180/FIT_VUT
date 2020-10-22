###################################################################
#   			  BC-Calc Development Makefile					  #
#	   			Author: Filip Januska - xjanus11				  #
###################################################################



.PHONY: all pack test run profile doc installator clean init

all: run
###################################################################
#		Some recipes require additional dependencies to 		  #
#		be installed. To install them, run the 'make init' recipe #
###################################################################
#Install required dependencies for Makefile recipes
init:
	sudo apt-get install python3
	sudo apt-get install python3-pyqt5
	sudo apt-get install python3-pytest
	sudo apt-get install doxygen
	sudo apt-get install dh-make
	
#Generate program documentation
doc: 
	cd .. && doxygen

#Pack project ready for submitting
pack: doc installator
	mkdir ../xjanus11_xgerza00_xmalyv03_xhurta04
	mkdir ../xjanus11_xgerza00_xmalyv03_xhurta04/repo
	cp -ar ../install ../xjanus11_xgerza00_xmalyv03_xhurta04
	rsync -r ../ ../xjanus11_xgerza00_xmalyv03_xhurta04/repo
	cp -ar ../doc ../xjanus11_xgerza00_xmalyv03_xhurta04
	cd ../xjanus11_xgerza00_xmalyv03_xhurta04 && zip -r xjanus11_xgerza00_xmalyv03_xhurta04.zip .
	mv ../xjanus11_xgerza00_xmalyv03_xhurta04/xjanus11_xgerza00_xmalyv03_xhurta04.zip ../
	rm -rf ../xjanus11_xgerza00_xmalyv03_xhurta04

#Run matlib tests
test: 
	python3 -m pytest

#Run the program
run: 
	python3 calc_main.py

#Run the profiling software
profile: 
	python3 profiling.py

#Create debian installation package
installator: 
	cd ../pckg_create && tar -xzvf ./bc-calc-2.0.tar.gz
	cd ../pckg_create/bc-calc-2.0 && dh_make --yes -e xjanus11@fit.vutbr.cz -n -s -f ../bc-calc-2.0.tar.gz
	cd ../pckg_create/bc-calc-2.0 && mv ./debian_settings/* ./debian
	cd ../pckg_create/bc-calc-2.0 && dpkg-buildpackage -rfakeroot -uc -b -d
	mkdir ../install
	mv ../pckg_create/bc-calc_2.0_amd64.deb ../install

clean: 
	cd ../pckg_create && rm -rf ./bc-calc-2.0
	cd .. && rm -rf ./install


