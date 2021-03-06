#ifndef B2BTL_MEAM
#define B2BTL_MEAM

#include "pclFunction.h"
#include "meshSampling.h"
#include "HPR.h"

#include <pcl/common/common.h>
// kdtree
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/kdtree/impl/kdtree_flann.hpp>
#include <pcl/surface/mls.h>
//extract indices
#include <pcl/filters/extract_indices.h>
#include <pcl/ModelCoefficients.h>
#include <pcl/filters/project_inliers.h>
//opencv
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
//Eigen
#include <Eigen/Dense>

class DescriptorB2BTL_MEAM
{
private:
	//IO
	std::string model_filename_ = "../../../data/nap.STL";
	bool is_mesh = true;
	std::queue<cv::Mat>* images_q;

	//Algorithm params
	bool show_keypoints_ = true;
	bool show_corr = false;
	bool show_FP = false;
	bool show_instances = false;
	bool use_hough_ = true;
	float samp_rad = 0.01f;

	std::string type = "B2BTL_MEAM";

	// Model 
	PointCloudType::Ptr model = PointCloudType::Ptr(new PointCloudType());
	PointCloudType::Ptr model_keypoints = PointCloudType::Ptr(new PointCloudType());
	pcl::PointCloud<PointXYZTangent>::Ptr model_keypoints_tangent = pcl::PointCloud<PointXYZTangent>::Ptr(new pcl::PointCloud<PointXYZTangent>());
	pcl::PointCloud<PointXYZTangent>::Ptr off_scene_model_keypoints_tangent = pcl::PointCloud<PointXYZTangent>::Ptr(new pcl::PointCloud<PointXYZTangent>());

	pcl::PointCloud<PointType>::Ptr off_scene_model = pcl::PointCloud<PointType>::Ptr(new pcl::PointCloud<PointType>());
	pcl::PointCloud<PointType>::Ptr off_scene_model_keypoints = pcl::PointCloud<PointType>::Ptr(new pcl::PointCloud<PointType>());

	//Scene
	PointCloudType::Ptr captured_scene = PointCloudType::Ptr(new PointCloudType());
	PointCloudType::Ptr passthroughed_scene = PointCloudType::Ptr(new PointCloudType());
	PointCloudType::Ptr voxelgrid_filtered_scene = PointCloudType::Ptr(new PointCloudType());
	PointCloudType::Ptr segmented_scene = PointCloudType::Ptr(new PointCloudType());
	PointCloudType::Ptr statistical_filtered_scene = PointCloudType::Ptr(new PointCloudType());
	PointCloudType::Ptr scene = PointCloudType::Ptr(new PointCloudType());
	PointCloudType::Ptr scene_keypoints = PointCloudType::Ptr(new PointCloudType());
	pcl::PointCloud<PointXYZTangent>::Ptr scene_keypoints_tangent = pcl::PointCloud<PointXYZTangent>::Ptr(new pcl::PointCloud<PointXYZTangent>());


	//Others
	int prev_instances_size = 0; // for removing previous cloud
	boost::mutex mtx; //Mutex for locking
	pcl::console::TicToc tt; // Tictoc for process-time calculation

	
public:
	CustomVisualizer customViewer;

	DescriptorB2BTL_MEAM(std::queue<cv::Mat>* images_queue) { images_q = images_queue; }
	std::string getType();
	bool loadModel();
	bool prepareModelDescriptor();
	void _3D_Matching(const PointCloudType::ConstPtr &cloud);
};




#endif