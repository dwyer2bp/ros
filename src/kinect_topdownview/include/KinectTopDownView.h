#include <nodelet/nodelet.h>
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <image_transport/image_transport.h>
#include <pcl/point_types.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/filters/passthrough.h>

namespace kinect_proc
{

    class KinectTopDownView : public nodelet::Nodelet
    {
        public:
            virtual void onInit();
						float scan_center;
						float scan_delta;
						float scan_width;
						int scan_direction;
						float scan_min;
						float scan_max;
						pcl::PassThrough<pcl::PointXYZ> pass;
						std::vector<pcl::PointXYZ, Eigen::aligned_allocator<pcl::PointXYZ> > cloudData, cloudDataFloor;
				private:
						image_transport::Publisher pub_it;
						ros::Subscriber sub;
						//image_transport::ImageTransport *imagetransport_it;
						//void callback(const sensor_msgs::PointCloud2::ConstPtr msg);
						void callback(const pcl::PointCloud<pcl::PointXYZ>::Ptr& msg);
					  int mapFromPointToPixel(float x, float xmin, float xmax, float pmin, float pmax);
    };

}
