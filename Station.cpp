// Name: Manan Patel
// Seneca Student ID: 148603194
// Seneca email: mspatel45@myseneca.ca
// Date of completion: 11-19-2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"
using namespace std;

namespace sdds
{
	size_t Station::m_widthField = 0;
	int Station::id_generator = 0;

	Station::Station()
	{
		id = 0;
		item = nullptr;
		desc = nullptr;
		serial = 0;
		qty = 0;
		m_widthField = 0;
		id_generator = 0;
	}

	Station::Station(const string& str)
	{
		Utilities util;
		size_t pos = 0;
		bool flag = true;
		
		item = util.extractToken(str, pos, flag);
		serial = stoi(util.extractToken(str, pos, flag));
		qty = stoi(util.extractToken(str, pos, flag));
		
		if (m_widthField < util.getFieldWidth())
		{
			m_widthField = util.getFieldWidth();
		}
		
		desc = util.extractToken(str, pos, flag);
		
		id_generator++;
		id = id_generator;
	}

	const string& Station::getItemName() const
	{
		return item;
	}

	size_t Station::getNextSerialNumber()
	{
		return serial++;
	}

	size_t Station::getQuantity() const
	{
		return qty;
	}

	void Station::updateQuantity()
	{
		if (qty > 0)
		{
			qty--;
		}
	}

	void Station::display(ostream& os, bool full) const
	{
		os << "[" << right << setw(3) << setfill('0') << id << "] ";
		os << "Item: " << left << setw(m_widthField) << setfill(' ') << item;
		os << " [" << right << setw(6) << setfill('0') << serial << "]";
		if (full == true)
		{
			os << " Quantity: " << left << setw(m_widthField) << setfill(' ') << qty;
			os << " Description: " << desc;
		}
		os << endl;
	}
}