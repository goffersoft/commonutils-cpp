#include <boost/lambda/lambda.hpp>
#include <boost/log/trivial.hpp>
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

   BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
   BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
   BOOST_LOG_TRIVIAL(info) << "An informational severity message";
   BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
   BOOST_LOG_TRIVIAL(error) << "An error severity message";
   BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";

    return 0;
}
