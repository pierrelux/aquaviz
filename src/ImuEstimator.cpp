#include "LandmarkParser.h"
#include "PoseParser.h"

#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"
#include "visualization_msgs/MarkerArray.h"

#include <sstream>

visualization_msgs::MarkerArray createMarkerMessage(
		LandmarkParser::Points& landmarks) {

	visualization_msgs::MarkerArray markers_msg;
	markers_msg.markers.resize(landmarks.size());

	LandmarkParser::Points::const_iterator it;
	int i = 0;
	for (it = landmarks.begin(); it != landmarks.end(); it++, i++) {
		markers_msg.markers[i].header.frame_id = "/feature";
		markers_msg.markers[i].header.stamp = ros::Time::now();
		markers_msg.markers[i].ns = "basic_shapes";
		markers_msg.markers[i].id = 0;
		markers_msg.markers[i].type = visualization_msgs::Marker::POINTS;
		markers_msg.markers[i].action = visualization_msgs::Marker::ADD;
		markers_msg.markers[i].pose.position.x = it->x;
		markers_msg.markers[i].pose.position.y = it->y;
		markers_msg.markers[i].pose.position.z = it->z;
		markers_msg.markers[i].pose.orientation.x = 0.0;
		markers_msg.markers[i].pose.orientation.y = 0.0;
		markers_msg.markers[i].pose.orientation.z = 0.0;
		markers_msg.markers[i].pose.orientation.w = 1.0;
		markers_msg.markers[i].scale.x = 1.0;
		markers_msg.markers[i].scale.y = 1.0;
		markers_msg.markers[i].scale.z = 1.0;
		markers_msg.markers[i].color.r = 0.0f;
		markers_msg.markers[i].color.g = 1.0f;
		markers_msg.markers[i].color.b = 0.0f;
		markers_msg.markers[i].color.a = 1.0;
		markers_msg.markers[i].lifetime = ros::Duration();
	}

	return markers_msg;
}

geometry_msgs::PoseStamped createGeometryMessage(const PoseParser::Poses& poses) {
	geometry_msgs::PoseStamped msg;

	const PoseParser::Pose3D& pose = poses.front();

	msg.header.frame_id = "/attitude_pose";
	msg.pose.position.x = pose.position.x;
	msg.pose.position.y = pose.position.y;
	msg.pose.position.z = pose.position.z;
	msg.pose.orientation.x = pose.quaternion.x;
	msg.pose.orientation.y = pose.quaternion.y;
	msg.pose.orientation.z = pose.quaternion.z;
	msg.pose.orientation.w = pose.quaternion.w;

	return msg;
}

int main(int argc, char **argv) {
	LandmarkParser landmarkParser("landmarks.txt");
	PoseParser poseParser("pose.txt");

	// Initialize the fake node
	ros::init(argc, argv, "attitude_estimator");

	// Create publisher endpoints
	ros::NodeHandle n;
	ros::Publisher attitude_pub = n.advertise<geometry_msgs::PoseStamped> (
			"attitude", 1000);
	ros::Publisher marker_pub = n.advertise<visualization_msgs::MarkerArray> (
			"visual_markers", 1000);

	// Replay all the data at 1Hz
	LandmarkParser::const_iterator itLand = landmarkParser.begin();
	ros::Rate loop_rate(1);

	while (ros::ok() && itLand != landmarkParser.end()) {
		// Send features
		unsigned timestamp = itLand->first;
		LandmarkParser::Points points = itLand->second;
		visualization_msgs::MarkerArray markersMessage = createMarkerMessage(points);

		marker_pub.publish(markersMessage);

		// Send corresponding poses
		PoseParser::const_iterator itPoses = poseParser.find(timestamp);
		if (itPoses != poseParser.end()) {
			geometry_msgs::PoseStamped poses = createGeometryMessage(itPoses->second);

			attitude_pub.publish(poses);
		}

		ros::spinOnce();
		loop_rate.sleep();
		itLand++;
	}

	std::cout << "Done replaying data." << std::endl;
	return 0;
}

