// Name: Manan Patel
// Seneca Student ID: 148603194
// Seneca email: mspatel45@myseneca.ca
// Date of completion: 11-27-2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <iomanip>
#include "CustomerOrder.h"
#include "Station.h"
#include "Utilities.h"
using namespace std;

namespace sdds
{
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder()
	{
		m_name = "";
		m_product = "";
		m_cntItem = 0;
		m_lstItem = nullptr;
	}

	CustomerOrder::CustomerOrder(const string& s)
	{
		Utilities u;
		size_t next_pos = 0;
		bool more = true;

		m_name = u.extractToken(s, next_pos, more);
		m_product = u.extractToken(s, next_pos, more);
		m_cntItem = 0;
		size_t pos = next_pos;

		do
		{
			m_cntItem++;
			u.extractToken(s, next_pos, more);
		} while (more);

		m_lstItem = new Item * [m_cntItem];
		more = true;
		for (size_t i = 0; i < m_cntItem; ++i)
		{
			m_lstItem[i] = new Item(u.extractToken(s, pos, more));
		}

		if (m_widthField < u.getFieldWidth())
		{
			m_widthField = u.getFieldWidth();
		}
	}

	CustomerOrder::CustomerOrder(CustomerOrder&)
	{
		throw "No copy operations allowed";
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& c) noexcept
	{
		*this = move(c);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& c) noexcept
	{
		if (m_lstItem)
		{
			for (size_t i = 0; i < m_cntItem; ++i)
			{
				delete m_lstItem[i];
			}
		}
		delete[] m_lstItem;

		m_name = c.m_name;
		m_product = c.m_product;
		m_cntItem = c.m_cntItem;
		m_lstItem = c.m_lstItem;

		c.m_lstItem = nullptr;
		return *this;
	}

	CustomerOrder::~CustomerOrder()
	{
		if (m_lstItem)
		{
			for (size_t i = 0; i < m_cntItem; ++i)
			{
				delete m_lstItem[i];
			}
		}
		delete[] m_lstItem;
		m_lstItem = nullptr;
	}

	bool CustomerOrder::isFilled() const
	{
		for (size_t i = 0; i < m_cntItem; ++i)
		{
			if (!m_lstItem[i]->m_isFilled)
			{
				return false;
			}
		}
		return true;
	}

	bool CustomerOrder::isItemFilled(const string& itemName) const
	{
		for (size_t i = 0; i < m_cntItem; ++i)
		{
			if (m_lstItem[i]->m_itemName == itemName)
			{
				if (!m_lstItem[i]->m_isFilled)
				{
					return false;
				}
			}
		}
		return true;
	}

	void CustomerOrder::fillItem(Station& station, ostream& os)
	{
		for (size_t i = 0; i < m_cntItem; ++i)
		{
			if (m_lstItem[i]->m_itemName == station.getItemName())
			{
				if (station.getQuantity() > 0)
				{
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;

					os << setw(m_widthField - 19) << right << "Filled ";
					os << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
				}
				else
				{
					os << setw(19) << right << "Unable to fill ";
					os << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
				}
			}
		}
	}

	void CustomerOrder::display(ostream& os) const
	{
		os << m_name << " - " << m_product << endl;
		for (size_t i = 0; i < m_cntItem; ++i)
		{
			os << "[" << setw(6) << setfill('0') << right << m_lstItem[i]->m_serialNumber << setfill(' ') << "] ";
			os << setw(m_widthField) << left << m_lstItem[i]->m_itemName << " - ";
			if (m_lstItem[i]->m_isFilled)
			{
				os << "FILLED" << endl;
			}
			else
			{
				os << "TO BE FILLED" << endl;
			}
		}
	}
}