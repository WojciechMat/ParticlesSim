#include "event.h"
#include <ostream>

std::ostream& operator<<(std::ostream& os, const Event& e) {
    os << "Event(time=" << e.time;
    if (e.p1) {
        os << ", p1=" << *e.p1;
    } else {
        os << ", p1=nullptr";
    }
    if (e.p2) {
        os << ", p2=" << *e.p2;
    } else {
        os << ", p2=nullptr";
    }
    os << ", countA=" << e.countA
       << ", countB=" << e.countB << ")";
    return os;
}
