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

#ifndef TAGSLAM__GRAPH_VERTEX_HPP_
#define TAGSLAM__GRAPH_VERTEX_HPP_

#include <iostream>
#include <memory>
#include <string>

namespace tagslam
{
class Vertex;
typedef std::shared_ptr<Vertex> GraphVertex;
std::ostream & operator<<(std::ostream & os, const GraphVertex & v);

}  // namespace tagslam
#endif  // TAGSLAM__GRAPH_VERTEX_HPP_