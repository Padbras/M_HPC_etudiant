#include <opencv2/opencv.hpp>
#include "utils.hpp"

int main(int argc, char ** argv) 
{ 
    if (argc != 2) 
    {
        std::cerr << "usage: " << argv[0] << " <filename> \n";
        exit(-1);
    }
    const char * filename = argv[1];
    const double COEF = 0.5;
    std::string basename, extension;
    getBasenameAndExtension(filename, basename, extension);

    // load input image
    cv::Mat imgInput = cv::imread(filename);
    if (imgInput.channels()!=3 or imgInput.depth()!=CV_8U)
    {
        std::cerr << "error: only 3-channel 8-bits images are supported\n";
        exit(-1);
    }



    // operator*=
    timePoint_t tpMul0 = now();
    cv::Mat imgMul = imgInput.clone();
    cv::Mat imgMul2 = imgInput.clone();
    cv::Mat imgMul3 = imgInput.clone();
    imgMul *= COEF;
    timePoint_t tpMul1 = now();

    // foreach loop
    auto f =[COEF](cv::Vec3b &p, const int*){p*=COEF;};
    timePoint_t tpMul4 = now();
    imgMul3.forEach<cv::Vec3b>(f);
    timePoint_t tpMul5 = now();
  
    // 2D loop
    timePoint_t tpMul2 = now();    
    for(int i = 0; i < imgInput.rows; i++)
      {
      for (int j = 0; j < imgInput.cols; j++)
	{
	  imgMul2.at<cv::Vec3b>(i,j) *=COEF;	  
	}
      }
  
    timePoint_t tpMul3  = now();

    // print computation times
    std::cout << "imgMul: " << duration(tpMul0, tpMul1) << " s\n";
    std::cout << "2D: " << duration(tpMul2, tpMul3) << " s\n";
    std::cout << "foreach: " << duration(tpMul4, tpMul5) << " s\n";
    // TODO

    // write image files
    imwrite(basename + "_imgMul" + extension, imgMul);
    imwrite(basename + "_imgMul2" + extension, imgMul2);
    imwrite(basename + "_imgMul3" + extension, imgMul3);

    // TODO

    // display images
    cv::imshow("imgInput", imgInput);
    cv::imshow("imgMul", imgMul);
    cv::imshow("imgMul2", imgMul2);
    cv::imshow("imgMul3", imgMul3);
    // TODO

    // wait for "esc"
    while (true)
    {
        int k = cv::waitKey(100) % 0x100;
        if (k == 27)
            break;
    }

    return 0;
}


