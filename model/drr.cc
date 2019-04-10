/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "drr.h"
#include "diffserv.cc"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("Drr");
NS_OBJECT_ENSURE_REGISTERED (Drr);

/* The QueueMode specifies whether service is in byte mode or packet mode */
QueueMode m_mode;
vector<TrafficClass*> q_class; 

/* For network queues, DoEnqueue() and DoDequeue() functions can be
overwritten to meet implementation requirements for various QoS
algorithms.  */
}

