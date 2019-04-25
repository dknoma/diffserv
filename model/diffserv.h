/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef DIFFSERV_H
#define DIFFSERV_H

#include <cstring>
#include "trafficclass.h"
#include "ns3/packet.h"
#include "ns3/traced-callback.h"
#include "ns3/nstime.h"
#include "ns3/data-rate.h"
#include "ns3/ptr.h"
#include "ns3/drop-tail-queue.h"

namespace ns3 {

/* DiffServ class provides basic functionalities required to simulate
differentiated services */

/* This makes DiffServ a template */
template <typename Item>
class DiffServ : public DropTailQueue<Item>
{
public:
	std::vector<TrafficClass<Packet>*> q_class;
	/**
	* \brief Get the TypeId
	*
	* \return The TypeId for this class
	*/
	static TypeId GetTypeId (void);

	/**
	* Construct a DiffServ
	*
	* This is the constructor for the Diffserv.  It takes as a
	* parameter a pointer to the Node to which this device is connected, 
	* as well as an optional DataRate object.
	*/
	DiffServ ();

	/**
	* Destroy a DiffServ
	*
	* This is the destructor for the Diffserv.
	*/
	virtual ~DiffServ ();

	/* Required Methods */

	/* This queue will be true for whole vector of traffic classes */
	void AddTrafficClass(TrafficClass<Item>* traffic);
	void SetMode(uint32_t mode);
	uint32_t GetMode();
	bool DoEnqueue(Ptr<Item> T);
	Ptr<Item> DoDequeue(void);
	Ptr<const Item> DoPeek(void);
	/* Also required methods, can be private or public */
	/* Returns a packet to transmit. How do we determine this packet?  */
	virtual Ptr<Item> Schedule();
	/*  The classify function utilizes filter aspect to sort the traffic packets into appropriate traffic
	queues. */
	virtual uint32_t Classify(Ptr<Item> p);
private:

	
	/* If 0, byte mode. If 1, packet mode. */
	uint32_t m_mode;
};

}


#endif /* DIFFSERV_H */

