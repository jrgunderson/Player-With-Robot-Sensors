# Player-With-Robot-Sensors


PREFACE:

If you don't have a Linux Partition |or| need some general Linux troubleshooting tips:
	- Read "How to Dual Boot" inside "Notes" folder

___________________________________________________________________________________________________
	
# Note: Ubuntu 16.04 seemed to be too new to be compatible with player/stage

/// To get Player/Stage working on your Ubuntu 14.04 ///

	- Simply download the "src" folder inside the folder "Player-Stage for Ubuntu 14.04" into your home directory

	- Run the 2 .sh script files inside the src folder
		- $ sudo ./<filename>.sh
	
	- Confirm that library path was added to your .bashrc file
	  1) navigate to "home" folder -> view hidden files -> open ".bashrc" file 
	  2) add the folowing code to the bottom of the file -> save -> restart
		export PKG_CONFIG_PATH=/usr/local/lib64/pkgconfig
		export LD_LIBRARY_PATH=/usr/local/lib64:/usr/local/lib:$LD_LIBRARY_PATH


/// SETUP HOKUYOAIST & PHIDGET SENSORS ///

	- Follow instructions on first 2 pages of "DesignOverviewDocument" inside "Player for Ubuntu 14.04" folder

	- If you run into any problems, please reference "Troubleshoot Install"






