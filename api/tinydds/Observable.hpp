#ifndef __OBSERVABLE__HPP__
#define __OBSERVABLE__HPP__

#include <vector>
#include "Observer.hpp"

namespace octopus {
    class Observable {
    private:
        std::vector<Observer*> observer_list;


        bool exists(Observer *obs){
            for (size_t i = 0; i < observer_list.size(); i++) {
                if(observer_list[i] == obs)
                    return true;
            }

            return false;
        }

    protected:
        Observable(){

        }

        void notifyObservers(){
            for (size_t i = 0; i < observer_list.size(); i++) {
                observer_list[i]->update();
            }
        }

    public:

        void addObserver(Observer *observer){
            if( ! exists(observer))
                observer_list.push_back(observer);
        }


    };
} /* octopus */

#endif
