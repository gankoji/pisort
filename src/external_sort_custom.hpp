#ifndef EXTERNAL_SORT_CUSTOM_HPP
#define EXTERNAL_SORT_CUSTOM_HPP

/// ----------------------------------------------------------------------------
/// custom type to run external sort for

#include <cstring>

struct CustomRecord
{
	char key[10];
	char body[90];
};

struct CustomRecordComparator
{
	bool operator()(const CustomRecord& x, const CustomRecord& y) const
	{
		if (strncmp(x.key, y.key, 10) < 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

struct CustomRecord2Str
{
	std::string operator()(const CustomRecord& x)
	{
		return std::string();
	}
};

// struct CustomRecordGenerator
// {
//     CustomRecord operator()()
//     {
//         CustomRecord x;
//         std::ostringstream name;
//         std::ostringstream text;
//         x.id = rand();
//         cnt++;
//         name << boost::format("Name %03d") % cnt;
//         memcpy(x.name, name.str().c_str(), sizeof(x.name));
//         x.name[sizeof(x.name) - 1] = '\0';
//         text << boost::format("Text %03d") % cnt;
//         memcpy(x.text, text.str().c_str(), sizeof(x.text));
//         x.text[sizeof(x.text) - 1] = '\0';
//         return x;
//     }
//     size_t cnt = 0;
// };

namespace external_sort
{
template <>
struct ValueTraits<CustomRecord>
{
	using Comparator = CustomRecordComparator;
	//using Generator = CustomRecordGenerator;
	using Value2Str = CustomRecord2Str;

	// .. or default generator with all random bytes:
	using Generator = DefaultValueGenerator<CustomRecord>;
};
}

#endif
