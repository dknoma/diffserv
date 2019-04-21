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

#ifndef FILTER_ELEMENT_HELPER_H
#define FILTER_ELEMENT_HELPER_H

#include "ns3/FilterElement.h"
#include "ns3/event-id.h"
#include "ns3/object.h"
#include "ns3/object-factory.h"
#include "ns3/packet.h"
#include "ns3/ptr.h"
#include "ns3/traced-callback.h"

namespace ns3 {

/**
 * \ingroup filterelement
 * \brief A Filter Element
 *
 * Every packet sent should be matched against one of these Filter Elements
 */
class SourcePortNumberFilterHelper
{
public:
  SourcePortNumberFilterHelper (uint32_t port);

  void SetAttribute (std::string name, const AttributeValue &value);
 
private:
  
  ObjectFactory m_factory; //!< Object factory.
};

} // namespace ns3

#endif /* FILTER_ELEMENT_H */
