/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "diffserv.h"
#include "ns3/spq.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("Spq");
NS_OBJECT_ENSURE_REGISTERED (Spq);

/* The QueueMode specifies whether service is in byte mode or packet mode */
QueueMode m_mode;
vector<TrafficClass*> q_class; 

}

