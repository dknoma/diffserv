/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "diffserv.h"
#include "queuemode.h"
#include "ns3/queue.h"
#include "ns3/log.h"
#include <cstdlib>

namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("DiffServ");
// NS_OBJECT_ENSURE_REGISTERED (DiffServ);

/* The QueueMode specifies whether service is in byte mode or packet mode */
/* Queuemode is an enum of queue in other versions. Should be able to work as a 
class. Maybe even a boolean but more flexible as a class right now. */

std::vector<TrafficClass*> q_class; 

/* For network queues, DoEnqueue() and DoDequeue() functions can be
overwritten to meet implementation requirements for various QoS
algorithms.  */
template <typename Item>
TypeId DiffServ<Item>::GetTypeId (void) {
	static TypeId tid = TypeId ("ns3::DiffServ");
	return tid;
};

/* Take packet as input and add to queue. We will need
to figure out which queue to add to in here, using classify.
 */
template <typename Item>
bool DiffServ<Item>::DoEnqueue(Ptr<ns3::Packet> p) {
	return this -> Enqueue(p);
};


/* Remove next packet from queue */
template <typename Item>
Ptr<ns3::Packet> DiffServ<Item>::DoDequeue(void) {
	Ptr<Packet> p = this -> DoDequeue (this -> Head ());
  	NS_LOG_LOGIC ("Popped " << p);
	return p;
};

/* Get most recent Packet but do not remove */
template <typename Item>
Ptr<ns3::Packet> DiffServ<Item>::DoPeek(void) {
	return this -> DoPeek (this -> Head ());
};

template <typename Item>
void DiffServ<Item>::SetMode(uint32_t mode) {
	DiffServ<Item>::m_mode = mode;
};

template <typename Item>
	uint32_t DiffServ<Item>::GetMode(void) {
	return DiffServ<Item>::m_mode;
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

}

