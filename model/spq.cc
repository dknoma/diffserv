/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "spq.h"
#include "ns3/log.h"

namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("Spq");
NS_OBJECT_TEMPLATE_CLASS_DEFINE (Spq, Packet);

/* Constructor and Deconstructor */
template <typename Item>
Spq<Item>::Spq()
{
std::cout << "Constructor\n";
}
template <typename Item>
Spq<Item>::~Spq ()
{

}
/* The QueueMode specifies whether service is in byte mode or packet mode */

/* For network queues, DoEnqueue() and DoDequeue() functions can be
overwritten to meet implementation requirements for various QoS
algorithms.  */
template <typename Item>
TypeId Spq<Item>::GetTypeId (void) {
	static TypeId tid = TypeId ("ns3::Spq<Packet>")
	    .SetParent<DiffServ<Item> >()
	    .SetGroupName ("DiffServ")
     	.template AddConstructor<Spq<Item>> ();
	return tid;
};

/* Enqueue in the High Priority Queue if it's a match I imagine */
template <typename Item>
bool Spq<Item>::DoEnqueue(Ptr<Item> T) {
	std::cout << "Enqueue\n";
	/* Figure out which traffic class to add this to */
	/* So loop through our filters, and figure out which queue to put this in */
	bool matching = false;
	for(typename std::vector<Item>::size_type i = 0; i != this -> Spq::q_class.size(); i++) {
    	matching = Spq::q_class[i] -> match(T);
    	if (matching == true) {
    		return this -> Spq::q_class[i] -> Enqueue(T);
    	}
	}

	/* So there are no matches, so loop through again and put into default queue */
	bool isDefault;
	for(typename std::vector<Item>::size_type i = 0; i != this -> Spq::q_class.size(); i++) {
    	isDefault = Spq::q_class[i] -> GetIsDefault();
    	if (isDefault == true) {
    		return this -> Spq::q_class[i] -> Enqueue(T);
    	}
	}

	/* Place here to avoid error for now but need to refactor above code */
	return this -> Enqueue(T);
};


/* Remove next packet from queue. Not a good way to do it atm. */
template <typename Item>
Ptr<Item> Spq<Item>::DoDequeue(void) {
	std::cout << "Dequeue\n";
	/* Iterate through the vectors. If high priority vector is not empty 
	dequeue from that one. Else dequeue from the other one */
	uint32_t priority;
	for(typename std::vector<Item>::size_type i = 0; i != this -> Spq::q_class.size(); i++) {
    	priority = Spq::q_class[i] -> GetPriorityLevel();
    	/* 1 or 0, not sure */
    	if (priority == 1) {
    		/* If the high priority queue is empty */
    		if (Spq::q_class[i] -> GetPackets() == 0) {
    			/* Get first packet available from other non-empty queues */
    			for(typename std::vector<Item>::size_type z = 0; z != this -> Spq::q_class.size(); z++) {
    				if (Spq::q_class[z] -> GetPackets() != 0) {
    					return this -> Spq::q_class[z] -> Dequeue ();
    				}
    			}
    		} else {
    			/* Not empty so dequeue the high priority packet */
    			return this -> Spq::q_class[i] -> Dequeue ();
    		}
    	} else {
    		/* Keep going through the loop until we get to the high priority queue */
    		continue;
    	}
	}
	/* Never came across the high priority queue */
	return NULL;
	
};

/* Get most recent Packet but do not remove */
template <typename Item>
Ptr<const Item> Spq<Item>::DoPeek(void) {
	return this -> Peek ();
};

/* The schedule function carries out designed Quality-of-Service (QoS) algorithm to schedule which
traffic queue to be served at the time. */
template <typename Item>
Ptr<Item> Spq<Item>::Schedule() {
 	Ptr<Packet> p = Create<Packet>();
	/* If we received a high priority packet, deal with that first */

	/* Else if there are no high priority packets, we can deal with the low 
	priority packets */

	/* Retun the packet that we'd like to dequeue */
	return p;
};

/* The classify function utilizes filter aspect to sort the traffic packets into appropriate traffic
queues. */
template <typename Item>
uint32_t Spq<Item>::Classify(Ptr<Item> p) {
	/* Decide which queue to inert this packet into */
	return 0;
};

// template class Spq<Packet>;

}

