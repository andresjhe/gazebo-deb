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

#include <gtest/gtest.h>
#include "gazebo/physics/Physics.hh"
#include "gazebo/common/Time.hh"
#include "test/ServerFixture.hh"

using namespace gazebo;
class SensorManager_TEST : public ServerFixture
{
};

/////////////////////////////////////////////////
/// \brief Test SensorManager initialization
TEST_F(SensorManager_TEST, InitEmpty)
{
  Load("worlds/empty.world");
  sensors::SensorManager *mgr = sensors::SensorManager::Instance();

  EXPECT_TRUE(mgr->SensorsInitialized());
  sensors::Sensor_V sensors = mgr->GetSensors();
  size_t size = 0;
  EXPECT_EQ(sensors.size(), size);
}

/////////////////////////////////////////////////
/// \brief Test that sensors are actually created and updated.
TEST_F(SensorManager_TEST, Data)
{
  sensors::SensorPtr sensor;

  // Load in a world with cameras and lasers
  Load("worlds/test_camera_laser.world");
  sensors::SensorManager *mgr = sensors::SensorManager::Instance();
  EXPECT_TRUE(mgr->SensorsInitialized());

  // Make sure we have the right number of sensors
  size_t sensorCount = 4;
  sensors::Sensor_V sensors = mgr->GetSensors();
  EXPECT_EQ(sensors.size(), sensorCount);

  // Get the current simulation time
  common::Time time = physics::get_world()->GetSimTime();

  // Wait for 1 second
  for (unsigned int i = 0; i < 10; ++i)
  {
    common::Time::MSleep(100);
  }

  // Get each sensor, and make sure that it has been updated
  {
    sensor = mgr->GetSensor("default::camera_1::link::camera");
    EXPECT_TRUE(sensor != NULL);
    EXPECT_TRUE(sensor->GetLastMeasurementTime() > time);

    sensor = mgr->GetSensor("default::camera_2::link::camera");
    EXPECT_TRUE(sensor != NULL);
    EXPECT_TRUE(sensor->GetLastMeasurementTime() > time);

    sensor = mgr->GetSensor("default::laser_1::link::laser");
    EXPECT_TRUE(sensor != NULL);
    EXPECT_TRUE(sensor->GetLastMeasurementTime() > time);

    sensor = mgr->GetSensor("default::laser_2::link::laser");
    EXPECT_TRUE(sensor != NULL);
    EXPECT_TRUE(sensor->GetLastMeasurementTime() > time);
  }
}

/////////////////////////////////////////////////
/// \brief Test SensorManager init and removal of sensors
TEST_F(SensorManager_TEST, InitRemove)
{
  // Load in the pr2
  Load("worlds/pr2.world");
  sensors::SensorManager *mgr = sensors::SensorManager::Instance();

  size_t sensorCount = 18;

  // Make sure we have the correct number of sensors.
  EXPECT_TRUE(mgr->SensorsInitialized());
  sensors::Sensor_V sensors = mgr->GetSensors();
  EXPECT_EQ(sensors.size(), sensorCount);

  // Try removing a few senors.
  for (sensors::Sensor_V::iterator iter = sensors.begin();
       iter != sensors.end() && sensorCount > 10; ++iter)
  {
    mgr->RemoveSensor((*iter)->GetName());
    EXPECT_EQ(mgr->GetSensors().size(), --sensorCount);
  }

  // Make sure the proper number of sensors have been removed
  EXPECT_EQ(mgr->GetSensors().size(), sensorCount);

  // Remove the rest of the sensors
  mgr->RemoveSensors();

  // Make sure all the sensors have been removed
  EXPECT_EQ(mgr->GetSensors().size(), size_t(0));
}

/////////////////////////////////////////////////
int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
