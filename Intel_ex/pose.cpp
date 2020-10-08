#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API

/** declare pipes and start then with config */

// Declare RealSense pipeline, encapsulating the actual device and sensors
rs2::pipeline pipe;
// Create a configuration for configuring the pipeline with a non default profile
rs2::config cfg;
// Add pose stream
cfg.enable_stream(RS2_STREAM_POSE, RS2_FORMAT_6DOF);
// Start pipeline with chosen configuration
pipe.start(cfg);


/** wait for new frame data and get the pose info from it */

// Main loop
while (true)
{
    // Wait for the next set of frames from the camera
    auto frames = pipe.wait_for_frames();
    // Get a frame from the pose stream
    auto f = frames.first_or_default(RS2_STREAM_POSE);

	/*We cast the frame that arrives to `pose_frame` 
		in order to access its `pose_data`.cpp*/

	// Cast the frame to pose_frame and get its data
	auto pose_data = f.as<rs2::pose_frame>().get_pose_data();


	/** query dat that we care about here
	  -> distance from starting point */

	// Print the x, y, z values of the translation,
	//		relative to initial position

	std::cout << "\r" << "Device Position: " 
		<< std::setprecision(3) << std::fixed << pose_data.translation.x 
		<< " " << pose_data.translation.y << " " 
		<< pose_data.translation.z << " (meters)";

} //close while loop


