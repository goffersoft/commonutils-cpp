#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>

int boost_test_main(int argc, char **argv)
{
    using namespace boost::lambda;
    typedef std::istream_iterator<int> in;
    
    std::cout<<"Enter Numbers (non-integeer to quit)"<<std::endl;
 
    std::for_each(
        in(std::cin), in(),
        std::cout << (_1 * 3) << " ");

    return 0;
}
