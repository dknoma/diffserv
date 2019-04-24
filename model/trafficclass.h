/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef TRAFFICCLASS_H
#define TRAFFICCLASS_H

#include "Filter.h"
#include "ns3/node.h"
#include "ns3/log.h"
#include <queue>
#include "ns3/drop-tail-queue.h"


namespace ns3 {
template <typename Item>
class TrafficClass : public DropTailQueue<Item>
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
	* Construct a TrafficClass
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
	/* Getters and Setters for Priority Level and Weights */
	uint32_t GetPriorityLevel(void);
	void SetPriorityLevel(uint32_t p);

	bool GetIsDefault(void);
	void SetIsDefault(bool p);

	double GetWeight(void);
	void SetWeight(double w);

	/* Add Filter to Filters Vector, may or may not need */
	void AddFilter (Filter *f);

	/* Enqueue and Dequeue to add the packets */
	bool Enqueue(Ptr<Item> T);
	Ptr<Item> Dequeue(void);

	/* Match */
	bool match (Ptr<Item> T);


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
	std::queue<Ptr<Packet>> m_queue;
};

}


#endif /* TRAFFICCLASS_H */

