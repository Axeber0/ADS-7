// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TRAIN_H_
#define INCLUDE_TRAIN_H_

class Train {
    struct Car {
        bool light;
        Car* next;
        Car* prev;
        explicit Car(bool b) : light(b), next(nullptr), prev(nullptr) {}
    };
    Car* entry;
    int operations;
    void go() {
        entry = entry->next;
        operations++;
    }
    void back() {
        entry = entry->prev;
        operations++;
    }
    void toggleLight() {
        entry->light = !entry->light;
    }

 public:
    Train() : entry(nullptr), operations(0) {}
    ~Train() {
        if (!entry) return;
        Car* traveler = entry->next;
        while (traveler != entry) {
            Car* next = traveler->next;
            delete traveler;
            traveler = next;
        }
        delete entry;
    }
    void addCar(bool lightState) {
        Car* newCar = new Car{lightState};
        if (!entry) {
            entry = newCar;
            entry->next = entry;
            entry->prev = entry;
      } else {
            Car* last = entry->prev;
            newCar->prev = last;
            last->next = newCar;
            entry->prev = newCar;
            newCar->next = entry;
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
                cur = cur->next;
                operations++;
                step++;
                if (cur->light || cur == entry) break;
            }
            if (cur == entry && !cur->light) break;
            if (cur->light) cur->light = false;
            for (int i = 0; i < step; i++) {
                cur = cur->prev;
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
        return operations;
    }
    void resetCounters() {
        operations = 0;
    }
};
#endif  // INCLUDE_TRAIN_H_
