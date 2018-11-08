//
//  StateMachine.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 12/09/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef StateMachine_hpp
#define StateMachine_hpp

#include "State.hpp"
#include "IGameObject.hpp"

// A state machine
template <class entity_type>
class StateMachine : public IGameObject
{
public:
    
    StateMachine()
        :mOwner(nullptr), mCurrentState(&mNullState), mPreviousState(&mNullState), mGlobalState(&mNullState)
    { }
    
    StateMachine(entity_type* pOwner)
        :mOwner(pOwner), mCurrentState(&mNullState), mPreviousState(&mNullState), mGlobalState(&mNullState)
    { }
    
    virtual ~StateMachine() {}
    
    State<entity_type>*  getGlobalState()   const {return mGlobalState;}
    State<entity_type>*  getCurrentState()  const {return mCurrentState;}
    State<entity_type>*  getPreviousState() const {return mPreviousState;}

    void setGlobalState(State<entity_type>* pState) { mGlobalState = pState; }
    void setCurrentState(State<entity_type>* pState) { mCurrentState = pState; }
    void setPreviousState(State<entity_type>* pState) { mPreviousState = pState; }
    
    void  callOnFrame() override
    {
        // Global state is a state you need to call every frame -if you need one.
        mGlobalState->onExecute(mOwner);
        mCurrentState->onExecute(mOwner);
    }
    
    void  changeState(State<entity_type>* pNewState)
    {
        // Keep a record of the previous state
        mPreviousState = mCurrentState;
        
        // Call the exit method of the existing state
        mCurrentState->onExit(mOwner);
        
        // Change state to the new state
        mCurrentState = pNewState;
        
        // Call the entry method of the new state
        mCurrentState->onEnter(mOwner);
    }
    
    // Change state back to the previous state
    void  revertToPreviousState()
    {
        ChangeState(mPreviousState);
    }
    
    // Check if the current state and the given state are the same
    bool  isInState(const State<entity_type>& pState) const
    {
        return typeid(*mCurrentState) == typeid(pState);
    }

private:
    
    // Null object pattern:
    //
    // Object of this class will assign to global, current, and previous states by default.
    // This will save us from constant null checks and one-time null preventing logics, such
    // as very first call for changeState() in the late-initialization step.
    class NullState : public State<entity_type>
    {
    public:
        
        virtual ~NullState() {}
        void onEnter(entity_type*) {}
        void onExecute(entity_type*) {}
        void onExit(entity_type*) {}
    };
    
    
    void performInit(const int pArgNumber, va_list args) override
    {
        // TODO Solve this
        mOwner = va_arg(args, entity_type*);
    }
    
    // A pointer to the owner -not ownership
    entity_type* mOwner;
    
    NullState mNullState;
    State<entity_type>*   mGlobalState; // The global state is called every time the FSM is updated
    State<entity_type>*   mCurrentState;
    State<entity_type>*   mPreviousState;

};

#endif /* StateMachine_hpp */
