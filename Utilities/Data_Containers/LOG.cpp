#include "LOG.hpp"
LOG::LOG()
{
    m_entry_id                    = 0;
    m_bearing                     = 0;
    m_latitude                    = 0;
    m_longitude                   = 0;
    m_speed                       = 0;
    m_timestamp                   = "";
    m_distance_from_waypoint      = 0;
    m_distance_from_destination   = 0;
}