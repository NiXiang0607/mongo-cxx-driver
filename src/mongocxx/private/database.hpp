// Copyright 2014 MongoDB Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <mongocxx/config/prelude.hpp>

#include <mongocxx/database.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/private/client.hpp>
#include <mongocxx/private/write_concern.hpp>

#include <mongoc.h>

namespace mongocxx {
MONGOCXX_INLINE_NAMESPACE_BEGIN

class database::impl {
   public:
    impl(mongoc_database_t* db, const class client::impl* client, std::string name) :
        database_t(db),
        client_impl(client),
        name(std::move(name))
    {}

    impl(const impl& i) : 
        database_t{libmongoc::database_copy(i.database_t)},
        client_impl{i.client_impl},
        name{i.name} 
    {}

    // This method is deleted because we only use the copy constructor.
    impl& operator=(const impl& i) = delete;

    ~impl() {
        libmongoc::database_destroy(database_t);
    }

    mongoc_database_t* database_t;
    const class client::impl* client_impl;
    std::string name;

};

MONGOCXX_INLINE_NAMESPACE_END
}  // namespace mongocxx

#include <mongocxx/config/postlude.hpp>