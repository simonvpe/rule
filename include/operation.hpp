#pragma once

namespace Rule
{
    namespace Operation
    {

        namespace Draw
        {
            class OutOfEntitiesError : public std::exception {};
        
            template<typename Collection>
            auto top(std::shared_ptr<Collection> &collection, std::size_t n = 0)
            {
                if(n > collection->size()) throw OutOfEntitiesError();

                using T = typename std::remove_reference<decltype(collection->top())>::type;
                auto ret = std::vector<T>{ };
                                                     
                for(std::size_t i = 0 ; i < n ; ++i)
                    {
                        ret.push_back(collection->top());
                        collection->pop();
                    }
                return ret;
            } // function top
            
        } // namespace Draw
    } // namespace Operation
} // namespace Rule
