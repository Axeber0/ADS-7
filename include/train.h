// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TRAIN_H_
#define INCLUDE_TRAIN_H_

class Train {
    struct Car {
        bool light;
        Car* forward;
        Car* backward;
       explicit Car(bool b) : light(b), forward(nullptr), backward(nullptr) {}
    };
    Car* entry;
    int operations;
    void go() {
        entry = entry->forward;
        operations++;
    }
    void back() {
        entry = entry->backward;
        operations++;
    }
    void toggleLight() {
        entry->light = !entry->light;
    }
 public:
    Train() : entry(nullptr), operations(0) {}
    ~Train() {
        if (!entry) return;
        Car* traveler = entry->forward;
        while (traveler != entry) {
            Car* next = traveler->forward;
            delete traveler;
            traveler = next;
        }
        delete entry;
    }
    void addCar(bool lightState) {
        Car* newCar = new Car{lightState};
        if (!entry) {
            entry = newCar;
            entry->forward = entry;
            entry->backward = entry;
      } else {
            Car* last = entry->backward;
            newCar->backward = last;
            last->forward = newCar;
            entry->backward = newCar;
            newCar->forward = entry;
      }
    }
    int getLength() {
        operations = 0;
        bool allDark = true;
        Car* start = entry;
        do {
            if (start->light) {
                allDark = false;
                break;
            }
            start = start->forward;
            operations++;
        } while (start != entry);
        if (allDark) {
            int size = 1;
            while (start->forward != entry) {
                start = start->forward;
                operations++;
                size++;
            }
            return size;
        }
        entry->light = false;

        int counter = 0;
        while (true) {
            for (int i = 0; i <= counter; i++) {
                go();
            }
            if (entry->light) {
                toggleLight();
                counter = 0;
            } else {
                counter++;
            }
            if (counter > operations) {
                break;
            }
        }
        return operations;
    }
    int getOpCount() const {
        return operations+1;
    }
    void resetCounters() {
        operations = 0;
    }
};
#endif  // INCLUDE_TRAIN_H_
