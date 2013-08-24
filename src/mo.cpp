/*
 * moFileReader - A simple .mo-File-Reader
 * Copyright (C) 2009 Domenico Gentner (scorcher24@gmail.com)
 * All rights reserved.                          
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *
 *   3. The names of its contributors may not be used to endorse or promote 
 *      products derived from this software without specific prior written 
 *      permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "../include/moFileReader.h"
#include <iostream>
#include <cstdlib>

#if defined(_MSC_VER) && defined(_DEBUG)
#   include <crtdbg.h>   
#endif /* _MSC_VER */

using namespace moFileLib;

void Usage(const std::string appname)
{
    std::cout << "Usage: "                                                                  << std::endl;
    std::cout << appname << " <option> <params>"                                           << std::endl;
    std::cout << "Possible Options: "                                                       << std::endl;
    std::cout << "--lookup <mofile> <msgid>        - Outputs the given ID from the file."   << std::endl;    
    std::cout << "--export <mofile> [<exportfile>] - Exports the whole .mo-file as HTML."   << std::endl;        
    std::cout << "--help,-h,-?  - Prints this screen"                                       << std::endl;
    std::cout << "--license     - Prints the license of this program. "                     << std::endl;
    std::cout                                                                               << std::endl;
    std::cout << "Example: " << appname << " --export my18n.mo exportfile.html"            << std::endl;
    std::cout << "Example: " << appname << " --lookup my18n.mo lookupstring"               << std::endl;
    std::cout << "Please encapsualte strings or pathes with spaces in \". Thank you."       << std::endl;
    std::cout << "Parameters in Brackets [] are optional."                                  << std::endl;
}

void PrintLicense()
{
    std::cout << "\
    moFileReader - A simple .mo-File-Reader\n\
    Copyright (C) 2009 Domenico Gentner (scorcher24@gmail.com)\n\
    All rights reserved.                          \n\
    \n\
    Redistribution and use in source and binary forms, with or without\n\
    modification, are permitted provided that the following conditions\n\
    are met:\n\
    \n\
    1. Redistributions of source code must retain the above copyright\n\
     notice, this list of conditions and the following disclaimer.\n\
    2. Redistributions in binary form must reproduce the above copyright\n\
     notice, this list of conditions and the following disclaimer in the\n\
     documentation and/or other materials provided with the distribution.\n\
    \n\
    3. The names of its contributors may not be used to endorse or promote \n\
     products derived from this software without specific prior written \n\
     permission.\n\
    \n\
    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS\n\
    \"AS IS\" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT\n\
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR\n\
    A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR\n\
    CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,\n\
    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,\n\
    PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR\n\
    PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF\n\
    LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING\n\
    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS\n\
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.\n\
    " << std::endl;
}

std::string GetAppName(const char* raw)
{
    std::string r(raw);
    int first = r.find_last_of(moPATHSEP) + 1;
    r = r.substr(first, r.length() - first);
    return r;
}

#if defined(_CONSOLE)

int main( int, char** argv )
{
#if defined (_DEBUG) && defined(_MSC_VER)
            long flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
            flag |= _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF;
            _CrtSetDbgFlag(flag);
#endif /* _MSC_VER && _DEBUG */    

    std::string appname = GetAppName(argv[0]);

    if ( argv[1] == NULL )
    {
        Usage(appname);
        return EXIT_FAILURE;
    }
    if ( std::string(argv[1]) == "--help" || std::string(argv[1]) == "-?" || std::string(argv[1]) == "-h" )
    {
        Usage(appname);
        return EXIT_SUCCESS;
    }
    else if ( std::string(argv[1]) == "-v" || std::string(argv[1]) == "--version" )
    {
        std::cout << "This program is part of the moReaderSDK written by Domenico Gentner."    << std::endl;
        std::cout << "Released under the Terms of the MIT-License." << std::endl;
        std::cout << "Type " << appname << " --license to view it." << std::endl;
        std::cout << "Get all News and Updates from http://mofilereader.googlecode.com." << std::endl;
        return EXIT_SUCCESS;
    }
    else if ( std::string(argv[1]) == "--license" )
    {
        PrintLicense();
        return EXIT_SUCCESS;
    }
    else if ( std::string(argv[1]) == "--export" )
    {
        std::string outfile;
        if ( argv[2] == NULL )
        {
            Usage(appname);
            return EXIT_FAILURE;
        }
        if ( argv[3] )
        {
            outfile = argv[3];
        }
        
        moFileReader::eErrorCode r = moFileReader::ExportAsHTML(argv[2], outfile);
        if (  r == moFileReader::EC_SUCCESS )
        {
            std::cout << "Dumped " << argv[2] << " successfully to " << outfile << std::endl;
            return EXIT_SUCCESS;
        }
        else if ( r == moFileReader::EC_TABLEEMPTY )
        {
            std::cout << "Could not dump " << argv[2] << " to " << outfile << " because the lookup-table is empty!" << std::endl;
            return EXIT_FAILURE;
        }
        else if ( r == moFileReader::EC_FILENOTFOUND )
        {
            std::cout << "Could not dump " << argv[2] << " to " << outfile << " because I could not open a file!" << std::endl;
            return EXIT_FAILURE;            
        }
        else if ( r == moFileReader::EC_FILEINVALID )
        {
            std::cout << "Could not dump " << argv[2] << " to " << outfile << " because the .mo-File was invalid!" << std::endl;
            return EXIT_FAILURE;
        }
        else
        {
            std::cout << "Could not dump " << argv[2] << " to " << outfile << ". An unknown error occured." << std::endl;
            return EXIT_FAILURE;
        }
    }
    else if ( std::string(argv[1]) == "--lookup")
    {
        if ( argv[2] == NULL || argv[3] == NULL )
        {
            Usage(appname);
            if (argv[3] == NULL)
                std::cout << "HINT: If you want to call an empty msgid, please use \"\" as parameter 3." << std::endl;
            return EXIT_FAILURE;
        }
        if ( moReadMoFile(argv[2]) != moFileReader::EC_SUCCESS )
        {
            std::cout << "Error while loading the file: " << moFileGetErrorDescription() << std::endl;
            return -1;
        }
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "Lookup: " <<   argv[3]                     << std::endl;
        std::cout << "Result: " << _(argv[3])                    << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        return EXIT_SUCCESS;
    }
    else
    {
        Usage(appname);
        std::cout << std::endl;
        std::cout << "HINT: Missing --export or --lookup!" << std::endl;
        return EXIT_FAILURE;
    }
}

#elif defined(_USRDLL) && defined(WIN32)

#include <windows.h>
extern "C"
int WINAPI DllMain( DWORD reason, LPVOID)
{
    switch (reason)
    {
        case DLL_THREAD_ATTACH:
        case DLL_PROCESS_ATTACH:
            {
#if defined (_DEBUG) && defined(_MSC_VER)
            long flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
            flag |= _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF;
            _CrtSetDbgFlag(flag);
#endif /* _MSC_VER && _DEBUG */
            break;
            }
        default:
            return FALSE;
    };

    return TRUE;
}

#endif /* Compilation-Mode */

