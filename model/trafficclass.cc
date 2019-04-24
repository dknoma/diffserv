/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "trafficclass.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("TrafficClass");
// NS_OBJECT_ENSURE_REGISTERED (TrafficClass);

template <typename Item>
TypeId TrafficClass<Item>::GetTypeId (void) {
	static TypeId tid = TypeId ("ns3::TrafficClass");
	return tid;
}

// constructor
template <typename Item>
TrafficClass<Item>::TrafficClass()
{
  NS_LOG_FUNCTION (this);
}

template <typename Item>
TrafficClass<Item>::~TrafficClass ()
{
  NS_LOG_FUNCTION (this);
}

template <typename Item>
uint32_t TrafficClass<Item>::GetPriorityLevel()
{
	return this -> priority_level;
}

template <typename Item>
void TrafficClass<Item>::SetPriorityLevel(uint32_t p)
{
	this -> priority_level = p;
}

template <typename Item>
double TrafficClass<Item>::GetWeight()
{
	return this -> weight;
}

template <typename Item>
void TrafficClass<Item>::SetWeight(double w)
{
	this -> weight = w;
}

template <typename Item>
bool TrafficClass<Item>::GetIsDefault()
{
	return this -> isDefault;
}

template <typename Item>
void TrafficClass<Item>::SetIsDefault(bool p)
{
	this -> isDefault = p;
}

template <typename Item>
void TrafficClass<Item>::AddFilter(Filter *f)
{
	this -> filters.push_back(f);
}

template <typename Item>
bool TrafficClass<Item>::Enqueue(Ptr<Item> T)
{
	return this -> Enqueue(T);
}

template <typename Item>
Ptr<Item> TrafficClass<Item>::Dequeue(void)
{
	return this -> Dequeue ();
}

template <typename Item>
bool TrafficClass<Item>::match(Ptr<Item> T)
{
	/* Check filter to see if packet matches */
	for(std::vector<Filter*>::size_type i = 0; i != this -> filters.size(); i++) {
    	filters[i] -> Match(T);
	}
	/* Add to internal queue if it's a match */

	/* And return true if it's a match */

	/* Return false if now */
	return false;
}
template class TrafficClass<Packet>;

}

