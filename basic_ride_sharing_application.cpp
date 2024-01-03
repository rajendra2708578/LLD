#include<bits/stdc++.h>
using namespace std;

enum RideStatus{IDLE,CREATED,WITHDRAWN,COMPLETED};
// Ride is type of instruction working class.
class Ride{
    int id;
    int origin,dest;
    int seats;
    RideStatus rideStatus;
public:
    static const int AMT_PER_KM=20;
    Ride();
    int calculateFare(bool);
    void setDest(int dest);
    int getId() const;
    void setId(int id);
    void setOrigin(int origin);
    RideStatus getRideStatus() const;
    void setRideStatus(RideStatus rideStatus);
    void setSeats(int seats);

};
class Person{
public:
    string name;
};
// Rider class is type of person 
class Driver:private Person{
public:
    Driver(string);
};
// Rider class is type of person 
class Rider:private Person{
    vector<Ride>completedRides;
    Ride currentRide;
public:
    Rider(string);
    void createRide(int,int,int,int);
    void updateRide(int,int,int,int);
    void withdrawRide(int);
    int closeRide();
};
Ride::Ride()
{
    id=origin=dest=seats=0;
    rideStatus=RideStatus::IDLE;
}
Driver::Driver(string name)
{
    this->name=name;
}
int Ride::calculateFare(bool isPriorityRider)
{
    int dist=dest-origin;
    if(seats<2)
    {
        return dist*AMT_PER_KM*(isPriorityRider?0.75:1);
    }
    return dist*seats*AMT_PER_KM*(isPriorityRider?0.5:0.75);
}
void Ride::setDest(int dest)
{
    this->dest=dest;
}
int Ride::getId() const{
    return id;
}
void Ride::setId(int id){
    this->id=id;
}
void Ride::setOrigin(int origin)
{
    this->origin=origin;
}
RideStatus Ride::getRideStatus() const{
    return rideStatus;
}
void Ride::setRideStatus(RideStatus rideStatus){
    this->rideStatus=rideStatus;
}
void Ride::setSeats(int seats){
    this->seats=seats;
}
Rider::Rider(string name) 
{
    this->name=name;
}
void Rider::createRide(int id,int origin,int dest,int seats)
{
    if(origin>=dest)
    {
        cout<<"Wrong values of origin and Destination provided. Can't Create";
        return;
    }
    currentRide.setId(id);
    currentRide.setOrigin(origin);
    currentRide.setDest(dest);
    currentRide.setSeats(seats);
    currentRide.setRideStatus(RideStatus::CREATED);
}
void Rider::updateRide(int id,int origin,int dest,int seats)
{
    if(currentRide.getRideStatus()==RideStatus::WITHDRAWN)
    {
        cout<<"Can't update ride.Ride was withdraw\n";
        return;
    }
    if(currentRide.getRideStatus()==RideStatus::COMPLETED)
    {
        cout<<"Can't update ride.Ride already complete\n";
        return;
    }
    createRide(id,origin,dest,seats);

}
void Rider::withdrawRide(int id)
{
    if(currentRide.getId()!=id)
    {
        cout<<"Wrong ride Id as input.Can't withdraw curent ride\n";
        return;
    }
    if(currentRide.getRideStatus()!=RideStatus::CREATED)
    {
        cout<<"Ride wasn't in progress.Can't widthdraw ";
        return;
    }
    currentRide.setRideStatus(RideStatus::WITHDRAWN);
}
int Rider::closeRide()
{
    if(currentRide.getRideStatus()!=RideStatus::CREATED)
    {
        cout<<"Ride wasn't in progress. Can't close ride\n";
        return 0;
    }
    currentRide.setRideStatus(RideStatus::COMPLETED);
    completedRides.push_back(currentRide);
    return currentRide.calculateFare(completedRides.size()>=10);

}
int main()
{
    Rider rider("lucifer");
    Driver driver("Amendiel");

    rider.createRide(1,50,60,1);
    cout<<rider.closeRide()<<endl;
    rider.updateRide(1,50,60,2);
    cout<<rider.closeRide()<<endl;
    cout<<"#########################################################"<<endl;
    rider.createRide(1,50,60,1);
    rider.withdrawRide(1);
    rider.updateRide(1,50,60,2);
    cout<<rider.closeRide()<<endl;

    cout<<"####################################################### "<<endl;
    rider.createRide(1,50,60,1);
    rider.updateRide(1,50,60,2);
    cout<<rider.closeRide()<<endl;
    return 0;
    
    return 0;
}