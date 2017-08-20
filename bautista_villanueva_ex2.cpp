/*
Name: Samuel Tadeo L. Bautista
Student number: 2014-72738
Name: Zoe Kirsten T. Villanueva
Student number: 2014-46051
Section: U-2L
Date: August 15, 2017
Description:

*/

#include <iostream>
#include <cstdio>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <functional>
using namespace cv;
using namespace std;

int GRAPH_WIDTH = 256;
int GRAPH_HEIGHT = 256;

uchar lowcontrast(uchar channel) {
  return (0.004 * channel * channel) - channel * 0.002;
}

uchar highcontrast(uchar channel) {
  return sqrt(channel) * 16;
}

uchar underexposed(uchar channel) {
  return sqrt(channel*2) * 11;
}


Mat makeGraph(function<uchar (uchar)> fxn) {
  Mat graph(256, 256, CV_8UC3, Scalar(256, 256, 256));
  int x, y = 0;
  for (int i=0; i<GRAPH_HEIGHT; ++i ) {
    for (int j=0; j<GRAPH_WIDTH; ++j) {

      x = j;
      y = abs(i - GRAPH_HEIGHT + 1);

      if (i == j) {
        graph.at<Vec3b>(y, x)[0] = 0;
        graph.at<Vec3b>(y, x)[1] = 0;
        graph.at<Vec3b>(y, x)[2] = 0;
      } else if (fxn(j) == i) {
        graph.at<Vec3b>(y, x)[0] = 0;
        graph.at<Vec3b>(y, x)[1] = 0;
        graph.at<Vec3b>(y, x)[2] = 255;
      } else {
        graph.at<Vec3b>(y, x)[0] = 255;
        graph.at<Vec3b>(y, x)[1] = 255;
        graph.at<Vec3b>(y, x)[2] = 255;
      }
    }
  }

  return graph;
}

void applyFunction(function<uchar (uchar)> fxn, Mat image) {
  for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			Vec3b intensity =  image.at<Vec3b>(i, j);
			uchar blue = intensity.val[0];
			uchar green = intensity.val[1];
			uchar red = intensity.val[2];

			//blue
			image.at<Vec3b>(i, j)[0] = fxn(blue);

			//green
			image.at<Vec3b>(i, j)[1] = fxn(green);

			//red
			image.at<Vec3b>(i, j)[2] = fxn(red);
		}
	}
}



int main(int argc, char *argv[]) {
  // Mat lowcontrastImage = imread("lowcontrast.jpg", 1);
  // Mat highcontrastImage = imread("highcontrast.jpg", 1);
  Mat underexposedImage = imread("underexposed.jpg", 1);

  // Mat lowcontrastGraph = makeGraph(lowcontrast);
  // Mat highcontrastGraph = makeGraph(highcontrast);
  Mat underexposedGraph = makeGraph(underexposed);
  
  // applyFunction(lowcontrast, lowcontrastImage);
  // applyFunction(highcontrast, highcontrastImage);
  applyFunction(underexposed, underexposedImage);

  // imshow("lowcontrastImage.jpg", lowcontrastImage);
  // imshow("highcontrastImage.jpg", highcontrastImage);
  imshow("underexposedImage.jpg", underexposedImage);

  // imshow("highcontrastGraph.jpg", highcontrastGraph);
  // imshow("lowcontrastGraph.jpg", lowcontrastGraph);
	imshow("underexposedGraph.jpg", underexposedGraph);

	waitKey(0);

  return 0;
}