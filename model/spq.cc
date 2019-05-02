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
/* Need to create the high priority and low priority traffic classes first */
	TrafficClass<Packet>* trafficClassHigh = new TrafficClass<Packet>();
	TrafficClass<Packet>* trafficClassLow = new TrafficClass<Packet>();
	/* Set the first one (0) to be default */
	trafficClassLow -> SetIsDefault(false);

	/* Add them to q_class */
    this->q_class.push_back(trafficClassLow);
    this->q_class.push_back(trafficClassHigh);

    /* Create the filters. They'll just be hardcoded for now */
    Filter* filter1 = new Filter();
    Filter* filter2 = new Filter();


    /* Adding these filters to test against */
    q_class[0]->AddFilter(filter1);
    q_class[1]->AddFilter(filter2);


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
	/* Figure out which traffic class to add this to by calling classify */
    int priority = Classify(T);
    return q_class[priority]->Enqueue((Ptr<Packet>) T);
};


/* Remove next packet from queue. Not a good way to do it atm. */
template <typename Item>
Ptr<Item> Spq<Item>::DoDequeue(void) {
	std::cout << "Dequeue\n";
	/* Iterate through the vectors. If high priority vector is not empty 
	dequeue from that one. Else dequeue from the other one */
	uint32_t priority;
	for(typename std::vector<Item>::size_type i = 0; i != this -> q_class.size(); i++) {
    	priority = Spq::q_class[i] -> GetPriorityLevel();
    	/* 1 or 0, not sure */
    	if (priority == 1) {
    		/* If the high priority queue is empty */
    		if (Spq::q_class[i] -> GetPackets() == 0) {
    			/* Get first packet available from other non-empty queues */
    			for(typename std::vector<Item>::size_type z = 0; z != this -> q_class.size(); z++) {
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
	/* If we received a high priority packet, deal with that first */
    if (this -> q_class[1]->GetSizeBytes() != 0) {
        return (Ptr<Item>)(this -> q_class[1]->Dequeue());
    } else {
        return (Ptr<Item>)(this -> q_class[0]->Dequeue());
    }

	/* Retun the packet that we'd like to dequeue */
};

/* The classify function utilizes filter aspect to sort the traffic packets into appropriate traffic
queues. */
template <typename Item>
uint32_t Spq<Item>::Classify(Ptr<Item> p) {
	/* Decide which queue to inert this packet into */
	Ptr<Packet> packet = (Ptr<Packet>)p;
    for (int i = 0; i < (int) this -> q_class.size(); i++) {
        if (this->q_class[i]->match(packet)) {
            return i;
        }
    }
    /* Otherwise return whatever is the default queue */
    return 0;
};

// template class Spq<Packet>;

}

