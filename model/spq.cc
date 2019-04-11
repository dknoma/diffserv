/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "diffserv.h"
#include "ns3/spq.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("Spq");
NS_OBJECT_ENSURE_REGISTERED (Spq);

/* The QueueMode specifies whether service is in byte mode or packet mode */
QueueMode m_mode;
vector<TrafficClass*> q_class; 

/* For network queues, DoEnqueue() and DoDequeue() functions can be
overwritten to meet implementation requirements for various QoS
algorithms.  */

TypeId Spq::GetTypeId (void) {
	static TypeId tid = TypeId ("ns3::Spq");
	return tid;
}

/* Take packet as input and add to queueu */
bool Spq::DoEnqueue(Ptr<ns3::Packet> p) {
	return false;
};


/* Remove next packet from queue */
Ptr<ns3::Packet> Spq::DoDequeue(void) {
	Ptr<Packet> p = Create<Packet>();
	return p;
};

//Ptr<ns3::Packet> DiffServ::DoRemove(void) {

//};

/* Get most recent Packet but do not remove */
Ptr<ns3::Packet> Spq::DoPeek(void) {

};

}

