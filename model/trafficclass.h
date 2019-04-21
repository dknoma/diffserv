/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef TRAFFICCLASS_H
#define TRAFFICCLASS_H

#include "Filter.h"
#include "ns3/node.h"
#include "ns3/log.h"
#include <queue>


namespace ns3 {
template <typename Item> class queue;

class TrafficClass
{
public:
	std::vector<Filter*> filters;

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
	TrafficClass ();

	/**
	* Destroy a DiffServ
	*
	* This is the destructor for the Diffserv.
	*/
	virtual ~TrafficClass ();

private:
	/** Data Members */
	uint32_t bytes;
	uint32_t packets;
	uint32_t maxPackets;
	uint32_t maxBytes;

	/* Applicable is QOS uses weight, DRR */
	double weight;

	/* Applicable is QOS uses priority level, SPQ */
	uint32_t priority_level;
	/* One queue that will take over the packets if packet comes in and 
	does not match any of the other classes */
	bool isDefault;
	std::queue<Ptr<ns3::Packet>> m_queue;
};

}


#endif /* TRAFFICCLASS_H */

