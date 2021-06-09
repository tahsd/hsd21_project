# Final Project 
This is official manual for your final project.  
Please follow the instructions and specs below.   
Keep your eyes on updates as there may be some changes in specification / scoring criteria in future.

---
## Updates 
- (5/14) The due date has been extended to June 19.
- (5/24) The official file and videos for the final project has been uploaded on ETL. 
- (5/24) Updates to the scoring criteria
- (5/25) Materials for quantization has been uploaded.
- (6/4) Materials for zero-skipping has been uploaded.
- (6/9) Updates to specs : Latency of your floating point MAC must be set as 16 cycles.

---

## Due date
With your report and project files: **~6/19**  
For now we do not consider accepting any delayed submission.

---

## Optimizing your work
We suggest three different ways to optimize your work: **Quantization**, **Zero-Skipping**, and **DMA**(Direct Memory Access).  

|              |        |         |         |
|--------------|--------|---------|---------|
| V0 (Baseline)| [Korean](http://etl.snu.ac.kr/mod/vod/view.php?id=1553770) | [English](http://etl.snu.ac.kr/mod/vod/view.php?id=1553879) |   [Files](http://etl.snu.ac.kr/mod/ubboard/article.php?id=1413711&bwid=2525754)      |
| Quantization | [Korean](http://etl.snu.ac.kr/mod/vod/view.php?id=1554890) | [English](http://etl.snu.ac.kr/mod/vod/view.php?id=1554898)          | [Files](http://etl.snu.ac.kr/mod/ubboard/article.php?id=1413711&bwid=2544036)        |
| Zero-skpping | [Korean](http://etl.snu.ac.kr/mod/vod/view.php?id=1567756)       |   [English](http://etl.snu.ac.kr/mod/vod/view.php?id=1567757)     |  [Files](http://etl.snu.ac.kr/mod/ubboard/article.php?id=1413711&bwid=2562718)       |
| DMA          | [Korean](http://etl.snu.ac.kr/mod/vod/view.php?id=1547993) | [English](http://etl.snu.ac.kr/mod/vod/view.php?id=1547994) |   [Files](http://etl.snu.ac.kr/mod/ubboard/article.php?id=1413711&bwid=2535101)      |


---
## 1. Prepare your bitstream file
You need a bitstream file that you have generated with the block design that includes your IP.  
You just have to replace the custom IP of the block design in lab10 with your MM(Matrix-Matrix) PE controller.  
How the PE controller should be designed is explained [here.](http://etl.snu.ac.kr/mod/ubboard/article.php?id=1413711&bwid=2502253)  



## 2. Boot your device with the bitstream file
Once you are prepared with the bistream file, rename it to "zynq.bit", and move it to the sdcard.  
Insert the sdcard to the device and boot it.  
How you can boot your device via minicom is explained [here.](http://etl.snu.ac.kr/mod/ubboard/article.php?id=1413711&bwid=2500892)

  
## 3. (Optional) Download the repository 
※ This is optional since the source files are totally same as in lab09, except benchmark.sh.  
You can therefore skip 3~6 and extend your work on lab09.  
  
You need to download this repository to start your final project.  
```
$ git clone https://github.com/tahsd/hsd21_project  
```
Note that this command can be run on the terminal on your device if connected to the network.  

## 4. (Optional) Check dependencies 
Check if all the dependencies for running the codes have been installed.
```
$ sudo apt-get update -y
$ sudo apt-get install -y libprotobuf-dev protobuf-compiler python python-numpy
```
These would have already been installed on your device if you have successfully done your lab09.

## 5. (Optional) Download the dataset 
Run the command below to download the dataset.
```
$ bash download.sh
```

## 6. (Optional) Modify the codes
You will see three functions (LargeMV & LargeMM & ConvLowering) that have not been implemented in the fpga_api.cpp & fpga_api_cpu.cpp.  
You can fill in the codes for the functions, though, since you have already done it in the lab09.  
Modify fpga_api.cpp & fpga_api_cpu.cpp based on your previous works.  

## 7. Run it
Run the validation code as below.
```
sh benchmark.sh
```
Hopefully you will get 100% accuracy on the classfication task!

---
## Specifications
1. Accuracy on the classification task with CNN should be 100%.   
  (Small degradation by quantization or zero-skipping will be allowed for particular cases.)
2. The PE controller should consist of (at most) 8x8 (=64) PEs.
3. The FSM should consist of 5 states: **IDLE** - **LOAD** - **CALC** - **HARV** - **DONE**  
4. During HARV(harvest) state, the PE controller should write back the computed data to BRAM.  
You are not bound to this approach for optimizing V0. That means, you can also utilize pipelining.
5. Latency of your floating point MAC must be set as 16 cycles.

---
## Scoring Criteria
Well explained in the videos.
1. Implementation
2. Inference time
  - **Total computation time spent by HW** for V0, quantization, zero-skipping
  - **Total data transfer time** for DMA
  - Time spent by SW is not evaluted.
3. Accuracy 
4. Report 


---
**Please use the Q&A board on ETL if you have questions or want more information about the project.**  




