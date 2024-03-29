/**
 * @author Pierre-Luc Bacon <pbacon@cim.mcgill.ca>
 */
#include <QApplication>
#include "TerrainViewUI.h"

#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"
#include "visualization_msgs/MarkerArray.h"

TerrainView* terrainView;

void attitudeCallback(
		const geometry_msgs::PoseStamped::ConstPtr& msg) {
	//ROS_INFO("Attitude : %s", msg->header.frame_id.c_str());
	double px = msg->pose.position.x;
	double py = msg->pose.position.y;
	double pz = msg->pose.position.z;
	terrainView->setIMUPosition(px, py, pz);

	double qx = msg->pose.orientation.x;
	double qy = msg->pose.orientation.y;
	double qz = msg->pose.orientation.z;
	double qw = msg->pose.orientation.w;
	terrainView->setIMURotation(qx, qy, qz, qw);
}

void markerCallback(
		const visualization_msgs::MarkerArray::ConstPtr& markers) {
	int size = markers->markers.size();
	//ROS_INFO("%d markers sent", size);

	for (int i = 0; i < size; i++) {
		//ROS_INFO("x %f y %f z %f", markers->markers[i].pose.position.x,
		//		markers->markers[i].pose.position.y,
		//		markers->markers[i].pose.position.z);

		terrainView->insertPoint(markers->markers[i].pose.position.x,
		                         markers->markers[i].pose.position.y,
		                         markers->markers[i].pose.position.z);
	}
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "listener");

	// Subscribe to topics
	ros::NodeHandle n;

	ros::Subscriber attitudeSubscriber = n.subscribe("attitude", 1000, attitudeCallback);

	ros::Subscriber markerSubscriber = n.subscribe("visual_markers", 1000, markerCallback);

	// QT Stuff
	QApplication app(argc, argv);

	terrainView = new TerrainView;
	terrainView->show();

	ros::AsyncSpinner spinner(4);
	spinner.start();

	// Block
	int ret = app.exec();

	spinner.stop();

	delete terrainView;

	return ret;
}
