/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "drr.h"
#include "ns3/log.h"

namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("Drr");

/* Constructor and Deconstructor */
Drr::Drr()
{
  NS_LOG_FUNCTION (this);
}

Drr::~Drr ()
{
  NS_LOG_FUNCTION (this);
}

/* For network queues, DoEnqueue() and DoDequeue() functions can be
overwritten to meet implementation requirements for various QoS
algorithms.  */



TypeId Drr::GetTypeId (void) {
	static TypeId tid = TypeId ("ns3::Drr");
	return tid;
};

/* Enqueue based on weight. Need to do the calculation */

bool Drr::DoEnqueue(Ptr<Packet> T) {
	/* This is the first part of SPQ. This is only a placeholder */
	/* TODO: Figure out how DRR uses weight */
	bool matching = false;
	for(std::vector<Packet>::size_type i = 0; i != this -> Drr::q_class.size(); i++) {
    	matching = Drr::q_class[i] -> match(T);
    	if (matching == true) {
    		return this -> Drr::q_class[i] -> Enqueue(T);
    	}
	}
	return this -> Enqueue(T);
};


/* Remove next packet from queue */
Ptr<Packet> Drr::DoDequeue(void) {
	return this -> Dequeue ();
};

/* Get most recent Packet but do not remove */
Ptr<const Packet> Drr::DoPeek(void) {
	return this -> Peek ();
};

Ptr<ns3::Packet> Drr::Schedule() {
	Ptr<Packet> p = Create<Packet>();
	return p;
};

uint32_t Drr::Classify(Ptr<ns3::Packet> p) {
	return 0;
};


}

