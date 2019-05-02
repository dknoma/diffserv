/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "drr.h"
#include "ns3/log.h"

namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("Drr");

/* Constructor and Deconstructor */
Drr::Drr()
{
	/* Add the three traffic classes this time */
	TrafficClass<Packet>* trafficClass1 = new TrafficClass<Packet>();
	TrafficClass<Packet>* trafficClass2 = new TrafficClass<Packet>();
	TrafficClass<Packet>* trafficClass3 = new TrafficClass<Packet>();
	/* Set the first one (0) to be default */
	trafficClass1 -> SetIsDefault(true);

	/* Add them to q_class */
    this->q_class.push_back(trafficClass1);
    this->q_class.push_back(trafficClass2);
    this->q_class.push_back(trafficClass3);

    /* Create the filters. They'll just be hardcoded for now */
    Filter* filter1 = new Filter();
    Filter* filter2 = new Filter();
    Filter* filter3 = new Filter();


    /* Adding these filters to test against */
    q_class[0]->AddFilter(filter1);
    q_class[1]->AddFilter(filter2);
    q_class[1]->AddFilter(filter3);
}

Drr::~Drr ()
{

}

/* For network queues, DoEnqueue() and DoDequeue() functions can be
overwritten to meet implementation requirements for various QoS
algorithms.  */

TypeId Drr::GetTypeId (void) {
	static TypeId tid = TypeId ("ns3::Drr");
	return tid;
};

/* Enqueue based on weight. Same as SPQ */
bool Drr::DoEnqueue(Ptr<Packet> T) {
	/* This is the first part of SPQ. This is only a placeholder */
	/* TODO: Figure out how DRR uses weight */
	std::cout << "Enqueue\n";
	/* Figure out which traffic class to add this to by calling classify */
    int queueNumber = Classify(T);
    return q_class[queueNumber]->Enqueue((Ptr<Packet>) T);
};


/* TODO: This function */
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

/* This should be the same as SPQ */
uint32_t Drr::Classify(Ptr<ns3::Packet> p) {
		/* If we received a high priority packet, deal with that first */
	Ptr<Packet> packet = (Ptr<Packet>)p;
    for (int i = 0; i < (int) this -> q_class.size(); i++) {
        if (this->q_class[i]->match(packet)) {
            return i;
        }
    }
    /* Otherwise return whatever is the default queue, so 0 */
    return 0;
};


}

