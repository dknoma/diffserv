/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "spq.h"
#include "ns3/log.h"

namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("Spq");

/* The QueueMode specifies whether service is in byte mode or packet mode */

/* For network queues, DoEnqueue() and DoDequeue() functions can be
overwritten to meet implementation requirements for various QoS
algorithms.  */

template <typename Item>
TypeId Spq<Item>::GetTypeId (void) {
	static TypeId tid = TypeId ("ns3::Spq");
	return tid;
}

/* The schedule function carries out designed Quality-of-Service (QoS) algorithm to schedule which
traffic queue to be served at the time. */
template <typename Item>
Ptr<ns3::Packet> Spq<Item>::Schedule() {
	Ptr<Packet> p = Create<Packet>();
	return p;
}

/* The classify function utilizes filter aspect to sort the traffic packets into appropriate traffic
queues. */
template <typename Item>
uint32_t Spq<Item>::Classify(Ptr<ns3::Packet> p) {
	return 0;
}

}

