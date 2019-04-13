/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "drr.h"
#include "ns3/log.h"

namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("Drr");
NS_OBJECT_ENSURE_REGISTERED (Drr);


/* For network queues, DoEnqueue() and DoDequeue() functions can be
overwritten to meet implementation requirements for various QoS
algorithms.  */

TypeId Drr<Item>::GetTypeId (void) {
	static TypeId tid = TypeId ("ns3::Drr");
	return tid;
}

Ptr<ns3::Packet> Drr<Item>::Schedule() {
	Ptr<Packet> p = Create<Packet>();
	return p;
}

uint32_t Drr<Item>::Classify(Ptr<ns3::Packet> p) {
	return 0;
};


}

