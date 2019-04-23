/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef SPQ_H
#define SPQ_H

#include "diffserv.h"


namespace ns3 {

/* DiffServ class provides basic functionalities required to simulate
differentiated services */
class Spq : public DiffServ<Packet>
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
	bool DoEnqueue(Ptr<Packet> T);
	Ptr<const ns3::Packet> DoPeek();
	Ptr<Packet> DoDequeue(void);
	Ptr<ns3::Packet> Schedule(); 
	uint32_t Classify(Ptr<ns3::Packet> p);


};

}


#endif /* Spq_H */

