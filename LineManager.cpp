// Name: Manan Patel
// Seneca Student ID: 148603194
// Seneca email: mspatel45@myseneca.ca
// Date of completion: 12-03-2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Workstation.h"
#include "LineManager.h"
#include "Utilities.h"

using namespace std;

namespace sdds
{
	LineManager::LineManager(const string& file, const vector<Workstation*>& stations)
	{
		try
		{
			m_cntCustomerOrder = pending.size();
			ifstream is(file);
			string s;
			Utilities util;

			while (getline(is, s))
			{
				string first, next;
				size_t next_pos = 0;
				bool more;
				first = util.extractToken(s, next_pos, more);

				if (more)
				{
					next = util.extractToken(s, next_pos, more);
				}

				for_each(stations.begin(), stations.end(), [&](Workstation* ws)
					{
						if (ws->getItemName() == first)
						{
							for_each(stations.begin(), stations.end(), [&](Workstation* nextws)
								{
									if (nextws->getItemName() == next)
									{
										ws->setNextStation(nextws);
									}
								});
							activeLine.push_back(ws);
						}
					});

				m_firstStation = activeLine.front();
			}
		}
		catch (...)
		{
			throw "Error in LineManager Constructor";
		}
	}

	void LineManager::linkStations()
	{
		vector<Workstation*> v{ m_firstStation };
		size_t i = 0;

		for_each(activeLine.begin(), activeLine.end(), [&](Workstation* ws)
			{
				for_each(activeLine.begin(), activeLine.end(), [&](Workstation* nextws)
					{
						if (v[i]->getNextStation())
						{
							if (v[i]->getNextStation()->getItemName() == nextws->getItemName())
							{
								v.push_back(nextws);
								++i;
							}
						}
					});
			});

		activeLine = v;
	}

	bool LineManager::run(ostream& ostr)
	{
		static size_t n = 1;
		ostr << "Line Manager Iteration: " << n << endl;
		size_t before = completed.size() + incomplete.size();

		if (!pending.empty())
		{
			*m_firstStation += move(pending.front());
			pending.pop_front();
		}

		for_each(activeLine.begin(), activeLine.end(), [&](Workstation* ws)
			{
				ws->fill(ostr);
			});

		for_each(activeLine.begin(), activeLine.end(), [&](Workstation* ws)
			{
				ws->attemptToMoveOrder();
			});

		size_t after = completed.size() + incomplete.size();
		size_t diff = after - before;
		m_cntCustomerOrder = m_cntCustomerOrder - diff;
		n++;

		if (m_cntCustomerOrder <= 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void LineManager::display(ostream& ostr) const
	{
		for_each(activeLine.begin(), activeLine.end(), [&ostr](Workstation* ws) 
			{ 
				ws->display(ostr); 
			});
	}
}