#include <librealsense2/rs.hpp>     // Include RealSense Cross Platform API
#include "example.hpp"              // Include short list of convenience functions for rendering

// Create a simple OpenGL window for rendering:
window app(1280, 960, "CPP Multi-Camera Example");
rs2::context ctx;    // Create librealsense context for managing devices
rs2::colorizer      colorizer;      // Utility class to convert depth data RGB
std::vector<rs2::pipeline>  pipelines;

// Start a streaming pipe per each connected device
for (auto&& dev : ctx.query_devices())
{
    rs2::pipeline pipe(ctx);
    rs2::config cfg;
    cfg.enable_device(dev.get_info(RS2_CAMERA_INFO_SERIAL_NUMBER));
    pipe.start(cfg);
    pipelines.emplace_back(pipe);
}

rs2::pipeline pipe(ctx);
pipe.start(cfg);

while (app) {
	// Collect the new frames from all the connected devices
	std::vector<rs2::frame> new_frames;
	for (auto &&pipe : pipelines)
	{
		rs2::frameset fs;
		if (pipe.poll_for_frames(&fs))
		{
			for (rs2::frame& f : fs)
				new_frames.emplace_back(f);
		}
	}

	if (pipe.poll_for_frames(&fs)) {

	for (rs2::frame& f : fs) {
		new_frames.emplace_back(f);
	}

	// Convert the newly-arrived frames to render-friendly format
	for (const auto& frame : new_frames)
	{
	render_frames[frame.get_profile().unique_id()] = colorizer.process(frame);
	}

	app.show(render_frames);

	}
}

















