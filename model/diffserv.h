/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef DIFFSERV_H
#define DIFFSERV_H


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

/* DiffServ class provides basic functionalities required to simulate
differentiated services */

class DiffServ {
public:

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

	bool DoEnqueue(Ptr<ns3::Packet> p);
	Ptr<ns3::Packet> DoDequeue(void);
	//Ptr<ns3::Packet> DoRemove(void);
	Ptr<ns3::Packet> DoPeek(void);
	//void SetMode(QueueMode mode);
	//QueueMode GetMode(void);
	//Ptr<ns3::Packet> GetMode(void);
	/* Returns a packet to transmit. How do we determine this packet?  */
	//Ptr<ns3::Packet> Schedule();
	/*  The classify function utilizes filter aspect to sort the traffic packets into appropriate traffic
	queues. */
	//uint32_t Classify(Ptr<ns3::Packet> p);

};

}


#endif /* DIFFSERV_H */

