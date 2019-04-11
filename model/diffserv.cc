/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "diffserv.h"
#include "ns3/queue.h"
#include "ns3/log.h"
#include <cstdlib>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("DiffServ");
NS_OBJECT_ENSURE_REGISTERED (DiffServ);

/* The QueueMode specifies whether service is in byte mode or packet mode */
/* Queuemode is an enum of queue in other versions. Should be able to work as a 
class. Maybe even a boolean but more flexible as a class right now. */

QueueMode m_mode;
//vector<TrafficClass*> q_class; 

/* For network queues, DoEnqueue() and DoDequeue() functions can be
overwritten to meet implementation requirements for various QoS
algorithms.  */

TypeId DiffServ::GetTypeId (void) {
	static TypeId tid = TypeId ("ns3::DiffServ");
	return tid;
}

/* Take packet as input and add to queueu */
bool DiffServ::DoEnqueue(Ptr<ns3::Packet> p) {
	return false;
};


/* Remove next packet from queue */
Ptr<ns3::Packet> DiffServ::DoDequeue(void) {
	Ptr<Packet> p = Create<Packet>();
	return p;
};

//Ptr<ns3::Packet> DiffServ::DoRemove(void) {

//};

/* Get most recent Packet but do not remove */
Ptr<ns3::Packet> DiffServ::DoPeek(void) {
	Ptr<Packet> p = Create<Packet>();
	return  p;
};

void DiffServ::SetMode(QueueMode mode) {
	m_mode = mode;
};

QueueMode DiffServ::GetMode(void) {
	return m_mode;
};


/* Utilizes filter aspect to sort the traffic packets into
appropriate traffic queues. */
//uint32_t DiffServ::Classify(Ptr<ns3::Packet> p) {
//	return 0;
//};

/*  Carries out designed Quality-of-Service (QoS) algorithm to schedule
 which traffic queue to be served at the time.  */
//uint32_t DiffServ::Schedule(Ptr<ns3::Packet> p) {
	
//};

/* Additional Functions */
/* Two separate functions need to be implemented per QoS algorithm
design of the developer’s choice. */

}

