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
        if (!entry) return 0;
        Car* cur = entry;
        if (!cur->light) {
            cur->light = true;
        }
        int len = 0;
        while (true) {
            int step = 0;
            while (true) {
                cur = cur->forward;
                operations++;
                step++;
                if (cur->light || cur == entry) break;
            }
            if (cur == entry && !cur->light) break;
            if (cur->light) cur->light = false;
            for (int i = 0; i < step; i++) {
                cur = cur->backward;
                operations++;
            }
            if (!cur->light) {
                len = step;
                break;
            }
        }
        return len;
    }
    int getOpCount() const {
        return operations+1;
    }
    void resetCounters() {
        operations = 0;
    }
};
#endif  // INCLUDE_TRAIN_H_
