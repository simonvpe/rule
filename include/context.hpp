#pragma once

#include "collection.hpp"
#include "policy.hpp"
#include "entity.hpp"
#include "operation.hpp"
#include "gsl/span"

#include <algorithm>
#include <experimental/array>

namespace Rule
{
    struct Context
    {
        constexpr Context() { }

        // makeEntities()
        template<
        typename Payload
        > auto makeEntities(std::initializer_list<Collection::E<Payload>> args) const
        {
            return Collection::C<Payload>(args);
        } // makeEntities()

        // makeStack()
        template<
        typename    Payload,
        typename    ContainmentPolicy = Policy::Containment::None<Payload>
        > auto makeStack(
            const char *name,
            ContainmentPolicy,
            gsl::span<Collection::E<Payload>> ent)
        {
            return Collection::Stack<Payload,ContainmentPolicy>{ name, ent };
        } // makeStack()
        
    }; // struct Context
    
} // namespace Rule
