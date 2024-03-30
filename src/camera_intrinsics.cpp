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

#include <ctime>
#include <sstream>
#include <string>
#include <tagslam/camera_intrinsics.hpp>
#include <tagslam/logging.hpp>
#include <tagslam/yaml.hpp>
#include <tagslam/yaml_utils.hpp>
#include <vector>

using std::string;

namespace tagslam
{
static rclcpp::Logger get_logger()
{
  return (rclcpp::get_logger("camera_intrinsics"));
}

static std::map<string, DistortionModel> distMap = {
  {"rad_tan", RADTAN},   {"radtan", RADTAN},
  {"plumb_bob", RADTAN}, {"equidistant", EQUIDISTANT},
  {"equi", EQUIDISTANT}, {"fisheye", EQUIDISTANT}};

static std::string model_to_string(DistortionModel m)
{
  for (const auto & dm : distMap) {
    if (dm.second == m) {
      return (dm.first);
    }
  }
  return ("INVALID");
}

CameraIntrinsics CameraIntrinsics::parse_no_error(const YAML::Node & config)
{
  CameraIntrinsics ci;
  ci.cameraModel_ = yaml::parse<string>(config, "camera_model");
  const string distModel = yaml::parse<string>(config, "distortion_model");
  if (distMap.count(distModel) == 0) {
    BOMB_OUT("unknown distortion model: " << distModel);
  }
  ci.distortionModel_ = distMap[distModel];
  ci.distortionCoeffs_ =
    yaml::parse_container<std::vector<double>>(config, "distortion_coeffs");
  ci.K_ = yaml::parse_container<std::vector<double>>(config, "intrinsics");
  ci.resolution_ =
    yaml::parse_container<std::vector<int>>(config, "resolution");
  // precompute K and D
  ci.cvK_ =
    (cv::Mat_<double>(3, 3) << ci.K_[0], 0.0, ci.K_[2], 0.0, ci.K_[1], ci.K_[3],
     0.0, 0.0, 1.0);
  const auto & D = ci.distortionCoeffs_;
  ci.cvD_ = cv::Mat_<double>(1, D.size());
  for (unsigned int i = 0; i < D.size(); i++) {
    ci.cvD_.at<double>(i) = D[i];
  }
  return (ci);
}

CameraIntrinsics CameraIntrinsics::parse(const YAML::Node & config)
{
  try {
    return (parse_no_error(config));
  } catch (const std::runtime_error & e) {
    BOMB_OUT("error parsing camera intrinsics: " << e.what());
  }
}

void CameraIntrinsics::writeYaml(std::ostream & f, const string & pf) const
{
  f << pf << "camera_model: " << cameraModel_ << std::endl;
  f << pf << "distortion_coeffs: ";
  yaml_utils::write_container<std::vector<double>>(f, "", distortionCoeffs_);
  f << std::endl;
  f << pf << "distortion_model: " << model_to_string(distortionModel_)
    << std::endl;
  f << pf << "intrinsics: ";
  yaml_utils::write_container<std::vector<double>>(f, "", K_);
  f << std::endl;
  f << pf << "resolution: ";
  yaml_utils::write_container<std::vector<int>>(f, "", resolution_, 4, 0);
  f << std::endl;
}

std::ostream & operator<<(std::ostream & os, const CameraIntrinsics & ci)
{
  ci.writeYaml(os, "");
  return (os);
}

}  // namespace tagslam
