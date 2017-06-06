IplImage* captureImage(){
    IplImage *gray, *image;
    CvCapture *capture;

    capture = cvCaptureFromCAM(0);
    image = cvQueryFrame(capture);
    if(!image){
        puts("image capture failed");
        exit(1);
    }
    gray = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
    cvCvtColor(image, gray, CV_RGB2GRAY);

    cvReleaseCapture(&capture);

    return gray;
}

void capt_all(){
    IplImage* images[3];
    int i;
    for(i=0 ; i<3 ; i++){
       images[i] = captureImage();
    }
}
