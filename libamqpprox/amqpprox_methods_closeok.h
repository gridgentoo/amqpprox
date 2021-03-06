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
#ifndef BLOOMBERG_AMQPPROX_METHODS_CLOSEOK
#define BLOOMBERG_AMQPPROX_METHODS_CLOSEOK

#include <iosfwd>

namespace Bloomberg {
namespace amqpprox {

class Buffer;

namespace methods {

/**
 * \brief Represents AMQP Connection CLOSE-OK method
 */
class CloseOk {
  public:
    /**
     * \brief Encode close-ok method and write the data into buffer
     */
    static inline bool encode(Buffer &buffer, const CloseOk &closeOk)
    {
        return true;  // nothing to encode
    }

    constexpr inline static int classType() { return 10; }

    constexpr inline static int methodType() { return 51; }
};

std::ostream &operator<<(std::ostream &os, const CloseOk &closeOkMethod);
}
}
}

#endif
