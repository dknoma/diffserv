/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "spq.h"
#include "ns3/log.h"

namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("Spq");

/* Constructor and Deconstructor */

Spq::Spq()
{
  NS_LOG_FUNCTION (this);
}

Spq::~Spq ()
{
  NS_LOG_FUNCTION (this);
}
/* The QueueMode specifies whether service is in byte mode or packet mode */

/* For network queues, DoEnqueue() and DoDequeue() functions can be
overwritten to meet implementation requirements for various QoS
algorithms.  */

TypeId Spq::GetTypeId (void) {
	static TypeId tid = TypeId ("ns3::Spq");
	return tid;
};

bool Spq::DoEnqueue(Ptr<Packet> T) {
	/* Figure out which traffic class to add this to */
	return this -> Enqueue(T);
};


/* Remove next packet from queue */
Ptr<Packet> Spq::DoDequeue(void) {
	return this -> Dequeue ();
};

/* Get most recent Packet but do not remove */
Ptr<const Packet> Spq::DoPeek(void) {
	return this -> Peek ();
};

/* The schedule function carries out designed Quality-of-Service (QoS) algorithm to schedule which
traffic queue to be served at the time. */
Ptr<Packet> Spq::Schedule() {
 	Ptr<Packet> p = Create<Packet>();
	/* If we received a high priority packet, deal with that first */

	/* Else if there are no high priority packets, we can deal with the low 
	priority packets */

	/* Retun the packet that we'd like to dequeue */
	return p;
};

/* The classify function utilizes filter aspect to sort the traffic packets into appropriate traffic
queues. */
uint32_t Spq::Classify(Ptr<ns3::Packet> p) {
	/* Decide which queue to inert this packet into */
	return 0;
};

}

