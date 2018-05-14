//***********************************************
//HEADERS
//***********************************************
#include <iostream>
#include <string>
#include <thread>
#include <set>
#include <eigen3/Eigen/Dense>
#include <boost/filesystem.hpp>
#include <boost/algorithm/algorithm.hpp>
#include "BundleAdjustment.h"

class StructFromMotion{ 

  private:
  std::vector<cv::Mat>                    nImages;
  std::vector<cv::Matx34f>                nCameraPoses;
  std::vector<Feature>                    nFeatureImages;
  std::vector<Point3D>                    nReconstructionCloud; 
  std::vector<cv::Vec3b>                  nReconstructionCloudRGB;
  std::vector<std::string>                nImagesPath; 
  std::set<int>                           nDoneViews;
  std::set<int>                           nGoodViews;
  CameraData                              cameraMatrix;
  cv::Ptr<cv::Feature2D>                  ptrFeature2D;
  cv::Ptr<cv::DescriptorMatcher>          matcherFlan;
  double                                  NN_MATCH_RATIO;
  ROSInterface                            visualizer;

  public: 

  //===============================================
  //CONSTRUCTOR
  //===============================================

  StructFromMotion(){

    /*
    @ FLANNBASED = 1,
    @ BRUTEFORCE = 2,
    @ BRUTEFORCE_L1 = 3,
    @ BRUTEFORCE_HAMMING = 4,
    @ BRUTEFORCE_HAMMINGLUT = 5,
    @ BRUTEFORCE_SL2 = 6
    */    

    ptrFeature2D = cv::ORB::create(5000.0);
    matcherFlan = cv::DescriptorMatcher::create("BruteForce-Hamming");
    NN_MATCH_RATIO = 0.8f;

  }

  //===============================================
  //PIPELINE
  //===============================================
  void run_SFM();
  //===============================================
  //IMAGES LOAD
  //===============================================
  bool imagesLOAD(const std::string&  directoryPath);
  //===============================================
  //FEATURE DETECTION
  //===============================================
  Feature getFeature(const cv::Mat& image);  
  //===============================================
  //FEATURE EXTRACTION ALL IMAGES
  //===============================================
  bool extractFeature();
  //===============================================
  //FEATURE MATCHING WITH RATIO TEST
  //===============================================
  Matching getMatching(const Feature& left,const Feature& right);  
  //===============================================
  //FEATURE MATCHING WITH CROSS-CHECK FILTER
  //===============================================
  Matching matchingFor2D3D(Feature& feature1,Feature& feature2);
  //===============================================
  //IMAGE MATCHING
  //===============================================
  cv::Mat imageMatching(const cv::Mat& img1,const Keypoints& keypoints1,
                        const cv::Mat& img2,const Keypoints& keypoints2,const Matching& matches);  
  //===============================================
  //PRINT IMAGE
  //===============================================
  void imShow(const cv::Mat& matchImage,const std::string& str);
  //===============================================
  //CONVERTION KEYPOINTS TO POINTS2D
  //===============================================
  void keypoints2F(Keypoints& keypoints, Points2f& points2D);
  //===============================================
  //GET CAMERA MATRIX
  //===============================================
  void getCameraMatrix(const std::string& str);
  //===============================================
  //FUNCTION CHECK ROTATION MATRIX (Must be det=1)
  //===============================================
  bool CheckCoherentRotation(cv::Mat& R); 
  //===============================================
  //FUNCTION ALIGNED POINTS
  //===============================================
  void AlignedPointsFromMatch(const Feature& left,const Feature& right,const Matching& matches,
                              Feature& alignedL,Feature& alignedR);  
  //===============================================
  //FUNCTION ALIGNED POINTS WITH BACK REFERENCE
  //===============================================
  void AlignedPoints(const Feature& left,const Feature& right,const Matching& matches,
                     Feature& alignedL, Feature& alignedR,std::vector<int>& idLeftOrigen,
                     std::vector<int>& idRightOrigen);
  //===============================================
  //TRIANGULATE VIEWS
  //===============================================
  bool triangulateViews(const Feature& left,const Feature& right,const cv::Matx34f& P1,
                        const cv::Matx34f& P2,const Matching& matches,const CameraData& matrixK,
                        const ImagePair& imagePair,std::vector<Point3D>& pointcloud);
  //===============================================
  //BASE TRIANGULATION
  //===============================================
  bool baseTriangulation(); 
  //===============================================
  //INVERSE MATRIX-DETERMINANT FUNCTION EIGEN
  //===============================================
  cv::Mat inverse(cv::Mat& matrix);
  //===============================================
  //MATRIX DETER
  //===============================================
  double determinante(cv::Mat& relativeRotationCam);
  //===============================================
  //FIND HOMOGRAPHY INLIERS
  //===============================================
  int findHomographyInliers(const Feature& f1,const Feature& f2,const Matching& matches);
  //===============================================
  //ADD MORE VIEWS FUNCTION
  //===============================================
  void addMoreViews();
  //===============================================
  //FIND CAMERA POSE WITH PNPRANSAC
  //===============================================
  bool findCameraPosePNP(const CameraData& matrixK,const std::vector<cv::Point3f>& pts3D,
                         const std::vector<cv::Point2f>& pts2D,cv::Matx34f& cameraPose);
  //===============================================
  //FIND CAMERA POSE WITH ESSENTIAL MATRIX
  //===============================================
  bool getCameraPose(const CameraData& intrinsics,const Matching & matches,
                     const Feature& left, const Feature& right, Matching& prunedMatch,
                     cv::Matx34f& Pleft, cv::Matx34f& Pright);
  //===============================================
  //FIND 2D-3D CORRESPONDENCES
  //===============================================
  Pts3D2DPNP find2D3DMatches(ImagePair& pair);
  //===============================================
  //FIND BEST PAIR FOR BASELINE RECONSTRUCTION
  //===============================================
  std::map<int,ImagePair> findBestPair();
  //===============================================
  //MERGE NEW POINTCLOUD
  //===============================================
  void mergeNewPoints(const std::vector<Point3D>& cloud);
  //===============================================
  //BUNDLE ADJUSTMENT ADJUSTER
  //===============================================
  void adjustCurrentBundle(); 
  //===============================================
  //SAVE POINTCLOUD TO .PLY OR .PCD
  //===============================================
  void saveCloudAndCamerasToPLY(const std::string& prefix);
  void saveCloudToPCD(const std::string& prefix);
  //===============================================
  //MESHING POINTCLOUD
  //===============================================
  void meshingPointCloud();  
  //===============================================
  //GET RGB FOR POINTCLOUD
  //===============================================
  void GetRGBForPointCloud(std::vector<Point3D>& _pcloud,std::vector<cv::Vec3b>& RGBforCloud);

};//End class


