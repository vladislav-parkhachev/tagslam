// -*-c++-*---------------------------------------------------------------------------------------
// Copyright 2024 Bernd Pfrommer <bernd.pfrommer@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <message_filters/subscriber.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <message_filters/synchronizer.h>
#include <sensor_msgs/Image.h>

#include <memory>

namespace tagslam
{
class ApproxImageSync
{
  using Image = sensor_msgs::Image;
  using ImageConstPtr = sensor_msgs::ImageConstPtr;

public:
  explicit ApproxImageSync(const ros::NodeHandle & nh);
  ApproxImageSync(const ApproxImageSync &) = delete;
  ApproxImageSync & operator=(const ApproxImageSync &) = delete;

  void initialize();

  void callback2(const ImageConstPtr &, const ImageConstPtr &);
  void callback3(
    const ImageConstPtr &, const ImageConstPtr &, const ImageConstPtr &);
  void callback4(
    const ImageConstPtr &, const ImageConstPtr &, const ImageConstPtr &,
    const ImageConstPtr &);
  void callback5(
    const ImageConstPtr &, const ImageConstPtr &, const ImageConstPtr &,
    const ImageConstPtr &, const ImageConstPtr &);
  void callback6(
    const ImageConstPtr &, const ImageConstPtr &, const ImageConstPtr &,
    const ImageConstPtr &, const ImageConstPtr &, const ImageConstPtr &);
  void callback7(
    const ImageConstPtr &, const ImageConstPtr &, const ImageConstPtr &,
    const ImageConstPtr &, const ImageConstPtr &, const ImageConstPtr &,
    const ImageConstPtr &);
  void callback8(
    const ImageConstPtr &, const ImageConstPtr &, const ImageConstPtr &,
    const ImageConstPtr &, const ImageConstPtr &, const ImageConstPtr &,
    const ImageConstPtr &, const ImageConstPtr &);
  void callback9(
    const ImageConstPtr &, const ImageConstPtr &, const ImageConstPtr &,
    const ImageConstPtr &, const ImageConstPtr &, const ImageConstPtr &,
    const ImageConstPtr &, const ImageConstPtr &, const ImageConstPtr &);

private:
  typedef message_filters::sync_policies::ApproximateTime<Image, Image>
    ApproxPolicy2;
  typedef message_filters::sync_policies::ApproximateTime<Image, Image, Image>
    ApproxPolicy3;
  typedef message_filters::sync_policies::ApproximateTime<
    Image, Image, Image, Image>
    ApproxPolicy4;
  typedef message_filters::sync_policies::ApproximateTime<
    Image, Image, Image, Image, Image>
    ApproxPolicy5;
  typedef message_filters::sync_policies::ApproximateTime<
    Image, Image, Image, Image, Image, Image>
    ApproxPolicy6;
  typedef message_filters::sync_policies::ApproximateTime<
    Image, Image, Image, Image, Image, Image, Image>
    ApproxPolicy7;
  typedef message_filters::sync_policies::ApproximateTime<
    Image, Image, Image, Image, Image, Image, Image, Image>
    ApproxPolicy8;
  typedef message_filters::sync_policies::ApproximateTime<
    Image, Image, Image, Image, Image, Image, Image, Image, Image>
    ApproxPolicy9;
  typedef message_filters::Synchronizer<ApproxPolicy2> Sync2;
  typedef message_filters::Synchronizer<ApproxPolicy3> Sync3;
  typedef message_filters::Synchronizer<ApproxPolicy4> Sync4;
  typedef message_filters::Synchronizer<ApproxPolicy5> Sync5;
  typedef message_filters::Synchronizer<ApproxPolicy6> Sync6;
  typedef message_filters::Synchronizer<ApproxPolicy7> Sync7;
  typedef message_filters::Synchronizer<ApproxPolicy8> Sync8;
  typedef message_filters::Synchronizer<ApproxPolicy9> Sync9;
  // ------ variables --------
  ros::NodeHandle nh_;
  std::vector<std::shared_ptr<message_filters::Subscriber<Image>>> sub_;
  std::vector<ros::Publisher> pub_;
  std::shared_ptr<Sync2> sync2_;
  std::shared_ptr<Sync3> sync3_;
  std::shared_ptr<Sync4> sync4_;
  std::shared_ptr<Sync5> sync5_;
  std::shared_ptr<Sync6> sync6_;
  std::shared_ptr<Sync7> sync7_;
  std::shared_ptr<Sync8> sync8_;
  std::shared_ptr<Sync9> sync9_;
};
}  // namespace tagslam
