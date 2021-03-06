/*
 * Copyright 2012 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
/*
 * Desc: a test for getting force and torques at joints
 * Author: John Hsu
 */
#ifndef GAZEBO_JOINT_TRAJECTORY_PLUGIN_HH
#define GAZEBO_JOINT_TRAJECTORY_PLUGIN_HH

#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

#include "gazebo/physics/physics.hh"
#include "gazebo/transport/TransportTypes.hh"
#include "gazebo/common/Time.hh"
#include "gazebo/common/Plugin.hh"
#include "gazebo/common/Events.hh"

namespace gazebo
{
  class ForceTorquePlugin : public ModelPlugin
  {
    /// \brief Constructor
    public: ForceTorquePlugin();

    /// \brief Destructor
    public: virtual ~ForceTorquePlugin();

    /// \brief Load the controller
    public: void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf);

    /// \brief Update the controller
    /// \param[in] _info Update information provided by the server.
    private: void UpdateStates(const common::UpdateInfo &_info);

    private: physics::WorldPtr world;
    private: physics::ModelPtr model;
    private: physics::Joint_V joints;

    private: boost::mutex update_mutex;

    // Pointer to the update event connection
    private: event::ConnectionPtr updateConnection;
  };
}
#endif
