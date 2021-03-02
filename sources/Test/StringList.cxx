#include <iostream>
#include "Support/StringList.hxx"

int32_t main()
{
    const std::string split1 = "one, two, three, four, 5, 6, 7, 8, nine, ten";
    const std::string sep1 = ", ";
    Mud::Support::String::List slist;

    slist.split(split1, sep1);
    std::cout << "string to split (', '): '" << split1 << "' (size: " << slist.size() << ")\n"
              << "result: " << slist.at(0);
    for (size_t i = 1; i < slist.size(); ++i)
        std::cout << "_" << slist.at(i);
    std::cout << "\nrejoin (':::'): '" << slist.join(":::") << "'" << std::endl;

    return 0;
}
