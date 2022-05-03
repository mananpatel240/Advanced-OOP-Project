// Name: Manan Patel
// Seneca Student ID: 148603194
// Seneca email: mspatel45@myseneca.ca
// Date of completion: 12-03-2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef WORKSTATION_H
#define WORKSTATION_H

#include <deque>
#include "CustomerOrder.h"
#include "Station.h"

extern std::deque<sdds::CustomerOrder> pending;
extern std::deque<sdds::CustomerOrder> completed;
extern std::deque<sdds::CustomerOrder> incomplete;

namespace sdds 
{
	class Workstation : public Station 
	{
		std::deque<CustomerOrder> m_orders{};
		Workstation* m_pNextStation;
	public:
		Workstation() {};
		Workstation(const std::string s);
		~Workstation() {};
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);
	};
}
#endif 