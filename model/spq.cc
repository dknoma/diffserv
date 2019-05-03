/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "spq.h"
#include "ns3/SourcePortNumberFilter.h"
#include "ns3/log.h"
#include "ns3/ppp-header.h"
#include "ns3/ipv4-header.h"

namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("Spq");
NS_OBJECT_TEMPLATE_CLASS_DEFINE (Spq, Packet);

/* Constructor and Deconstructor */
template <typename Item>
Spq<Item>::Spq()
{
std::cout << "Constructor\n";
/* Need to create the high priority and low priority traffic classes first */
 //  TrafficClass<Packet>* trafficClassLow = new TrafficClass<Packet>();
	// TrafficClass<Packet>* trafficClassHigh = new TrafficClass<Packet>();
  TrafficClass<Packet> trafficClassLow;
  TrafficClass<Packet> trafficClassHigh;
	/* Set the first one (0) to be default */
	// trafficClassLow -> SetIsDefault(true);
 //  trafficClassHigh -> SetPriorityLevel(1);
  trafficClassLow.SetIsDefault(true);
  trafficClassHigh.SetPriorityLevel(1);

  /* Create the filters. They'll just be hardcoded for now */
  // Filter* filter1 = new Filter();
  // Filter* filter2 = new Filter();
  // Filter filter1;
  // Filter filter2;

  /* Set the filters. Can also do this in the example but this is easier */
  SourcePortNumberFilter srcPortFilter1;
  SourcePortNumberFilter srcPortFilter2;
	srcPortFilter1.SetPort(4000);
	srcPortFilter2.SetPort(6000);

  std::vector<FilterElement*> elements1;
  std::vector<FilterElement*> elements2;

  elements1.push_back(&srcPortFilter1);
  elements2.push_back(&srcPortFilter2);

  std::cout << "elements1 size: " << elements1.size() << "\n";

  Filter filter1(&elements1);
  Filter filter2(&elements2);
	// filter1.SetFilterElements(&elements1);
	// filter2.SetFilterElements(&elements2);
	/* So whatever is running on Port 4000 is Low Priority */

  /* Adding these filters to test against */
  // trafficClassLow->AddFilter(filter1);
  // trafficClassHigh->AddFilter(filter2);
  trafficClassLow.AddFilter(filter1);
  trafficClassHigh.AddFilter(filter2);
  // q_class[0]->AddFilter(filter1);
  // q_class[1]->AddFilter(filter2);
  /* Add them to q_class */
  /* Low is 0 */
  q_class.push_back(&trafficClassLow);
  q_class.push_back(&trafficClassHigh);
}
template <typename Item>
Spq<Item>::~Spq ()
{

}
/* The QueueMode specifies whether service is in byte mode or packet mode */

/* For network queues, Enqueue() and Dequeue() functions can be
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

template <typename Item>
bool Spq<Item>::DoEnqueue(Ptr<Item> T) {
    // std::cout << "DoEnqueue\n";
    /* Figure out which traffic class to add this to by calling classify */
    // int priority = Classify(T);
    // std::cout << "priority: " << priority << "\n";
    // return q_class[priority]->Enqueue((Ptr<Packet>) T);
   return Spq<Item>::Enqueue(T);
};

/* Enqueue in the High Priority Queue if it's a match I imagine */
template <typename Item>
bool Spq<Item>::Enqueue(Ptr<Item> T) {
	// std::cout << "Enqueue\n";
	/* Figure out which traffic class to add this to by calling classify */
    int priority = Classify(T);
    // std::cout << "priority: " << priority << "\n";
    return q_class[priority]->Enqueue((Ptr<Packet>) T);
};

/* Remove next packet from queue. p2p should use this internally to decide
what to send next */
template <typename Item>
Ptr<Item> Spq<Item>::DoDequeue(void) {
    // std::cout << "DoDequeue\n";

    /* This removes the packet from the correct traffic class */
    Ptr<Item> T = Schedule();

    /* Convert the item to a packet */
    Ptr<Packet> p = (Ptr<Packet>)T;
    Ptr<Packet> copy = p->Copy ();

    PppHeader ppp;

    /* Now prepare to send to destination */
    copy->RemoveHeader (ppp);
    Ipv4Header iph;
    copy->RemoveHeader (iph);
    /* Iterate through the vectors. If high priority vector is not empty 
    dequeue from that one. Else dequeue from the other one */

    /* Never came across the high priority queue */
    return T;   
};

/* Remove next packet from queue. p2p should use this internally to decide
what to send next */
template <typename Item>
Ptr<Item> Spq<Item>::Dequeue(void) {
	// std::cout << "Dequeue\n";

	/* This removes the packet from the correct traffic class */
	Ptr<Item> T = Schedule();

  if (T == 0) 
    { 
      return 0;
    }

	/* Convert the item to a packet */
	Ptr<Packet> p = (Ptr<Packet>)T;
	Ptr<Packet> copy = p->Copy ();

  PppHeader ppp;

  /* Now prepare to send to destination */
  copy->RemoveHeader (ppp);
  Ipv4Header iph;
  copy->RemoveHeader (iph);
	/* Iterate through the vectors. If high priority vector is not empty 
	dequeue from that one. Else dequeue from the other one */

	/* Never came across the high priority queue */
	return T;	
};

/* Get most recent Packet but do not remove */
template <typename Item>
Ptr<const Item> Spq<Item>::DoPeek(void) {
	return this -> Peek ();
};

/* The schedule function carries out designed Quality-of-Service (QoS) algorithm to schedule which
traffic queue to be served at the time. */
template <typename Item>
Ptr<Item> Spq<Item>::Schedule() 
{
  // std::cout << "Schedule\n";
  /* If we received a high priority packet, deal with that first */
  if (this -> q_class[1]->GetSizeBytes() != 0) 
    {
      /* Retun the object that we'd like to dequeue */
      return (Ptr<Item>)(this -> q_class[1]->Dequeue());
    } 
  else if (this -> q_class[0]->GetSizeBytes() != 0)
    {
      /* Bug is here */
      return (Ptr<Item>)(this -> q_class[0]->Dequeue());
    } 
  // std::cout << "queues are empty\n";
  return 0;
}; 

/* The classify function utilizes filter aspect to sort the traffic packets into appropriate traffic
queues. */
template <typename Item>
uint32_t Spq<Item>::Classify(Ptr<Item> p) 
{
	/* Decide which queue to inert this packet into */
    // std::cout << "Classify\n";
	Ptr<Packet> packet = (Ptr<Packet>)p;
  for (int i = 0; i < (int) q_class.size(); i++) {
      std::cout << "asfaasf " << q_class[i]->GetPackets() << "\n";
      if (q_class[i]->match(packet)) {
          std::cout << "Match\n";
          return i;
      }
  }
  // std::cout << "No match\n";
  /* Otherwise return whatever is the default queue, so 0 */
  return 0;
};

// template class Spq<Packet>;
}

