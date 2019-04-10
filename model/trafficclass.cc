/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "diffserv.h"
#include "ns3/queue.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("DiffServ");
NS_OBJECT_ENSURE_REGISTERED (DiffServ);

/* The QueueMode specifies whether service is in byte mode or packet mode */
QueueMode m_mode;
vector<TrafficClass*> q_class; 
/* 
bool DiffServ::DoEnqueue(Ptr<ns3::Packet> p) {

};
Ptr<ns3::Packet> DiffServ::DoDequeue(void) {

};
Ptr<ns3::Packet> DiffServ::DoRemove(void) {

};
Ptr<ns3::Packet> DiffServ::DoPeek(void) {

};
void DiffServ::SetMode(QueueMode mode) {

};
QueueMode DiffServ::GetMode(void) {

};
Ptr<ns3::Packet> DiffServ::GetMode(void) {

};
uint32_t DiffServ::Classify(Ptr<ns3::Packet> p) {
	
};
*/

}

