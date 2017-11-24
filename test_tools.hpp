#ifndef BOOST_SERIALIZATION_TEST_TOOLS_HPP
#define BOOST_SERIALIZATION_TEST_TOOLS_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

#define BOOST_FILESYSTEM_VERSION 3
#include <boost/filesystem/operations.hpp> // unique_path

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// test_tools.hpp
//
// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifndef BOOST_NO_EXCEPTION_STD_NAMESPACE
    #include <exception>
#endif
#include <boost/detail/no_exceptions_support.hpp>

#include <boost/core/lightweight_test.hpp>

#define BOOST_CHECK( P ) \
    BOOST_TEST( (P) )
#define BOOST_REQUIRE( P )  \
    BOOST_TEST( (P) )
#define BOOST_CHECK_MESSAGE( P, M )  \
    ((P)? (void)0 : ::boost::detail::error_impl( (M) , __FILE__, __LINE__, BOOST_CURRENT_FUNCTION))
#define BOOST_REQUIRE_MESSAGE( P, M ) \
    BOOST_CHECK_MESSAGE( (P), (M) )
#define BOOST_CHECK_EQUAL( A , B ) \
    BOOST_TEST( (A) == (B) )

namespace boost { namespace detail {
inline void msg_impl(char const * msg, char const * file, int line, char const * function)
{
    std::cerr << file << "(" << line << "): " << msg << " in function '" << function << "'" << std::endl;
}
} } // boost::detail

#define BOOST_WARN_MESSAGE( P, M )  \
    ((P)? (void)0 : ::boost::detail::msg_impl( (M) , __FILE__, __LINE__, BOOST_CURRENT_FUNCTION))
#define BOOST_MESSAGE( M ) \
    BOOST_WARN_MESSAGE( true , (M) )

#define BOOST_CHECKPOINT( M ) \
    BOOST_WARN_MESSAGE( true , (M) )

//#define BOOST_TEST_DONT_PRINT_LOG_VALUE( T ) 

#define BOOST_FAIL( M ) BOOST_REQUIRE_MESSAGE( false, (M) )
#define EXIT_SUCCESS 0

int test_main(int argc, char * argv[]);

#include <boost/serialization/singleton.hpp>

int
main(int argc, char * argv[]){
    boost::serialization::singleton_module::lock();

    int retval = 1;
    BOOST_TRY{
        retval = test_main(argc, argv);
    }
    #ifndef BOOST_NO_EXCEPTION_STD_NAMESPACE
        BOOST_CATCH(const std::exception & e){
            BOOST_ERROR(e.what());
        }
    #endif
    BOOST_CATCH(...){
        BOOST_ERROR("failed with uncaught exception:");
    }
    BOOST_CATCH_END

    boost::serialization::singleton_module::unlock();

    int error_count = boost::report_errors();
    if(error_count > 0)
        retval = error_count;
    return retval;
}

// the following is to ensure that when one of the libraries changes
// BJAM rebuilds and relinks the test.
/*
#include "text_archive.hpp"
#include "text_warchive.hpp"
#include "binary_archive.hpp"
#include "xml_archive.hpp"
#include "xml_warchive.hpp"
*/

/////////////////////////////////////////////
// invoke header for a custom archive test.

/////////////////////////////////////////////
// invoke header for a custom archive test.
#if ! defined(BOOST_ARCHIVE_TEST)
#define BOOST_ARCHIVE_TEST text_archive.hpp
#endif

#include <boost/preprocessor/stringize.hpp>
#include BOOST_PP_STRINGIZE(BOOST_ARCHIVE_TEST)

#ifndef TEST_STREAM_FLAGS
    #define TEST_STREAM_FLAGS (std::ios_base::openmode)0
#endif

#ifndef TEST_ARCHIVE_FLAGS
    #define TEST_ARCHIVE_FLAGS 0
#endif

#ifndef TEST_DIRECTORY
#define TEST_DIRECTORY
#else
#define __x__ TEST_DIRECTORY
#undef TEST_DIRECTORY
#define TEST_DIRECTORY BOOST_PP_STRINGIZE(__x__)
#endif

#endif // BOOST_SERIALIZATION_TEST_TOOLS_HPP
