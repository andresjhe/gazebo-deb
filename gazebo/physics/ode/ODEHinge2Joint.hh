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
/* Desc: A hinge joint with 2 degrees of freedom
 * Author: Nate Koenig, Andrew Howard
 * Date: 21 May 2003
 */

#ifndef _ODEHINGE2JOINT_HH_
#define _ODEHINGE2JOINT_HH_

#include "gazebo/math/Angle.hh"
#include "gazebo/math/Vector3.hh"

#include "gazebo/physics/Hinge2Joint.hh"
#include "gazebo/physics/ode/ODEJoint.hh"

namespace gazebo
{
  namespace physics
  {
    /// \brief A two axis hinge joint
    class ODEHinge2Joint : public Hinge2Joint<ODEJoint>
    {
      /// \brief Constructor
      /// \param[in] _worldID ODE id of the world.
      /// \param[in] _parent Parent of the Joint
      public: ODEHinge2Joint(dWorldID worldId, BasePtr _parent);

      /// \brief Destructor.
      public: virtual ~ODEHinge2Joint();

      // Documentation inherited.
      public: virtual void Load(sdf::ElementPtr _sdf);

      // Documentation inherited.
      public: virtual void SetAnchor(int _index, const math::Vector3 &_anchor);

      // Documentation inherited.
      public: virtual void SetAxis(int _index, const math::Vector3 &_axis);

      // Documentation inherited.
      public: virtual math::Vector3 GetAnchor(int _index) const;

      // Documentation inherited.
      public: virtual math::Vector3 GetGlobalAxis(int _index) const;

      // Documentation inherited.
      public: virtual math::Angle GetAngleImpl(int _index) const;

      // Documentation inherited.
      public: virtual double GetVelocity(int _index) const;

      // Documentation inherited.
      public: virtual void SetVelocity(int index, double angle);

      // Documentation inherited.
      public: virtual void SetMaxForce(int index, double t);

      // Documentation inherited.
      public: virtual double GetMaxForce(int index);

      // Documentation inherited.
      public: virtual void SetForce(int _index, double _effort);

      // Documentation inherited.
      public: virtual double GetParam(int parameter) const;

      public: virtual void SetParam(int parameter, double value);
    };
  }
}
#endif
