#pragma once

#include <vector>

#include "entity.hpp"
#include "policy.hpp"
#include "gsl/span"

namespace Rule
{
    namespace Collection
    {
        template<typename EntityType> using E = Entity::Entity<EntityType>;
        template<typename EntityType> using C = std::vector<E<EntityType>>;

        // Stack
        template<
            typename    EntityType,
            typename    ContainmentPolicy
        > class Stack : private ContainmentPolicy
        {
            using ContainmentPolicy::validate;
            using EE = E<EntityType>;
            using CE = C<EntityType>;
        public:
            Stack(const char *name, gsl::span<EE> ent)
                : m_name(name)
                , m_entities(ent.begin(), ent.end())
                {
                    //std::all_of(ent.begin(), ent.end(), ContainmentPolicy::validate);
                }
        private:
            const char *m_name;
            CE          m_entities;
        }; // class Stack
        
        template<typename T>
        using PlayerVector = std::vector<Entity::PlayerEntity<T>>;
         
    } // namespace Collections
} // namespace Rule
