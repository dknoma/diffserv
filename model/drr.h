/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef DRR_H
#define DRR_H

#include "ns3/diffserv.h"


namespace ns3 {


/* DRR class inherits from DiffServ Class and implements Deficit Round Robin Queue */
class Drr : public DiffServ<Packet>
{
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
	Drr ();

	/**
	* Destroy a DiffServ
	*
	* This is the destructor for Drr.
	*/
	virtual ~Drr ();
	bool DoEnqueue(Ptr<Packet> T);
	Ptr<const ns3::Packet>DoPeek();
	Ptr<Packet> DoDequeue(void);
	Ptr<ns3::Packet> Schedule();
	uint32_t Classify(Ptr<ns3::Packet> p);
	std::vector<TrafficClass<Packet>*> q_class;
};

}


#endif /* DRR_H */

