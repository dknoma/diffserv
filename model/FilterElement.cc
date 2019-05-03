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
#include "FilterElement.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>
#include <bitset>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("FilterElement");

NS_OBJECT_ENSURE_REGISTERED (FilterElement);

TypeId
FilterElement::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::FilterElement")
    .SetParent<Object> ()
    .SetGroupName("DiffServ")
  ;
  return tid;
}

// Constructors
FilterElement::FilterElement ()
{
  NS_LOG_FUNCTION (this);
}

FilterElement::~FilterElement()
{

  NS_LOG_FUNCTION (this);
}

bool 
FilterElement::Match (Ptr<ns3::Packet> packet)
{
  // std::cout << "Filter Element Match called" << "\n";
  NS_LOG_FUNCTION (this << packet);
  return false;
}
} // Namespace ns3
