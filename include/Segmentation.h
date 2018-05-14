//***********************************************
//HEADERS
//***********************************************
#include <pcl/search/search.h>
#include <pcl/search/kdtree.h>
#include <pcl/filters/passthrough.h>
#include <pcl/segmentation/region_growing_rgb.h>
#include <pcl/visualization/pcl_visualizer.h>
#include "Ros_interface.h"

class Segmentation{

private:


public:

  Segmentation(){}
  ~Segmentation(){}

  void color_based_growing_segmentation();


};
