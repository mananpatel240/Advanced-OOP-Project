// Name: Manan Patel
// Seneca Student ID: 148603194
// Seneca email: mspatel45@myseneca.ca
// Date of completion: 12-03-2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef LINEMANAGER_H
#define LINEMANAGER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

namespace sdds
{
	class LineManager
	{
		std::vector<Workstation*> activeLine;
		size_t m_cntCustomerOrder;
		Workstation* m_firstStation;
	public:
		LineManager() {};
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		~LineManager() {};
		void linkStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;
	};
}
#endif 