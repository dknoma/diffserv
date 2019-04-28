/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "diffserv.h"
#include "ns3/queue.h"
#include "ns3/log.h"
#include <cstdlib>

namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("DiffServ");
NS_OBJECT_TEMPLATE_CLASS_DEFINE (DiffServ, Packet);

 

// constructor
template <typename Item>
DiffServ<Item>::DiffServ()
{

}

template <typename Item>
DiffServ<Item>::~DiffServ ()
{

}

/* For network queues, DoEnqueue() and DoDequeue() functions can be
overwritten to meet implementation requirements for various QoS
algorithms.  */

/* static TypeId tid = TypeId ("ns3::DiffServ<Packet>") needs to have packet or else it can't be used in csma */
template <typename Item>
TypeId DiffServ<Item>::GetTypeId (void) {
   static TypeId tid = TypeId ("ns3::DiffServ<Packet>")
     .SetParent<DropTailQueue<Item> > ()
     .SetGroupName ("DiffServ")
     .template AddConstructor<DiffServ<Item>> ()
   ;
   return tid;
};

/* Take packet as input and add to queue. We will need
to figure out which queue to add to in here, using classify.
 */
template <typename Item>
bool DiffServ<Item>::DoEnqueue(Ptr<Item> T) {
	return this -> Enqueue(T);
};


/* Remove next packet from queue */
template <typename Item>
Ptr<Item> DiffServ<Item>::DoDequeue(void) {
	return this -> Dequeue ();
};

/* Get most recent Packet but do not remove */
template <typename Item>
Ptr<const Item> DiffServ<Item>::DoPeek(void) {
	return this -> Peek ();
};

template <typename Item>
void DiffServ<Item>::SetMode(uint32_t mode) {
	DiffServ<Item>::m_mode = mode;
};

template <typename Item>
uint32_t DiffServ<Item>::GetMode(void) {
	return DiffServ<Item>::m_mode;
};

template <typename Item>
void DiffServ<Item>::AddTrafficClass(TrafficClass<Item>* traffic) {
	this -> q_class.push_back(traffic);
};


/* Utilizes filter aspect to sort the traffic packets into
appropriate traffic queues. */
template <typename Item>
uint32_t DiffServ<Item>::Classify(Ptr<Item> p) {
	return 0;
};

/*  Carries out designed Quality-of-Service (QoS) algorithm to schedule
 which traffic queue to be served at the time.  */
template <typename Item>
Ptr<Item> DiffServ<Item>::Schedule(void) {
	Ptr<Item> T;
	return T;
};

/* Need these to say what types we can use in diffserv (Bytes and Packets) */
//template class DiffServ<Packet>;
//template class DiffServ<uint32_t>;
}

