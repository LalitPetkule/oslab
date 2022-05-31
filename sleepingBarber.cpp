#include<iostream>
using namespace std;

void delay() {
    for (int i=0; i<100000; i++){
        for (int j=0; j<10000; j++) {}
    }
}

int customerArrival(int waiting, int chairs) {
    delay();
    if (waiting < chairs){
        cout << "Customer Arrived to barber shop.." << endl;
        waiting += 1;
        cout << "Customer is waiting on the chair for barber.." << endl;
    } else {
        cout << "No chairs available to sit.." << endl;
        cout << "Customer left.. " << endl;
    }

    cout << endl;
    return waiting;
}

int main(){
    int chairs;
    int waiting;

    bool isBarberSleeping = true;

    cout << "Enter number of chairs present in barber shop: ";
    cin >> chairs;

    cout << "Enter number of currently waiting customers in barber shop: ";
    cin >> waiting;

    cout << endl;

    while (true) {
        int hasCustomerArrived;
        cout << "Has new Customer Arrived? [0/1]: ";
        cin >> hasCustomerArrived;
        cout << endl;

        if (hasCustomerArrived == 1) {
            waiting = customerArrival(waiting, chairs);
        }

        if (waiting < 0) {
            delay();
            cout << "No customer is waiting for barber.." << endl;
            cout << "Barber is leaving.." << endl;
            break;
        }

        else if (waiting == 0) {
            delay();
            cout << "No customer is waiting.." << endl;
            isBarberSleeping = true;
            cout << "Barber Slept.." << endl;
            cout << endl;
        }

        else if (isBarberSleeping) {
            delay();
            cout << "Waking up barber.." << endl;
            isBarberSleeping = false;
        }

        if (!isBarberSleeping && waiting > 0) {
            delay();
            cout << "Customer is having his haircut.." << endl;
            delay();
            cout << "Haircut Finished.." << endl;
            cout << "Barber is Idle" << endl;

            cout << endl;
        }

        waiting--;
    }

	return 0;
}
