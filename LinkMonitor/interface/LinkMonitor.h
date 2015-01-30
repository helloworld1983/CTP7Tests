#ifndef LINKMONITOR_h
#define LINKMONITOR_h

#include <vector>
#include <stdint.h>

// a simple class
struct LinkMonitor
{
	explicit LinkMonitor(uint32_t v):value_(v) { }
	LinkMonitor():value_(0) { }
	uint32_t value_;
        uint32_t raw() const { return value_; }


};

// this is our new product, it is simply a 
// collection of SampleProd held in an std::vector
//typedef std::vector<LinkMonitor> LinkMonitorCollection;
typedef std::vector<LinkMonitor> LinkMonitorCollection;

#endif
