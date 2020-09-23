#include <iostream>

#include "external_sort.hpp"
#include "external_sort_custom.hpp"

int main()
{
	// set split and merge parameters
	external_sort::SplitParams sp;
	external_sort::MergeParams mp;
	sp.mem.size = 10000;
	sp.mem.unit = external_sort::MB;
	sp.mem.blocks = 30;
	mp.mem = sp.mem;
	sp.spl.ifile = "/s/Sorting/input";
	mp.mrg.ofile = "/t/Sorting/output";

	using ValueType = CustomRecord;

	// run external sort
	external_sort::sort<ValueType>(sp, mp);

	if (sp.err.none && mp.err.none)
	{
		std::cout << "File sorted successfully!" << std::endl;
	}
	else
	{
		std::cout << "External sort failed!" << std::endl;
		if (sp.err)
		{
			std::cout << "Split failed: " << sp.err.msg() << std::endl;
		}
		else
		{
			std::cout << "Merge failed: " << mp.err.msg() << std::endl;
		}
	}
}
