#include <opencv2/opencv.hpp>
#include "utils.hpp"

int main()
{

    cv::Mat M = (cv::Mat_<float>(2, 3) << 1, 2, 3, 4, 5, 6);
    std::cout << "---- M ----\n" << M << std::endl;

    cv::Mat I = cv::Mat::eye(3, 3, CV_64F);
    std::cout << "---- I ----\n" << I << std::endl;
    
    cv::Mat u = (cv::Mat_<float>(3, 1) << 1, 2, 3);
    std::cout << "---- u ----\n" << u << std::endl;

    cv::Mat v = (cv::Mat_<float>(3, 1) << 1, 1, 1);
    std::cout << "---- v ----\n" << v << std::endl;

    std::cout << "Produit matriciel de M*v" << std::endl;
    std::cout << M*v << std::endl;

    std::cout << "Produit scalaire de u.v" << std::endl;
    std::cout << u.dot(v) << std::endl;

    std::cout << "Element (0,1) de M" << std::endl;    
    std::cout << M.at<float>(0, 1) << std::endl;
    
    std::cout << "FMT_CSV" << std::endl; 
    std::cout <<  cv::format(M, cv::Formatter::FMT_CSV) << std::endl;
    
    cv::Mat P = cv::ml::TrainData::loadFromCSV("TP_OpenCV_matrix.csv", 0, -2, 0)->getSamples();
    std::cout << "loadFromCSV" << std::endl; 
    std::cout <<  cv::format(P, cv::Formatter::FMT_CSV) << std::endl;

    return 0;
}

