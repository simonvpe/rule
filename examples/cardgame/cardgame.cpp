#include <type_traits>
#include <vector>
#include <string>
#include <algorithm>
#include "gsl/gsl"
#include <experimental/array>

#include "context.hpp"

namespace Card
{
    enum class Property {
        None                         = 0x00000000,
        Hearts                       = 0x00000001,
        Spades                       = 0x00000002,
        Diamonds                     = 0x00000004,
        Clubs                        = 0x00000008,
        Deuce                        = 0x00000010,
        Three                        = 0x00000020,
        Four                         = 0x00000040,
        Five                         = 0x00000080,
        Six                          = 0x00000100,
        Seven                        = 0x00000200,
        Eight                        = 0x00000400,
        Nine                         = 0x00000800,
        Ten                          = 0x00001000,
        Jack                         = 0x00002000,
        Queen                        = 0x00004000,
        King                         = 0x00008000,
        Ace                          = 0x00010000
    };

    struct Card {
        const Property properties;
    };
    
    template<typename T>
    inline constexpr T operator | (T lhs, T rhs) {
        using U = std::underlying_type_t<T>;
        return static_cast<T>((static_cast<U>(lhs) | static_cast<U>(rhs)));
    }

    template<typename T>
    inline constexpr T operator & (T lhs, T rhs) {
        using U = std::underlying_type_t<T>;
        return static_cast<T>((static_cast<U>(lhs) & static_cast<U>(rhs)));
    }
    
    namespace Policy {

        /**
         * Tests that a card has a single suit and a single number
         **/
        struct DeckPolicy
        {
            static bool validate(const Card &item)
            {
                using T = typename std::underlying_type_t<Property>;
                auto x = static_cast<const T>(item.properties);

                auto testSuit = [](auto itemProp, auto prop) {
                    return ((itemProp & 0x00007) ^ static_cast<T>(prop)) == 0;
                };

                auto testNumber = [](auto itemProp, auto prop) {
                    return ((itemProp & 0x1fff8) ^ static_cast<T>(prop)) == 0;
                };
                    
                auto singleSuit = 
                    testSuit(x,Property::Hearts  ) ||
                    testSuit(x,Property::Clubs   ) ||
                    testSuit(x,Property::Spades  ) ||
                    testSuit(x,Property::Diamonds) ||
                    false;
        
                auto singleNumber =
                    testNumber(x,Property::Deuce) ||
                    testNumber(x,Property::Three) ||
                    testNumber(x,Property::Four ) ||
                    testNumber(x,Property::Five ) ||
                    testNumber(x,Property::Six  ) ||
                    testNumber(x,Property::Seven) ||
                    testNumber(x,Property::Eight) ||
                    testNumber(x,Property::Nine ) ||
                    testNumber(x,Property::Ten  ) ||
                    testNumber(x,Property::Jack ) ||
                    testNumber(x,Property::Queen) ||
                    testNumber(x,Property::King ) ||
                    testNumber(x,Property::Ace  ) ||
                    false;
                    
                return singleSuit && singleNumber;
            }
        };
    }
}

#include <iostream>
int main()
{
    auto ctx = Rule::Context{};

    auto cardEntities = ctx.makeEntities<Card::Card>({
        {{ Card::Property::Hearts | Card::Property::Deuce }},
        {{ Card::Property::Hearts | Card::Property::Three }},
        {{ Card::Property::Hearts | Card::Property::Four  }},
        {{ Card::Property::Hearts | Card::Property::Five  }},            
        {{ Card::Property::Hearts | Card::Property::Six   }},
        {{ Card::Property::Hearts | Card::Property::Seven }},
        {{ Card::Property::Hearts | Card::Property::Eight }},
        {{ Card::Property::Hearts | Card::Property::Nine  }},
        {{ Card::Property::Hearts | Card::Property::Ten   }},
        {{ Card::Property::Hearts | Card::Property::Jack  }},
        {{ Card::Property::Hearts | Card::Property::Queen }},
        {{ Card::Property::Hearts | Card::Property::King  }},
        {{ Card::Property::Hearts | Card::Property::Ace   }},                        

        {{ Card::Property::Diamonds | Card::Property::Deuce }},
        {{ Card::Property::Diamonds | Card::Property::Three }},
        {{ Card::Property::Diamonds | Card::Property::Four  }},
        {{ Card::Property::Diamonds | Card::Property::Five  }},            
        {{ Card::Property::Diamonds | Card::Property::Six   }},
        {{ Card::Property::Diamonds | Card::Property::Seven }},
        {{ Card::Property::Diamonds | Card::Property::Eight }},
        {{ Card::Property::Diamonds | Card::Property::Nine  }},
        {{ Card::Property::Diamonds | Card::Property::Ten   }},
        {{ Card::Property::Diamonds | Card::Property::Jack  }},
        {{ Card::Property::Diamonds | Card::Property::Queen }},
        {{ Card::Property::Diamonds | Card::Property::King  }},
        {{ Card::Property::Diamonds | Card::Property::Ace   }},                        

        {{ Card::Property::Clubs | Card::Property::Deuce }},
        {{ Card::Property::Clubs | Card::Property::Three }},
        {{ Card::Property::Clubs | Card::Property::Four  }},
        {{ Card::Property::Clubs | Card::Property::Five  }},            
        {{ Card::Property::Clubs | Card::Property::Six   }},
        {{ Card::Property::Clubs | Card::Property::Seven }},
        {{ Card::Property::Clubs | Card::Property::Eight }},
        {{ Card::Property::Clubs | Card::Property::Nine  }},
        {{ Card::Property::Clubs | Card::Property::Ten   }},
        {{ Card::Property::Clubs | Card::Property::Jack  }},
        {{ Card::Property::Clubs | Card::Property::Queen }},
        {{ Card::Property::Clubs | Card::Property::King  }},
        {{ Card::Property::Clubs | Card::Property::Ace   }},                        

        {{ Card::Property::Spades | Card::Property::Deuce }},
        {{ Card::Property::Spades | Card::Property::Three }},
        {{ Card::Property::Spades | Card::Property::Four  }},
        {{ Card::Property::Spades | Card::Property::Five  }},            
        {{ Card::Property::Spades | Card::Property::Six   }},
        {{ Card::Property::Spades | Card::Property::Seven }},
        {{ Card::Property::Spades | Card::Property::Eight }},
        {{ Card::Property::Spades | Card::Property::Nine  }},
        {{ Card::Property::Spades | Card::Property::Ten   }},
        {{ Card::Property::Spades | Card::Property::Jack  }},
        {{ Card::Property::Spades | Card::Property::Queen }},
        {{ Card::Property::Spades | Card::Property::King  }},
        {{ Card::Property::Spades | Card::Property::Ace   }},                        
            
    });
    
    // DECK
    auto cards = ctx.makeStack("DECK", Card::Policy::DeckPolicy{}, gsl::make_span(cardEntities));

    return 0;
}
    
