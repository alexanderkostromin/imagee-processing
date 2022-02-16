#include <opencv2/opencv.hpp>
#include <cmath>
#include <iostream>
#include<chrono>


int main() {
    cv::Mat img(180, 768, CV_8UC1);

    for (size_t j = 0; j < 180; j++)
    {
        for (size_t i = 0; i < 768; i ++)
        {
            img.at<uchar>(j, i) = i / 3;
        }
    }
   
    cv::Mat img2(180, 768, CV_8UC1);

    auto start = std::chrono::high_resolution_clock::now();

    img.convertTo(img2, CV_32F, 1 / 255.0);
    cv::pow(img2, 2.3, img2);
    img2.convertTo(img2, CV_8UC1, 255);
    auto stop = std::chrono::high_resolution_clock::now();
    auto runTime1 = std::chrono::duration_cast< std::chrono::microseconds> (stop - start);
    
    cv::Mat img3(180, 768, CV_8UC1);

    img.copyTo(img3);

    auto start2= std::chrono::high_resolution_clock::now();

    for (size_t j = 0; j < 180; j++)
    {
        for (size_t i = 0; i < 768; i++)
        {
            img3.at<uint8_t>(j, i) = pow((i / 3) / 255.0, 2.3) * 255;
        }
    }
    auto stop2 = std::chrono::high_resolution_clock::now();
    auto runTime2 = std::chrono::duration_cast<std::chrono::microseconds> (stop2 - start2);
    
    cv::Mat img4(180, 768, CV_8UC1);
    
    img(cv::Rect2d(0, 0, 768, 60)).copyTo(img4(cv::Rect2d(0, 0, 768, 60)));
    img2(cv::Rect2d(0, 0, 768, 60)).copyTo(img4(cv::Rect2d(0, 60, 768, 60)));
    img3(cv::Rect2d(0, 0, 768, 60)).copyTo(img4(cv::Rect2d(0, 120, 768, 60)));

    cv::rectangle(img4, cv::Rect2d(0, 0, 768, 60), {100});
    cv::rectangle(img4, cv::Rect2d(0, 60, 768, 60), { 150 });
    cv::rectangle(img4, cv::Rect2d(0, 120, 768, 60), { 250 });
  
    std::cout << "Time for 1 GC = " << static_cast<int>(runTime1.count())/1000.0F << " ms" << '\n';
    std::cout << "Time for 2 GC = " << static_cast<int>(runTime2.count())/1000.0F << " ms" << '\n';

    cv::imwrite("lab03.png", img4);
    cv::imshow("lab03.png", img4);


    cv::waitKey(0);

}