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
#include "ns3/object-vector.h"
#include "ns3/packet.h"
#include "ns3/uinteger.h"
#include "ns3/trace-source-accessor.h"
#include "Filter.h"
#include "FilterElement.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>
#include <bitset>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("Filter");

NS_OBJECT_ENSURE_REGISTERED (Filter);

TypeId
Filter::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::Filter")
    .SetParent<Object> ()
    .SetGroupName("DiffServ")
    .AddAttribute ("FilterElements", 
                   "The list of filter elements of the inbound packets",
                   ObjectVectorValue (),
                   MakeObjectVectorAccessor (&Filter::elements),
                   MakeObjectVectorChecker<FilterElement> ())
  ;
  return tid;
}

// Constructors
Filter::Filter ()
{
  NS_LOG_FUNCTION (this);
  std::vector<FilterElement*> elements;
}

Filter::~Filter()
{
  NS_LOG_FUNCTION (this);
}

bool 
Filter::Match (Ptr<ns3::Packet> packet)
{
  NS_LOG_FUNCTION (this << packet);
  // TODO: for each element in vector, check its virtual match against the corresponding packet element
  // Elements ^/AND each other. HAS to satisfy ALL filter elements for this specific filter
  bool matching = false;
  // for (std::vector<FilterElement*>::iterator i = elements.begin(); i != elements.end(); ++i)
  for(uint32_t i = 0; i < elements.size(); i++)
  {
    std::cout << "filter element[" << i << "]\n";
    matching = elements.at(i) -> Match(packet);
  }
  return matching;
}

void
Filter::SetElements(std::vector<FilterElement*> filterElements)
{
  NS_LOG_FUNCTION (this);
  elements = filterElements;
}
} // Namespace ns3
