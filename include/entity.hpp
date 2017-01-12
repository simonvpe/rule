#pragma once
#include <string>
#include <vector>

#include "collection.hpp"

namespace Rule
{
    namespace Entity
    {
        
        template<typename T> class Entity : public T
        {
        public:
            constexpr Entity(const T &item) : T(item) {}
        }; // class Entity

        template<typename T>
        class PlayerEntity : public T
        {
        public:
            PlayerEntity(const T &player) : T(player) {}
        }; // class PlayerEntity
 
        
    } // namespace Entity
} // namespace Rule
