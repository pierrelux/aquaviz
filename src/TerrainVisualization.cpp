#include <QApplication>
#include "TerrainViewUI.h"

#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"
#include "visualization_msgs/MarkerArray.h"

void attitudeCallback(const geometry_msgs::PoseStamped::ConstPtr& msg) {
	ROS_INFO("Attitude : %s", msg->header.frame_id.c_str());
}

void markerCallback(const visualization_msgs::MarkerArray::ConstPtr& markers) {
	int size = markers->markers.size();
	ROS_INFO("%d markers sent", size);

	//	for (int i = 0; i < size; i++) {
	//		ROS_INFO("%f", markers->markers[i].pose.position.x);
	//	}
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "listener");

	ros::NodeHandle n;
	ros::Subscriber attitudeSubscriber = n.subscribe("attitude", 1000,
			attitudeCallback);
	ros::Subscriber markerSubscriber = n.subscribe("visual_markers", 1000,
			markerCallback);

	// QT Stuff
	QApplication app(argc, argv);

	TerrainView myTerrainView;
	myTerrainView.show();

	// Use 4 threads
	ros::AsyncSpinner spinner(4);
	spinner.start();

	// Block
	int ret = app.exec();
	spinner.stop();

	return ret;
}
