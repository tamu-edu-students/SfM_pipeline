
# A simple structure from motion pipeline for 3D incremental reconstruction

This is a reference implementation of a Structure-from-Motion pipeline in OpenCV, following the work of Roy Shilkrot at SfM-Toy-Library. https://github.com/royshil/SfM-Toy-Library

*Note:* This is not a complete and robust SfM pipeline implementation. The purpose of this code is to do a 3D reconstruction of a tree and get dendrometry estimation. 

----------------------

A simple incremental SFM pipeline for 3D reconstruction of a tree with bundle adjustment. 
* Incremental SFM
* Bundle Adjustment - Ceres solver
* Densification process - PMVS2 

## Example

<img src="./imgs/example.png" align="center" height="500" width="950"><br>




### Compilation
* Set "YOUR OWN" PCL Build DIR in CMakeList.txt e.g: **/opt/pcl-1.8.1/build** and save it.
* Set "YOUR OWN" OpenCV Build DIR in CMakeList.txt e.g: **/opt/opencv-3.4.1/build** and save it.
* Create a "build" folder

in the build folder:

    cd build/  
    cmake ..
    make
    ./iTree3DMap
 	 




### debug 
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
file ./iTree3DMap
apt-get update && apt-get install -y gdb gdbserver
gdb ./iTree3DMap
break main  # adds breakpoint
run
continue 
info locals infor args
quit # quit gdb