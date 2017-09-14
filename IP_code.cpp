
#include <iostream>
#include <fstream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<stdio.h>
#include<math.h>
int check=1;
using namespace cv;
using namespace std;
void T(Mat img, int a[3][3]);


 int main( int argc, char** argv )
 {int data;
  FILE *file;

   
VideoCapture cap(0); //capture the video from external web cam

    if ( !cap.isOpened() )  // if not success, exit program
    {
         cout << "Cannot open the web cam" << endl;
         return -1;
    }
// enter your path directory in which image is saved 
					
					Mat img1;
					Mat HSV1;
					//int h,s,v,z=0;
					Point xp,ip(0,0),fp(0,0);
					int x,y;
					float dt,di=0.0;
				int xd,yd;
					
					
					//line(frame,Point(0,0),Point(50,50),(255,255,255),5);
					Size size1(550,400);
					Mat dst1;//dst image




					//For starting Camera

					while (true)
					    {
						
						bool bSuccess = cap.read(img1); // read a new frame from video

						 if (!bSuccess) //if not success, break loop
						{
						     cout << "Cannot read a frame from video stream" << endl;
						     break;
						}
						 
	

					
					resize(img1,dst1,size1);//resize imag
					rectangle(dst1, Point(225,150), Point(325,250),Scalar(0,255,0), 1);
					cvtColor(dst1,HSV1, COLOR_BGR2HSV);
				//	Vec3b intensity = HSV1.at<Vec3b>(0, 0);
					//k=intensity.val[2];
					//cout<<HSV.cols<<"\t"<<k<<"\n";

					    	imshow("opencvtest",dst1);
					//wait for 'SPACE' key press for 3ms. If 'esc' key is pressed, break loop 
						if (waitKey(3) == 32)   
						    break;

					}
int a[3][3];
//Threshold Snapshot
T(img1,a);

destroyAllWindows();		
   

    

   namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"



int LowH = a[0][1];
 int HighH = a[0][2];

 int LowS = a[1][1]; 
 int HighS = a[1][2];

 int LowV = a[2][1];
 int HighV = a[2][2];
 
 /*
 int LowH = 0;
 int HighH =64;

 int LowS =32; 
 int HighS =255;

 int LowV =148;
 int HighV =255;
 
*/
 //Create trackbars in "Control" window
// This below function will create a bars on Control window using that you can change value 

 cvCreateTrackbar("LowH", "Control", &LowH, 179); //Hue (0 - 179)
 cvCreateTrackbar("HighH", "Control", &HighH, 179);

 cvCreateTrackbar("LowS", "Control", &LowS, 255); //Saturation (0 - 255)
 cvCreateTrackbar("HighS", "Control", &HighS, 255);

 cvCreateTrackbar("LowV", "Control", &LowV, 255); //Value (0 - 255)
 cvCreateTrackbar("HighV", "Control", &HighV, 255);
//=======================================

  int l=0;
  file = fopen("/dev/ttyACM0", "w");
  int e=0;
  char servo[30];
    while (true)
    {
        Mat img;

        bool bSuccess = cap.read(img); // read a new frame from video

         if (!bSuccess) //if not success, break loop
        {
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }

		//RESIZE IMAGE A DRAW
		
		Size size(550,400);
		Mat Original;//dst image
		resize(img,Original,size);//resize imag
		rectangle(Original, Point(200,125), Point(350,285),Scalar(0,255,0), 1);
  Mat HSV;		
//Convert the captured frame from BGR to HSV
  	cvtColor(Original,HSV, COLOR_BGR2HSV); 
 
  	Mat Thresholded;
//Threshold the image
  	inRange(HSV, Scalar(LowH, LowS, LowV), Scalar(HighH, HighS, HighV), Thresholded); 
      
//morphological opening (remove small objects from the foreground)
 	 erode(Thresholded, Thresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
  	dilate(Thresholded, Thresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

//morphological closing (fill small holes in the foreground)
  	dilate( Thresholded, Thresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
  	erode(Thresholded, Thresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );


//DETECTING CIRCLE
GaussianBlur( Thresholded, Thresholded,Size(9, 9), 2, 2 );//applied gaussian blur

    vector<Vec3f> circles;

HoughCircles(Thresholded, circles, CV_HOUGH_GRADIENT,
          2,   // accumulator resolution (size of the image / 2)
          5,  // minimum distance between two circles
          10, // Canny high threshold
          100, // minimum number of votes
          0,1000); // min and max radius

    
       vector<Vec3f>::
              const_iterator itc= circles.begin();

int maxradius=0,j=0;
       for( size_t i = 0; i < circles.size(); i++ )
  {
      Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
      int radius = cvRound(circles[i][2]);

if (radius>=maxradius)
{maxradius=radius;
j=i;
}
if(maxradius==0)
{data=9;
	putText(Original, 
										    "Turn Clockwise to find Ball",
										    Point(200,350), // Coordinates
										    FONT_HERSHEY_COMPLEX_SMALL, // Font
										    1.0, // Scale. 2.0 = 2x bigger
										    Scalar(255,0,0), // Color
										    1, // Thickness
										    CV_AA); // Anti-alias

}
   }
//-------------------------------------
 
 /*// open a file in write mode.
   ofstream outfile;
   outfile.open("a.txt");
   outfile << data << endl;
      outfile.close();*/
                         

       
	//printf("%d",maxradius);	

//---------------------------------------------
if (j< circles.size())
{	
     Point center1(cvRound(circles[j][0]), cvRound(circles[j][1]));
//circle center
      circle( Original, center1, 3, Scalar(0,255,0), -1, 8, 0 );
      // circle outline
    circle( Original, center1, maxradius, Scalar(0,0,255), 3, 8, 0 );
	xp=center1;


	





					if (cvRound(circles[j][0])<200)
					{if (cvRound(circles[j][1])<125)
						{ data=7;
							putText(Original, 
										    "LEFT UP",
										    Point(200,205), // Coordinates
										    FONT_HERSHEY_COMPLEX_SMALL, // Font
										    1.0, // Scale. 2.0 = 2x bigger
										    Scalar(255,255,255), // Color
										    1, // Thickness
										    CV_AA); // Anti-alias
						}
					 else if (cvRound(circles[j][1])>=125)
						{ if (cvRound(circles[j][1])<=285)
							{data=4;
								 putText(Original, 
										    "LEFT",
										    Point(200,205), // Coordinates
										    FONT_HERSHEY_COMPLEX_SMALL, // Font
										    1.0, // Scale. 2.0 = 2x bigger
										    Scalar(255,255,255), // Color
										    1, // Thickness
										    CV_AA); // Anti-alias
							}
						 else if (cvRound(circles[j][1])>285)
					 	{ data=3;
							putText(Original, 
										    "LEFT DOWN",
										    Point(200,205), // Coordinates
										    FONT_HERSHEY_COMPLEX_SMALL, // Font
										    1.0, // Scale. 2.0 = 2x bigger
										    Scalar(255,255,255), // Color
										    1, // Thickness
										    CV_AA); // Anti-alias
						}
						}
					 
					}
					else if (cvRound(circles[j][0])>350)
					{if (cvRound(circles[j][1])<125)
						{ data=7;
							putText(Original, 
										    "RIGHT UP",
										    Point(200,205), // Coordinates
										    FONT_HERSHEY_COMPLEX_SMALL, // Font
										    1.0, // Scale. 2.0 = 2x bigger
										    Scalar(255,255,255), // Color
										    1, // Thickness
										    CV_AA); // Anti-alias
						}
					 else if (cvRound(circles[j][1])>=125) 
						{ if (cvRound(circles[j][1])<=285)
							{data=6;
								 putText(Original, 
										    "RIGHT",
										    Point(200,205), // Coordinates
										    FONT_HERSHEY_COMPLEX_SMALL, // Font
										    1.0, // Scale. 2.0 = 2x bigger
										    Scalar(255,255,255), // Color
										    1, // Thickness
										    CV_AA); // Anti-alias
							}
						else if (cvRound(circles[j][1])>285)
					 	{data=3;
							 putText(Original, 
										    "RIGHT DOWN",
										    Point(200,205), // Coordinates
										    FONT_HERSHEY_COMPLEX_SMALL, // Font
										    1.0, // Scale. 2.0 = 2x bigger
										    Scalar(255,255,255), // Color
										    1, // Thickness
										    CV_AA); // Anti-alias
						}
						}
					 
					}
					else if (cvRound(circles[j][0])<=350)
					{if (cvRound(circles[j][0])>=200)
						{
						if (cvRound(circles[j][1])<125)
							{ data=7;
								putText(Original, 
											    "CENTER UP",
											    Point(200,205), // Coordinates
											    FONT_HERSHEY_COMPLEX_SMALL, // Font
											    1.0, // Scale. 2.0 = 2x bigger
											    Scalar(255,255,255), // Color
											    1, // Thickness
											    CV_AA); // Anti-alias
							}
						
					      else if (cvRound(circles[j][1])>=125)
						{ if (cvRound(circles[j][1])<=285)
							{ data=0;
								putText(Original, 
										    "CENTER",
										    Point(200,205), // Coordinates
										    FONT_HERSHEY_COMPLEX_SMALL, // Font
										    1.0, // Scale. 2.0 = 2x bigger
										    Scalar(255,255,255), // Color
										    1, // Thickness
										    CV_AA); // Anti-alias

							}
							
						else if (cvRound(circles[j][1])>285)
					 		{data=3;
								 putText(Original, 
										    "CENTER DOWN",
										    Point(200,205), // Coordinates
										    FONT_HERSHEY_COMPLEX_SMALL, // Font
										    1.0, // Scale. 2.0 = 2x bigger
										    Scalar(255,255,255), // Color
										    1, // Thickness
										    CV_AA); // Anti-alias
							}
						}
					 
						}
					}

}
if(data==0)
{if(maxradius<=30 && maxradius >0)
{data=8;
putText(Original, 
										    "Forwad",
										    Point(200,350), // Coordinates
										    FONT_HERSHEY_COMPLEX_SMALL, // Font
										    1.0, // Scale. 2.0 = 2x bigger
										    Scalar(255,0,0), // Color
										    1, // Thickness
										    CV_AA); // Anti-alias
}

else if(maxradius>=75)
{data=5;
	putText(Original, 
										    "Backward",
										    Point(200,350), // Coordinates
										    FONT_HERSHEY_COMPLEX_SMALL, // Font
										    1.0, // Scale. 2.0 = 2x bigger
										    Scalar(255,0,0), // Color
										    1, // Thickness
										    CV_AA); // Anti-alias
}

else
{data=0;
	putText(Original, 
										    "NO MOVEMENT",
										    Point(200,350), // Coordinates
										    FONT_HERSHEY_COMPLEX_SMALL, // Font
										    1.0, // Scale. 2.0 = 2x bigger
										    Scalar(255,0,0), // Color
										    1, // Thickness
										    CV_AA); // Anti-alias
}	
}
Point cp(275,200);
if(check==1)
{
cout<<"\n"<<check;
ip=xp;
fp=xp;
check=0;
}
else
{fp=xp;}
//cout<<"\n\n";
//cout<<"\n"<<ip.x<<"\t"<<ip.y;
//cout<<"\n"<<fp.x<<"\t"<<fp.y;


xd=fp.x-cp.x;
yd=fp.y-cp.y;

dt=sqrt(xd*xd+yd*yd);
int mapped;
mapped=(dt/250)*10;
//cout<<"\nDistance="<<dt;

//line(Original,Point(cp.x,cp.y), Point(550,cp.y), (255,255,255), 1);
//line(Original,Point(fp.x,ip.y), Point(cp.x,cp.y), (255,255,255), 1);
//float angle = atan2(fp.y - ip.y, fp.x - ip.x)*(-180)/3.14159;
//cout<<"\n"<<angle;
ip=fp;


     //serial output
     
           if(l==8)
            {
				//printf("%s",servo);
            //file = fopen("/dev/ttyACM0", "w");
     if(data==3)
     {
				fprintf (file, "%d\n", data); //Writing to the file
				              printf("%d",data);

			}
		else if (data==7)
			{
								fprintf (file, "%d\n", data); //Writing to the file
				              printf("%d",data);

			}
			else
			{								fprintf (file, "%d%d\n", data,mapped); //Writing to the file
								              printf("%d%d\n",data,mapped);


			}
              // fclose(file);

    
    

      l=0;
      e=0;
      while(e<=19)
      {servo[e]=0;
		  e=e+1;
		  }
      e=0;
  }
      l=l+1;

servo[e]=data;
e=e+1;

        namedWindow("image",CV_WINDOW_AUTOSIZE);
        namedWindow("Original",CV_WINDOW_AUTOSIZE);
        imshow("image", Thresholded); //show the thresholded image
  	imshow("Original", Original); //show the original image

/*z++;
if(z==29) ip=fp;*/
//wait for 'esc' key press for 3ms. If 'esc' key is pressed, break loop 



   // write the data at the screen.
        if (waitKey(3) == 27)   
            break; 
    }             
          fclose(file);
                                    

   return 0;

}





//Thresholding fn
void T(Mat img,int a[3][3])
{Mat HSV,dst;
Size size(550,400);
int h,s,v;
int x,y;
resize(img,dst,size);//resize imag
cvtColor(dst,HSV, COLOR_BGR2HSV);
//Vec3b intensity = HSV.at<Vec3b>(0, 0);

int hs=0, ss=0, vs=0, n=0,hmin=255,hmax=0,vmin=255,vmax=0,smin=255,smax=0;
float h6=0,h12=0,h18=0,v85=0,v170=0,v255=0,s85=0,s170=0,s255=0; 


for(y=150;y<250;y++)
{
   for(x=225;x<325;x++)
    {
        // get pixel
        Vec3b color = HSV.at<Vec3b>(Point(x,y));
	h=color.val[0];
	s=color.val[1];
	v=color.val[2];
	hs=hs+h;
	ss=ss+s;
	vs=vs+v;
if(h>hmax)
hmax=h;
if(v>vmax)
vmax=v;
if(s>smax)
smax=s;
if(h<hmin)
hmin=h;
if(v<vmin)
vmin=v;
if(s<smin)
smin=s;
if(h>=0 && h<=60)
h6++;
else if(h<=120)
h12++;
else if(h<=180)
h18++;
if(s>=0 && s<=85)
s85++;
else if(s<=170)
s170++;
else if(s<=255)
s255++;
if(v>=0 && v<=85)
v85++;
else if(v<=170)
v170++;
else if(v<=255)
v255++;
n++;
       
}

}


int ha,sa,va;
ha=hs/n;
sa=ss/n;
va=vs/n;
a[0][0]=ha;
a[0][1]=hmin;
a[0][2]=hmax;
a[1][0]=sa;
a[1][1]=smin;
a[1][2]=smax;
a[2][0]=va;
a[2][1]=vmin;
a[2][2]=vmax;
// To show image 
    	imshow("opencvtest",dst);
}


