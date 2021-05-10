# hsd21_project


## 1. Prepare your bitstream file
You need a bitstream file that you have generated with the block design that includes your IP.  
You just have to replace the custom IP of the block design in lab 10 with your MM(Matrix-Matrix) PE controller.  
How the PE controller should be designed is explained [here.](http://etl.snu.ac.kr/mod/ubboard/article.php?id=1413711&bwid=2502253)

## 2. Boot your device with the bitsream file
Once you are prepared, modify the name of your bitstream file to "zynq.bit", and move it to the sdcard.  
Insert the sdcard to the device, and boot your device.  
How you can boot your device via minicom is explained [here.](http://etl.snu.ac.kr/mod/ubboard/article.php?id=1413711&bwid=2500892)

## 3. Download the repository
You need to download this repository to start your final project.  
```
$ git clone https://github.com/tahsd/hsd21_project  
```
Note that this commaand can be run on the terminal on your device.  

## 4. Check dependencies
Check if all the dependencies for running the codes have been installed.
```
$ sudo apt-get update -y
$ sudo apt-get install -y libprotobuf-dev protobuf-compiler python python-numpy
```
These would have already been installed on your device if you have successfully done your lab 9.
