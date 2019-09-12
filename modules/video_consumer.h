#ifndef VIDEO_CONSUMER_H
#define VIDEO_CONSUMER_H

#include <base_factory.h>

#include <vector>
#include <thread>
#include <string>
#include <opencv2/core/cvstd.hpp>
#include <opencv2/opencv.hpp>
#include <initializer_list>

#include <mutex>
#include <condition_variable>
#include <atomic>

class Supervisor;

class Video_consumer :
    public Base_factory
{
public:
    Video_consumer();

    Video_consumer(const Video_consumer&)                 = delete;
    Video_consumer(Video_consumer&& )                     = delete;
    Video_consumer& operator = (const Video_consumer& )   = delete;
    Video_consumer& operator = (Video_consumer&& )        = delete;

    ~Video_consumer();
    void b_apply(void *);
    void b_start(void *) override;
    void b_stop(void *)  override;
    const char* b_type_name() override ;

    std::vector<cv::Mat>             vec_frame;
    std::queue<cv::Mat*>             que_frame;

    std::mutex                  mt;
    std::condition_variable     cv;
    bool notified               = {false};

private:

    std::atomic<bool> b_stop_thread   = {false};
    std::thread std_thread;

};

#endif // VIDEO_CONSUMER_H
