/*******************************************************
 * Copyright (C) 2019, Aerial Robotics Group, Hong Kong University of Science and Technology
 * 
 * This file is part of VINS.
 * 
 * Licensed under the GNU General Public License v3.0;
 * you may not use this file except in compliance with the License.
 *
 * Author: Qin Tong (qintonguav@gmail.com)
 *******************************************************/

#pragma once

#include <cstdio>
#include <iostream>
#include <queue>
#include <execinfo.h>
#include <csignal>
#include <opencv2/opencv.hpp>
#include <eigen3/Eigen/Dense>
#include <unordered_set>

#include "camodocal/camera_models/CameraFactory.h"
#include "camodocal/camera_models/CataCamera.h"
#include "camodocal/camera_models/PinholeCamera.h"
#include "../estimator/parameters.h"
#include "../utility/tic_toc.h"

using namespace std;
using namespace camodocal;
using namespace Eigen;

void reduceVector(vector<cv::Point2f> &v, vector<uchar> status);
void reduceVector(vector<int> &v, vector<uchar> status);

// added by myself
void reduceVector(vector<float> &v, vector<uchar> status);

class FeatureTracker
{
public:
    FeatureTracker();
    map<int, vector<pair<int, Eigen::Matrix<double, 11, 1>>>> trackImage(double _cur_time, const cv::Mat &_img, const cv::Mat &_img1 = cv::Mat());
    void setMask();
    void readIntrinsicParameter(const vector<string> &calib_file);
    void showUndistortion(const string &name);
    void rejectWithF();
    void undistortedPoints();
    vector<cv::Point2f> undistortedPts(vector<cv::Point2f> &pts, camodocal::CameraPtr cam);
    vector<cv::Point2f> ptsVelocity(vector<int> &ids, vector<cv::Point2f> &pts, 
                                    map<int, cv::Point2f> &cur_id_pts, map<int, cv::Point2f> &prev_id_pts);
    void showTwoImage(const cv::Mat &img1, const cv::Mat &img2, 
                      vector<cv::Point2f> pts1, vector<cv::Point2f> pts2);
    void drawTrack(const cv::Mat &imLeft, const cv::Mat &imRight, 
                                   vector<int> &curLeftIds,
                                   vector<cv::Point2f> &curLeftPts, 
                                   vector<cv::Point2f> &curRightPts,
                                   map<int, cv::Point2f> &prevLeftPtsMap);
    void setPrediction(map<int, Eigen::Vector3d> &predictPts);
    double distance(cv::Point2f &pt1, cv::Point2f &pt2);
    void removeOutliers(set<int> &removePtsIds);
    cv::Mat getTrackImage();
    bool inBorder(const cv::Point2f &pt);

    int row, col;
    cv::Mat imTrack;
    cv::Mat mask;
    cv::Mat fisheye_mask;
    cv::Mat prev_img, cur_img;
    vector<cv::Point2f> n_pts;
    vector<cv::Point2f> predict_pts;
    vector<cv::Point2f> predict_pts_debug;
    vector<cv::Point2f> prev_pts, cur_pts, cur_right_pts;
    vector<cv::Point2f> prev_un_pts, cur_un_pts, cur_un_right_pts;
    vector<cv::Point2f> pts_velocity, right_pts_velocity;
    vector<int> ids, ids_right;
    vector<int> track_cnt;
    map<int, cv::Point2f> cur_un_pts_map, prev_un_pts_map;
    map<int, cv::Point2f> cur_un_right_pts_map, prev_un_right_pts_map;
    map<int, cv::Point2f> prevLeftPtsMap;
    vector<camodocal::CameraPtr> m_camera;
    double cur_time;
    double prev_time;
    bool stereo_cam;
    int n_id;
    bool hasPrediction;

    // added by myself
    void saveImage(const int frameCnt, const set<int> keepIndex, const set<int> removeIndex);
    Eigen::Matrix2d computeHessian(const cv::Mat& image, const cv::Point2f& center, int winSize = 21);
    void getCovariance(const cv::Mat& cur_img, const cv::Mat& prev_img, 
                    const cv::Point2f& center, const int id, const double err, const bool right);
    void eraseMap(std::map<int,double>& flowVars, const std::vector<int>& ids);
    void getUndistortedCovs(const int& feature_id, bool right);
    double computeVariance(const cv::Mat& cur_img, const cv::Mat& prev_img,
                        const cv::Point2f& center, int winSize = 21);
    cv::Point2f undistortedToPixel(const Eigen::Vector3d &normPt);

    double fx_inv, fy_inv;
    map<int, double> flowVars;
    map<int, array<Eigen::Matrix2d, 2>> posCovs;
    map<int, array<Eigen::Matrix2d, 2>> un_posCovs;
};
