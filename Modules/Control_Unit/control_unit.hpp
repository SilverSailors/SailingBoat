#ifndef __CONTROL_UNIT_HPP__
#define __CONTROL_UNIT_HPP__
#include <queue>
#include <string>
#include <vector>
#include "../../Utilities/Data_Containers/GPS_POSITION.hpp"
#include "ANGLE.hpp"
class Control_Unit
{
    private:

        bool                      m_active;                     //Is the Control Unit Activated
        bool                      m_waypoint_reached;           //Have we reached our waypoint
        bool                      m_waypoint_set;               //Have we set a waypoint?
        bool                      m_destination_set;            //Have we set a destination
        bool                      m_destination_reached;        //Have we reached our destination

        std::queue<GPS_POSITION>  m_destination;                //Queue of all our destinations
        GPS_POSITION              m_waypoint;                   //Our current waypoint

        double                    m_distance_threshold;         //The distance we are allowed to be away from the waypoint to consider it reached (Meters)
        double                    m_time_threshold;             //How long should we wait until we establish a new waypoint If the old one hasnt been reached
        double                    m_distance_factor;            //How far away should waypoints be from our initial position
        double                    m_time_value;
        double                    m_calculated_threshold;
        double                    m_waypoint_distance_creation_threshold;

        ANGLE                     m_angle_direction;

    public:
        Control_Unit();

        bool          is_active();
        bool          init(std::string destination, std::string settings);

        GPS_POSITION  get_destination();
        void          set_destination(GPS_POSITION destination);

        GPS_POSITION  get_waypoint();
        void          set_waypoint(GPS_POSITION waypoint);

        void          set_distance_threshold(double value);
        double        get_distance_threshold();

        bool          validate_inits(std::vector<bool> statuses);
        bool          is_waypoint_set();
        void          set_waypoint_status(bool status);

        void          alternate_angle();
        ANGLE         get_angle_direction();

        double        get_distance_factor();

        bool          time_discrepency_reached(int time_value);

        void          set_time_value(int value);
        double        get_calculated_threshold();
        void          update_journey();

        double        get_waypoint_creation_threshold();

};
#endif//__CONTROL_UNIT_HPP__
