/*
 * main.cc
 *
 *  Created on: 31.08.2022
 *      Author: martin
 */
#include <format.h>
#include <BigInt.h>
#include <arg.h>
#include <OutDebug.h>
#include <colored_output.h>

#ifdef ENABLE_NLS
#   include <libintl.h>
#   include <locale.h>
#endif

#ifdef ENABLE_NLS
#   define _(STRING) gettext(STRING)
#else
#   define _(STRING) (STRING)
#endif


using namespace Tools;
using namespace BigNum2;

static void usage( const std::string & prog )
{
    std::cerr << _("usage: ")
              << prog << " [-debug]\n";
}


int main(int argc,char *argv[])
{
#ifdef ENABLE_NLS
    /* Setting the i18n environment */
    setlocale (LC_ALL, "");
#if defined WIN32 || defined _WIN32
    bindtextdomain ("bignum2", CppDir::exec_path.c_str() );
    bind_textdomain_codeset("bignum2", "utf-8");
#else
    bindtextdomain ("bignum2", LOCALEDIR );
#endif
    textdomain ("bignum2");
#endif

    ColoredOutput colored_output;

    Arg::Arg arg( argc, argv );

    arg.addPrefix( "-" );
    arg.addPrefix( "--" );

    Arg::OptionChain oc_info;
    arg.addChainR( &oc_info );
    oc_info.setMinMatch( 1 );
    oc_info.setContinueOnMatch( false );
    oc_info.setContinueOnFail( true );

    Arg::FlagOption o_help( "h" );
    o_help.addName( "help" );
    o_help.setDescription( _("Show this page") );
    oc_info.addOptionR( &o_help );

    Arg::FlagOption o_version( "v" );
    o_version.addName( "version" );
    o_version.setDescription( _("Show bignum2 version number") );
    oc_info.addOptionR( &o_version );

    Arg::FlagOption o_debug("debug");
    o_debug.setDescription( _("print debugging messages") );
    o_debug.setRequired(false);
    arg.addOptionR( &o_debug );

    const unsigned int console_width = 80;

    if( !arg.parse() )
    {
        if( o_version.getState() )
        {
            std::cout << format(_("%s version %s\n"), argv[0], VERSION);
            return 0;
        } else {
            usage(argv[0]);
            std::cout << arg.getHelp(5,20,30, console_width ) << std::endl;
            return 1;
        }
    }

    if( o_help.getState() )
    {
        // usage(argv[0]);
        std::cout << arg.getHelp(5,20,30, console_width ) << std::endl;
        return 0;
    }

    if( o_debug.getState() )
    {
        Tools::x_debug = new OutDebug();
    }

    BigInt a, b;

    a = "1";
    b = "2";

    std::cout << a + b << std::endl;

    return 0;
}

