/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright 2007 University of Washington
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#include "ns3/log.h"
#include "ns3/packet.h"
#include "ns3/uinteger.h"
#include "ns3/trace-source-accessor.h"
#include "ns3/ipv4-header.h"
#include "ns3/udp-header.h"
#include "DestinationPortNumberFilter.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>
#include <bitset>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("DestinationPortNumberFilter");

// NS_OBJECT_ENSURE_REGISTERED (DestinationPortNumberFilter);

TypeId
DestinationPortNumberFilter::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::DestinationPortNumberFilter")
    .SetParent<FilterElement> ()
    .SetGroupName("DiffServ")
    .AddAttribute("Port",
                   "Source port number",
                   UintegerValue (6666),
                   MakeUintegerAccessor (&DestinationPortNumberFilter::value),
                   MakeUintegerChecker<uint32_t> ())
  ;
  return tid;
}

// Constructors
DestinationPortNumberFilter::DestinationPortNumberFilter ()
{
  NS_LOG_FUNCTION (this);
}

DestinationPortNumberFilter::~DestinationPortNumberFilter()
{

  NS_LOG_FUNCTION (this);
}

bool 
DestinationPortNumberFilter::Match (Ptr<ns3::Packet> packet)
{
  NS_LOG_FUNCTION (this << packet);
  // std::cout << "THIS IS A DESTINATION PORT FILTER ELEMENT\n";
  Ptr<ns3::Packet> copy = packet->Copy();
  if (copy->GetSize() == 0)
  {
    std::cout << "empty packet...\n";
    return false;
  }
  // Remove Ipv4Header
  Ipv4Header removedHeader;
  copy->RemoveHeader(removedHeader);
  // Get UDP header
  UdpHeader header;
  // std::cout << "peeking header...\n";
  copy->PeekHeader(header); // Get the udp header from the packet
  // std::cout << "checking address...\n";
  uint32_t destPort = header.GetDestinationPort();
  bool matches = destPort == value;
  std::cout << "dest port: " << destPort << " vs value: " << value << "\tmatches: "<< matches << "\n";
  return destPort == value;
}

void 
DestinationPortNumberFilter::SetPort (uint32_t port)
{
  value = port;
}
} // Namespace ns3
