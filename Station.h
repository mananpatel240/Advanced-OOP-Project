// Name: Manan Patel
// Seneca Student ID: 148603194
// Seneca email: mspatel45@myseneca.ca
// Date of completion: 11-19-2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef STATION_H
#define STATION_H
#include <string>

namespace sdds
{
	class Station
	{
		int id = 0;
		std::string item;
		std::string desc = "";
		unsigned int serial = 0;
		unsigned int qty = 0;
		static size_t m_widthField;
		static int id_generator;
	public:
		Station();
		Station(const std::string&);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}
#endif