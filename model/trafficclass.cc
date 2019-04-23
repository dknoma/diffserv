/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "trafficclass.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("TrafficClass");
NS_OBJECT_ENSURE_REGISTERED (TrafficClass);

TypeId TrafficClass::GetTypeId (void) {
	static TypeId tid = TypeId ("ns3::TrafficClass");
	return tid;
}

// constructor
TrafficClass::TrafficClass()
{
  NS_LOG_FUNCTION (this);
}

TrafficClass::~TrafficClass ()
{
  NS_LOG_FUNCTION (this);
}

uint32_t TrafficClass::GetPriorityLevel()
{
	return this -> priority_level;
}

void TrafficClass::SetPriorityLevel(uint32_t p)
{
	this -> priority_level = p;
}

double TrafficClass::GetWeight()
{
	return this -> weight;
}

void TrafficClass::SetWeight(double w)
{
	this -> weight = w;
}

}

