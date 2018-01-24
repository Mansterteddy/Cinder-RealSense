#include <iostream>
#include "rs.hpp"

using namespace std;

int const INPUT_WIDTH = 640;
int const INPUT_HEIGHT = 480;
int const FRAMERATE = 30;

rs::context _rs_ctx;
rs::device& _rs_camera = *_rs_ctx.get_device(0);
rs::intrinsics _depth_intrin;
rs::intrinsics _color_intrin;

bool initialize_streaming()
{
    bool success = false;
    if(_rs_ctx.get_device_count() > 0)
    {
        _rs_camera.enable_stream(rs::stream::color, INPUT_WIDTH, INPUT_HEIGHT, rs::format::rgb8, FRAMERATE);
        _rs_camera.enable_stream(rs::stream::depth, INPUT_WIDTH, INPUT_HEIGHT, rs::format::z16, FRAMERATE);
        _rs_camera.start();

        success = true;
    }
    return success;
}

int main()
{
    cout<<"Hello, RealSense!"<<endl;
    rs::log_to_console(rs::log_severity::warn);

    if(!initialize_streaming())
    {
        cout<<"Unable to locare a camera"<<std::endl;
        rs::log_to_console(rs::log_severity::fatal);
        return EXIT_FAILURE;
    }

    cout<<"Initialize Streaming!"<<endl;
    _rs_camera.stop();
    return 0;
}
