/*
** Copyright 2020 Bloomberg Finance L.P.
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/
#ifndef BLOOMBERG_AMQPPROX_EVENTSOURCE
#define BLOOMBERG_AMQPPROX_EVENTSOURCE

#include <amqpprox_eventsourcesignal.h>

#include <memory>

namespace Bloomberg {
namespace amqpprox {

class Backend;
class Session;
class StatCollector;

/**
 * \brief Provides a central source of events relating to connections
 *
 */
class EventSource {
  public:
    using ConnectionReceived = EventSourceSignal<uint64_t>;
    using ConnectionVhostEstablished =
        EventSourceSignal<uint64_t, const std::string &>;
    using ConnectionEstablished   = EventSourceSignal<uint64_t>;
    using ConnectionFailed        = EventSourceSignal<const Backend &>;
    using BrokerConnectionSnapped = EventSourceSignal<uint64_t>;
    using ClientConnectionSnapped = EventSourceSignal<uint64_t>;
    using CleanDisconnect         = EventSourceSignal<uint64_t>;
    using StatisticsAvailable     = EventSourceSignal<StatCollector *>;

  private:
    std::shared_ptr<ConnectionReceived>         d_connectionReceived;
    std::shared_ptr<ConnectionVhostEstablished> d_connectionVhostEstablished;
    std::shared_ptr<ConnectionEstablished>      d_connectionEstablished;
    std::shared_ptr<ConnectionFailed>           d_connectionFailed;
    std::shared_ptr<BrokerConnectionSnapped>    d_brokerConnectionSnapped;
    std::shared_ptr<ClientConnectionSnapped>    d_clientConnectionSnapped;
    std::shared_ptr<CleanDisconnect>            d_cleanDisconnect;
    std::shared_ptr<StatisticsAvailable>        d_statisticsAvailable;

  public:
    EventSource();

    /**
     * \brief Emitted after a connection is received, before the handshaking
     * begins
     * \return signal relating to the connection initation
     */
    ConnectionReceived &connectionReceived() { return *d_connectionReceived; }

    /**
     * \brief Emitted after a connection has done enough handshaking to
     * determine its vhost
     * \return signal relating to the vhost connection
     */
    ConnectionVhostEstablished &connectionVhostEstablished()
    {
        return *d_connectionVhostEstablished;
    }

    /**
     * \brief Emitted after a connection has been fully established
     * \return signal relating to the established connection
     */
    ConnectionEstablished &connectionEstablished()
    {
        return *d_connectionEstablished;
    }

    /**
     * \brief Emitted after a connection to a backend fails
     * \return signal relating to the failed connection
     */
    ConnectionFailed &connectionFailed() { return *d_connectionFailed; }

    /**
     * \brief Emitted after a connection to a backend snaps
     * \return signal relating to the broker snapped connection
     */
    BrokerConnectionSnapped &brokerConnectionSnapped()
    {
        return *d_brokerConnectionSnapped;
    }

    /**
     * \brief Emitted after a connection from a client snaps
     * \return signal relating to the client snapped connection
     */
    ClientConnectionSnapped &clientConnectionSnapped()
    {
        return *d_clientConnectionSnapped;
    }

    /**
     * \brief Emitted after a connection disconnects gracefully
     * \return signal relating to the clean disconnect
     */
    CleanDisconnect &cleanDisconnectClient() { return *d_cleanDisconnect; }

    /**
     * \brief Emitted when statistics are available for collection
     * \return handle to the `StatsCollector`
     */
    StatisticsAvailable &statisticsAvailable()
    {
        return *d_statisticsAvailable;
    }

    // TODO signal wishlist
    // Slow response
    // Heartbeat volatility
    // Missing heartbeat
    // Hitting traffic shaping limits
    // High water mark of incoming connections: 10k?
};

}
}

#endif
