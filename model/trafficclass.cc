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
    packets = 0;
    bytes = 0;
    maxBytes = 1000000;
    maxPackets = 100000;
    weight = 1; 
    priority_level = 0; 
    isDefault = false;
}

template <typename Item>
TrafficClass<Item>::~TrafficClass ()
{

}

template <typename Item>
int TrafficClass<Item>::GetPriorityLevel()
{
	return this -> priority_level;
}

template <typename Item>
void TrafficClass<Item>::SetPriorityLevel(int p)
{
	this -> priority_level = p;
}

template <typename Item>
uint32_t TrafficClass<Item>::GetPackets()
{
	return this -> packets;
}

template <typename Item>
void TrafficClass<Item>::SetPackets(uint32_t p)
{
	this -> packets = p;
}

template <typename Item>
uint32_t TrafficClass<Item>::GetSizeBytes()
{
	return this -> bytes;
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
bool TrafficClass<Item>::IsEmpty()
{
	if (this->packets == 0) {
		return true;
	}
	return false;
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
	// std::cout << "Enqueue tc\n";
	Ptr<Packet> packet = (Ptr<Packet>) T;
    // if (packets + 1 > maxPackets || bytes + packet->GetSize() > maxBytes) {
    //     return false;
    // }
	/* Add to Queue */
    m_queue.push(packet);

    /* Add Bytes/Packets */
    this->packets++;
    this->bytes += packet->GetSize();
    return true;
}


template <typename Item>
Ptr<Item> TrafficClass<Item>::Dequeue(void)
{
	if (m_queue.empty()) {
    	// std::cout << "null? \n";
        return 0;
    } else {
    	// Get packet from front of Queue 
    	// std::cout << "non-empty? \n";
        Ptr <Packet> packet = m_queue.front();
        m_queue.pop();
        packets--;
        bytes -= packet->GetSize();
        return packet;
    }
}

template <typename Item>
bool TrafficClass<Item>::match(Ptr<Item> T)
{
    // std::cout << "TC match\n";
	/* Check filter to see if packet matches */
	bool matching = false;
	// for(std::vector<Filter*>::size_type i = 0; i != this -> filters.size(); i++) {
 //        std::cout << "checking tc matches\n";
 //    	matching = matching || filters[i] -> Match(T);
 //    	std::cout << matching << std::endl;
	// }

    std::cout << "filter size: " << filters.size() << "\n";
	for(uint32_t i = 0; i < filters.size(); i++)
	  {
	    std::cout << "filter[" << i << "]\n";
        // std::cout << "checking tc matches\n";
	    matching = matching || filters.at(i) -> Match(T); // Matches at least one of the filter elements
    	// std::cout << matching << std::endl;
	  }

	/* Add to internal queue if it's a match */

	/* And return true if it's a match */

	/* Return false if now */
  	std::cout << matching << std::endl;
	return matching;
}
template class TrafficClass<Packet>;

}

