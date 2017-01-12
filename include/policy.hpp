#pragma once

namespace Rule
{
    namespace Policy
    {
        namespace Containment
        {
            struct ContainmentError : public std::exception { };
                
            template<typename T>
            struct None {
                static bool validate(const T &item)
                {
                    return true;
                }
            }; // struct None

            template<typename T, typename U, typename V>
            struct Join {
                static bool validate(const T &item)
                {
                    return U::validate(item) && V::validate(item);
                }
            }; // struct Join
            
        } // namespace Containment

    } // namespace Policy
} // namespace Rule
