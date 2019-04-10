/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ns3/queue.h"
#include "diffserv.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("DiffServ");
NS_OBJECT_ENSURE_REGISTERED (DiffServ);

/* The QueueMode specifies whether service is in byte mode or packet mode */
// QueueMode m_mode;
//vector<TrafficClass*> q_class; 

/* For network queues, DoEnqueue() and DoDequeue() functions can be
overwritten to meet implementation requirements for various QoS
algorithms.  */
bool DiffServ::DoEnqueue(Ptr<ns3::Packet> p) {
	return false;
};

Ptr<ns3::Packet> DiffServ::DoDequeue(void) {
	Ptr<Packet> p = Create<Packet>();
	return p;
};

//Ptr<ns3::Packet> DiffServ::DoRemove(void) {

//};
//Ptr<ns3::Packet> DiffServ::DoPeek(void) {

//};
//void DiffServ::SetMode(QueueMode mode) {

//};
//QueueMode DiffServ::GetMode(void) {

//};

//Ptr<ns3::Packet> DiffServ::GetMode(void) {

//};
/* Utilizes filter aspect to sort the traffic packets into
appropriate traffic queues. */
//uint32_t DiffServ::Classify(Ptr<ns3::Packet> p) {
	
//};

/*  Carries out designed Quality-of-Service (QoS) algorithm to schedule
 which traffic queue to be served at the time.  */
//uint32_t DiffServ::Schedule(Ptr<ns3::Packet> p) {
	
//};

/* Additional Functions */
/* Two separate functions need to be implemented per QoS algorithm
design of the developer’s choice. */

}

