/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef TRAFFICCLASS_H
#define TRAFFICCLASS_H

#include "ns3/queue.h"
#include "ns3/address.h"
#include "ns3/node.h"
#include "ns3/net-device.h"
#include "ns3/callback.h"
#include "ns3/packet.h"
#include "ns3/traced-callback.h"
#include "ns3/nstime.h"
#include "ns3/data-rate.h"
#include "ns3/ptr.h"
#include "ns3/mac48-address.h"


namespace ns3 {
template <typename Item> class Queue;

class TrafficClass
{
public:
	vector<Filter*> filters;

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
	uint32_t maxBytes
	double_t weight;
	uint32_t priority_level;
	bool isDefault;
	std::queue<Ptr<ns3::Packet>> m_queue;
};

}


#endif /* TRAFFICCLASS_H */

