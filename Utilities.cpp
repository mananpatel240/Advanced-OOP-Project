// Name: Manan Patel
// Seneca Student ID: 148603194
// Seneca email: mspatel45@myseneca.ca
// Date of completion: 11-19-2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <string> 
#include "Utilities.h"
using namespace std;

namespace sdds
{
	char Utilities::m_delimiter = ' ';

	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}

	string Utilities::extractToken(const string& str, size_t& next_pos, bool& more)
	{
		string s = str.substr(next_pos);
		size_t pos = s.find(m_delimiter);
		
		if (pos != string::npos)
		{
			s = s.substr(0, pos);
			next_pos += (pos + 1);
			if (s == "")
			{
				more = false;
				throw "There is no token left.";
			}
			more = true;
		}
		else
		{
			more = false;
		}

		if (s.length() > m_widthField)
		{
			setFieldWidth(s.length());
		}
		return s;
	}

	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}
}