//
//  Subject.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 07/12/2017.
//  Copyright © 2017 Cihan Ozer. All rights reserved.
//

#ifndef Subject_hpp
#define Subject_hpp

#include "Observer.hpp"

#include <list>
#include <map>

// Base template class for the subject in Observer Design Pattern
template<class T>
class Subject
{
public:
    Subject()
    {
        
    }
    
    virtual ~Subject()
    {
        clear();
    }
    
    void attach( Observer* const object, void(Observer::* const func)(T) )
    {
        using namespace std::placeholders;
        
        auto it = mObserverRegister.find( object->getId() );
        if(it == mObserverRegister.end() )
        {
            mObserverList.emplace_back( std::bind(func, object, _1) );
            mObserverRegister.insert( std::pair<int, typename std::list< std::function<void(T)> >::iterator>(object->getId(), std::prev(mObserverList.end() ) ) );
        }
    }
    
    void detach(const int pObserverId)
    {
        auto it = mObserverRegister.find(pObserverId);
        if(it != mObserverRegister.end() )
        {
            mObserverList.erase( mObserverRegister[pObserverId] );
            mObserverRegister.erase(it);
        }
    }
    
    void notify(T& pEvent)
    {
        for( const auto& elem : mObserverList)
        {
            elem(pEvent);
        }
    }
    
    // Clear the subject: Clear the attached observer list
    void clear()
    {
        mObserverRegister.clear();
        mObserverList.clear();
    }
    
private:
    
    // For better management
    std::list< std::function<void(T)> > mObserverList;
    std::map<int, typename std::list< std::function<void(T)> >::iterator> mObserverRegister;
    
};

#endif /* Subject_hpp */
