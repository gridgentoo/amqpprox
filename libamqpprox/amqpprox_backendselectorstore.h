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
#ifndef BLOOMBERG_AMQPPROX_BACKENDSELECTORSTORE
#define BLOOMBERG_AMQPPROX_BACKENDSELECTORSTORE

#include <amqpprox_backendselector.h>

#include <map>
#include <memory>
#include <string>

namespace Bloomberg {
namespace amqpprox {

/**
 * \brief Store for different types of `BackendSelector`
 */
class BackendSelectorStore {
  private:
    // DATA
    std::map<std::string, std::unique_ptr<BackendSelector>> d_store;

  public:
    // MANIPULATORS
    /**
     * \brief Add the specified `BackendSelector` to the map of named selectors
     * installed in this store.
     * \param backendSelector Backend selector
     */
    void addSelector(std::unique_ptr<BackendSelector> backendSelector);

    // ACCESSORS
    /**
     * \brief Return a pointer to the `BackendSelector` instance with the
     * specified `name`.
     * \param name Backend selector name
     * \return Backend selector
     */
    BackendSelector *getSelector(const std::string &name) const;
};

}
}

#endif
