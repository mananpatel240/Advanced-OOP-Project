// Name: Manan Patel
// Seneca Student ID: 148603194
// Seneca email: mspatel45@myseneca.ca
// Date of completion: 12-03-2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <iomanip>
#include "Workstation.h"
using namespace std;

deque<sdds::CustomerOrder> pending{};
deque<sdds::CustomerOrder> completed{};
deque<sdds::CustomerOrder> incomplete{};

namespace sdds 
{
	Workstation::Workstation(const string s) : Station(s)
	{
		m_pNextStation = nullptr;
	}

	void Workstation::fill(ostream& os)
	{
		if (!m_orders.empty())
		{
			m_orders.front().fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder()
	{
		if (m_orders.size() > 0)
		{
			if ((getQuantity() == 0) || (m_orders.front().isItemFilled(getItemName())))
			{
				if (m_pNextStation)
				{
					*m_pNextStation += move(m_orders.front());
				}
				else
				{
					if (m_orders.front().isFilled())
					{
						completed.push_back(move(m_orders.front()));
					}
					else
					{
						incomplete.push_back(move(m_orders.front()));
					}
				}
				m_orders.pop_front();
				return true;
			}
		}
		return false;
	}
	
	void Workstation::setNextStation(Workstation* station = nullptr)
	{
		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}

	void Workstation::display(ostream& os) const
	{
		os << getItemName() << " --> ";
		if (m_pNextStation)
		{
			os << m_pNextStation->getItemName() << endl;
		}
		else
		{
			os << "End of Line" << endl;
		}
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(move(newOrder));
		return *this;
	}
}
