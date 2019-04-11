/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef SPQ_H
#define SPQ_H

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
#include "ns3/spq.h"


namespace ns3 {
template <typename Item> class Queue;

/* DiffServ class provides basic functionalities required to simulate
differentiated services */

class Spq : public DiffServ
{
public:

	/**
	* \brief Get the TypeId
	*
	* \return The TypeId for this class
	*/
	static TypeId GetTypeId (void);

	/**
	* Construct a Spq
	*
	* This is the constructor for the Diffserv.  It takes as a
	* parameter a pointer to the Node to which this device is connected, 
	* as well as an optional DataRate object.
	*/
	Spq ();

	/**
	* Destroy a Spq
	*
	* This is the destructor for the Diffserv.
	*/
	virtual ~Spq ();

};

}


#endif /* Spq_H */

