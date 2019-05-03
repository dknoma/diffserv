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

#ifndef FILTER_H
#define FILTER_H

#include "ns3/event-id.h"
#include "ns3/object.h"
#include "ns3/packet.h"
#include "ns3/ptr.h"
#include "ns3/traced-callback.h"
#include "FilterElement.h"

namespace ns3 {

/**
 * \ingroup udpapp
 * \brief A Udp App client
 *
 * Every packet sent should be returned by the server and received here.
 */
class Filter : public Object 
{
public:
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);

  std::vector<FilterElement*> elements;

  Filter ();
  Filter (std::vector<FilterElement*> filterElements);
  virtual ~Filter ();


  bool Match(Ptr<ns3::Packet> packet);
  void SetFilterElements(std::vector<FilterElement*> filterElements);

};

} // namespace ns3

#endif /* UDP_APP_CLIENT_H */
