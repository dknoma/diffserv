/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef DIFFSERV_H
#define DIFFSERV_H

#include "ns3/diffserv.h"


namespace ns3 {
template <typename Item> class Queue;

/* DRR class inherits from DiffServ Class and implements Deficit Round Robin Queue */

class Drr : public DiffServ
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

};

}


#endif /* DRR_H */

