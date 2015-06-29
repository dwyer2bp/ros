// this should really be in the implementation (.cpp file)
#include <pluginlib/class_list_macros.h>
#include <KinectTopDownView.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <image_transport/image_transport.h>
#include <pcl/filters/passthrough.h>
#include <pcl/point_types.h>
#include <pcl_ros/point_cloud.h>

// watch the capitalization carefully
PLUGINLIB_EXPORT_CLASS(kinect_proc::KinectTopDownView, nodelet::Nodelet) 

namespace kinect_proc
{
    void KinectTopDownView::onInit() 
    {
        NODELET_DEBUG("Initializing nodelet...");
    		//ros::NodeHandle& private_nh = getPrivateNodeHandle();
				scan_center = 0.0;
				scan_delta = 0.05;
				scan_width = 0.2;
				scan_direction = 0; //0-pos, 1-neg
				scan_min = -1.5;
				scan_max = 1.5;
				ros::NodeHandle g_nh;
				pass.setFilterFieldName ("y");
				pass.setFilterLimits( scan_center - 0.05, scan_center + 0.05);
				image_transport::ImageTransport it(g_nh);
				pub_it = it.advertise("kinect_topdown_img", 1);
				sub = g_nh.subscribe("/camera/depth/points", 1, &KinectTopDownView::callback, this);
    }
		//void MyNodeletClass::callback(const sensor_msgs::PointCloud2::ConstPtr msg)
    void KinectTopDownView::callback(const pcl::PointCloud<pcl::PointXYZ>::Ptr& msg)
		{
			
				//PCL Code
				pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>);
				//pcl::PassThrough<pcl::PointXYZ> pass;
				//std::vector<pcl::PointXYZ, Eigen::aligned_allocator<pcl::PointXYZ> > cloudData, cloudDataFloor;
				//pcl::fromROSMsg(*msg, *in_cloud);
				pass.setInputCloud(msg);
				pass.filter (*cloud_filtered);
				//cloudData = cloud_filtered->points;
				//pass.setFilterLimits( 0.5, 1.5);
			  //pass.filter (*cloud_filtered);
	  		//cloudDataFloor = cloud_filtered->points;
				
	
				int numpoints;
				int new_x, new_y;
				cv::Mat imgRGBcv = cv::Mat::zeros(480,640,CV_8UC3);
		
				//Mid range
				//numpoints = cloudData.size();
				numpoints = cloud_filtered->points.size();
				for(int i = 0; i < numpoints; i++)
				{
					//new_x = mapFromPointToPixel(cloudData[i].x, -5.0, 5.0, 80, 560);
					//new_y = mapFromPointToPixel(cloudData[i].z, 0, 10, 480, 0);
					new_x = mapFromPointToPixel(cloud_filtered->points[i].x, -5.0, 5.0, 80, 560);
					new_y = mapFromPointToPixel(cloud_filtered->points[i].z, 0, 10, 480, 0);
					imgRGBcv.at<cv::Vec3b>(new_y, new_x)[0] = 255;	//Set red channels only
				}
				//Commented out floor, too much processing...
				//Floor
				//numpoints = cloudDataFloor.size();
				//for(int i = 0; i < numpoints; i++)
				//{
				//	new_x = mapFromPointToPixel(cloudDataFloor[i].x, -5.0, 5.0, 80, 560);
				//	new_y = mapFromPointToPixel(cloudDataFloor[i].z, 0, 10, 480, 0);
				//	imgRGBcv.at<cv::Vec3b>(new_y, new_x)[1] = 255;	//Set green channels only
				//}

				//Output image
				sensor_msgs::ImagePtr img_msg = cv_bridge::CvImage(std_msgs::Header(), "rgb8", imgRGBcv).toImageMsg();
				pub_it.publish(img_msg);
		}

		int KinectTopDownView::mapFromPointToPixel(float x, float xmin, float xmax, float pmin, float pmax)
		{
				 int scaler = (pmax-pmin)/(xmax-xmin);
				 int offset = pmin - xmin*scaler;

				 return (int)( offset + x*scaler );
		}
}
