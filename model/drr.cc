/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "drr.h"
#include "ns3/log.h"

namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("Drr");

/* Constructor and Deconstructor */
Drr::Drr()
{

    std::vector<TrafficClass<Packet>*> q_class;
    std::cout << "Constructor\n";

	/* Add the three traffic classes this time */
	TrafficClass<Packet>* trafficClass1 = new TrafficClass<Packet>(); // 4000
	TrafficClass<Packet>* trafficClass2 = new TrafficClass<Packet>(); // 6000
	TrafficClass<Packet>* trafficClass3 = new TrafficClass<Packet>(); // 8000
	/* Set the first one (0) to be default */
	trafficClass1 -> SetIsDefault(true);
    trafficClass1 -> SetWeight(1.0);
    trafficClass2 -> SetWeight(2.0);
    trafficClass3 -> SetWeight(3.0);

      /* Set the filters. Can also do this in the example but this is easier */
    DestinationPortNumberFilter* srcPortFilter1 = new DestinationPortNumberFilter();
    DestinationPortNumberFilter* srcPortFilter2 = new DestinationPortNumberFilter();
    DestinationPortNumberFilter* srcPortFilter3 = new DestinationPortNumberFilter();
    srcPortFilter1->SetPort(4000);
    srcPortFilter2->SetPort(6000);
    srcPortFilter2->SetPort(8000);


    std::vector<FilterElement*> elements1;
    std::vector<FilterElement*> elements2;
    std::vector<FilterElement*> elements3;


    elements1.push_back(srcPortFilter1);
    elements2.push_back(srcPortFilter2);
    elements3.push_back(srcPortFilter3);

    Filter* filter1 = new Filter(elements1);
    Filter* filter2 = new Filter(elements2);
    Filter* filter3 = new Filter(elements3);

    /* Adding these filters to test against */
    trafficClass1->AddFilter(filter1);
    trafficClass2->AddFilter(filter2);
    trafficClass3->AddFilter(filter2);
    // q_class[0]->AddFilter(filter1);
    // q_class[1]->AddFilter(filter2);
    /* Add them to q_class */

    this->q_class.push_back(trafficClass1);
    this->q_class.push_back(trafficClass2);
    this->q_class.push_back(trafficClass3);
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

/* TODO: This function also */
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

