/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "queuemode.h"
#include "ns3/log.h"
#include <cstdlib>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("QueueMode");
NS_OBJECT_ENSURE_REGISTERED (QueueMode);

/* The QueueMode specifies whether service is in byte mode or packet mode */
TypeId QueueMode::GetTypeId (void) {
	static TypeId tid = TypeId ("ns3::QueueMode");
	return tid;
}

/* Constructor */
QueueMode::QueueMode () {

}

/* Destructor */
QueueMode::~QueueMode () {

}

/* For network queues, DoEnqueue() and DoDequeue() functions can be
overwritten to meet implementation requirements for various QoS
algorithms.  */
int QueueMode::IsPacket(void) {
	return 1;
};

int QueueMode::IsBytes(void) {
	return 0;
};

}

