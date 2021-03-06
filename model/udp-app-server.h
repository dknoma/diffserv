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

#ifndef UDP_APP_SERVER_H
#define UDP_APP_SERVER_H

#include "ns3/application.h"
#include "ns3/event-id.h"
#include "ns3/ptr.h"
#include "ns3/address.h"
#include "ns3/traced-callback.h"
#include <chrono>

namespace ns3 {

class Socket;
class Packet;

/**
 * \ingroup applications 
 * \defgroup udpapp UdpApp
 */

/**
 * \ingroup udpapp
 * \brief A Udp App server
 *
 * Every packet received is sent back.
 */
class UdpAppServer : public Application 
{
public:
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);
  UdpAppServer ();
  virtual ~UdpAppServer ();

protected:
  virtual void DoDispose (void);

private:

  virtual void StartApplication (void);
  virtual void StopApplication (void);

  /**
   * \brief Handle a packet reception.
   *
   * This function is called by lower layers.
   *
   * \param socket the socket the packet was received to.
   */
  void HandleRead (Ptr<Socket> socket);

  uint16_t m_port; //!< Port on which we listen for incoming packets.
  uint16_t m_size; //!< Size of packets
  uint16_t m_count;//!< Max number of packets
  uint16_t m_received_l;//!< Number of packets received
  uint16_t m_received_h;//!< Number of packets received
  bool receivedAllLowEntropy;
  float m_duration_l; //!< Time
  float m_duration_h; //!< Time
  float m_duration_total; //!< Time
  std::chrono::system_clock::time_point m_first_high; //!< first clock
  std::chrono::system_clock::time_point m_last_high;  //!< last clock
    std::chrono::system_clock::time_point m_first_low; //!< first clock
  std::chrono::system_clock::time_point m_last_low;  //!< last clock
  std::chrono::system_clock::time_point m_last_total;  //!< last clock
  std::chrono::system_clock::time_point m_first_total;  //!< last clock

  Ptr<Socket> m_socket; //!< IPv4 Socket
  Ptr<Socket> m_socket6; //!< IPv6 Socket
  Address m_local; //!< local multicast address

  /// Callbacks for tracing the packet Rx events
  TracedCallback<Ptr<const Packet> > m_rxTrace;

  /// Callbacks for tracing the packet Rx events, includes source and destination addresses
  TracedCallback<Ptr<const Packet>, const Address &, const Address &> m_rxTraceWithAddresses;
};

} // namespace ns3

#endif /* UDP_APP_SERVER_H */