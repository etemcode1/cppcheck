/*
 * Cppcheck - A tool for static C/C++ code analysis
 * Copyright (C) 2007-2012 Daniel Marjamäki and Cppcheck team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "testsuite.h"
#include "cmdlineparser.h"
#include "settings.h"
#include "redirect.h"

class TestCmdlineParser : public TestFixture {
public:
    TestCmdlineParser() : TestFixture("TestCmdlineParser")
    { }

private:

    void run() {
        TEST_CASE(nooptions);
        TEST_CASE(helpshort);
        TEST_CASE(helplong);
        TEST_CASE(showversion);
        TEST_CASE(onefile);
        TEST_CASE(onepath);
        TEST_CASE(optionwithoutfile);
        TEST_CASE(verboseshort);
        TEST_CASE(verboselong);
        TEST_CASE(debug);
        TEST_CASE(debugwarnings);
        TEST_CASE(forceshort);
        TEST_CASE(forcelong);
        TEST_CASE(relativePaths);
        TEST_CASE(quietshort);
        TEST_CASE(quietlong);
        TEST_CASE(defines_noarg);
        TEST_CASE(defines_noarg2);
        TEST_CASE(defines_noarg3);
        TEST_CASE(defines);
        TEST_CASE(defines2);
        TEST_CASE(defines3);
        TEST_CASE(includesnopath);
        TEST_CASE(includes);
        TEST_CASE(includesslash);
        TEST_CASE(includesbackslash);
        TEST_CASE(includesnospace);
        TEST_CASE(includes2);
        TEST_CASE(includesFile);
        TEST_CASE(enabledAll);
        TEST_CASE(enabledStyle);
        TEST_CASE(enabledPerformance);
        TEST_CASE(enabledPortability);
        TEST_CASE(enabledUnusedFunction);
        TEST_CASE(enabledMissingInclude);
#ifndef NDEBUG
        TEST_CASE(enabledInternal);
#endif
        TEST_CASE(errorExitcode);
        TEST_CASE(errorExitcodeMissing);
        TEST_CASE(errorExitcodeStr);
        TEST_CASE(exitcodeSuppressionsOld); // TODO: Create and test real suppression file
        TEST_CASE(exitcodeSuppressions);
        TEST_CASE(exitcodeSuppressionsNoFile);
        TEST_CASE(fileList); // TODO: Create and test real file listing file
        // TEST_CASE(fileListStdin);  // Disabled since hangs the test run
        TEST_CASE(inlineSuppr);
        TEST_CASE(jobs);
        TEST_CASE(jobsMissingCount);
        TEST_CASE(jobsInvalid);
        TEST_CASE(maxConfigs);
        TEST_CASE(maxConfigsMissingCount);
        TEST_CASE(maxConfigsInvalid);
        TEST_CASE(maxConfigsTooSmall);
        TEST_CASE(reportProgressTest); // "Test" suffix to avoid hiding the parent's reportProgress
        TEST_CASE(stdposix);
        TEST_CASE(stdc99);
        TEST_CASE(stdcpp11);
        TEST_CASE(suppressionsOld); // TODO: Create and test real suppression file
        TEST_CASE(suppressions);
        TEST_CASE(suppressionsNoFile);
        TEST_CASE(suppressionSingle);
        TEST_CASE(suppressionSingleFile);
        TEST_CASE(suppressionTwo);
        TEST_CASE(suppressionTwoSeparate);
        TEST_CASE(templates);
        TEST_CASE(templatesGcc);
        TEST_CASE(templatesVs);
        TEST_CASE(templatesEdit);
        TEST_CASE(xml);
        TEST_CASE(xmlver1);
        TEST_CASE(xmlver2);
        TEST_CASE(xmlver2both);
        TEST_CASE(xmlver2both2);
        TEST_CASE(xmlverunknown);
        TEST_CASE(xmlverinvalid);
        TEST_CASE(errorlist1);
        TEST_CASE(errorlistverbose1);
        TEST_CASE(errorlistverbose2);
        TEST_CASE(ignorepathsnopath);

        // Disabling these tests since they use relative paths to the
        // testrunner executable.
        //TEST_CASE(ignorepaths1);
        //TEST_CASE(ignorepaths2);
        //TEST_CASE(ignorepaths3);
        //TEST_CASE(ignorepaths4);
        //TEST_CASE(ignorefilepaths1);
        //TEST_CASE(ignorefilepaths2);

        TEST_CASE(checkconfig);
        TEST_CASE(unknownParam);

        TEST_CASE(undefs_noarg);
        TEST_CASE(undefs_noarg2);
        TEST_CASE(undefs_noarg3);
        TEST_CASE(undefs);
        TEST_CASE(undefs2);
    }


    void nooptions() {
        REDIRECT;
        const char *argv[] = {"cppcheck"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(1, argv));
        ASSERT_EQUALS(true, parser.GetShowHelp());
    }

    void helpshort() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-h"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(2, argv));
        ASSERT_EQUALS(true, parser.GetShowHelp());
    }

    void helplong() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--help"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(2, argv));
        ASSERT_EQUALS(true, parser.GetShowHelp());
    }

    void showversion() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--version"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(2, argv));
        ASSERT_EQUALS(true, parser.GetShowVersion());
    }

    void onefile() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(2, argv));
        ASSERT_EQUALS(1, (int)parser.GetPathNames().size());
        ASSERT_EQUALS("file.cpp", parser.GetPathNames().at(0));
    }

    void onepath() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "src"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(2, argv));
        ASSERT_EQUALS(1, (int)parser.GetPathNames().size());
        ASSERT_EQUALS("src", parser.GetPathNames().at(0));
    }

    void optionwithoutfile() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-v"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT_EQUALS(false, parser.ParseFromArgs(2, argv));
        ASSERT_EQUALS(0, (int)parser.GetPathNames().size());
    }

    void verboseshort() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-v", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT_EQUALS(true, settings._verbose);
    }

    void verboselong() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--verbose", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT_EQUALS(true, settings._verbose);
    }

    void debug() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--debug", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT_EQUALS(true, settings.debug);
    }

    void debugwarnings() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--debug-warnings", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT_EQUALS(true, settings.debugwarnings);
    }

    void forceshort() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-f", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT_EQUALS(true, settings._force);
    }

    void forcelong() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--force", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT_EQUALS(true, settings._force);
    }

    void relativePaths() {
        REDIRECT;
        Settings settings;
        CmdLineParser parser(&settings);

        const char *argvs[] = {"cppcheck", "-rp", "file.cpp"};
        ASSERT(parser.ParseFromArgs(3, argvs));
        ASSERT_EQUALS(true, settings._relativePaths);

        settings._relativePaths = false;

        const char *argvl[] = {"cppcheck", "--relative-paths", "file.cpp"};
        ASSERT(parser.ParseFromArgs(3, argvl));
        ASSERT_EQUALS(true, settings._relativePaths);

        settings._relativePaths = false;
        settings._basePaths.clear();

        const char *argvsp[] = {"cppcheck", "-rp=C:/foo;C:\\bar", "file.cpp"};
        ASSERT(parser.ParseFromArgs(3, argvsp));
        ASSERT_EQUALS(true, settings._relativePaths);
        ASSERT_EQUALS(2, settings._basePaths.size());
        ASSERT_EQUALS("C:/foo", settings._basePaths[0]);
        ASSERT_EQUALS("C:/bar", settings._basePaths[1]);

        settings._relativePaths = false;
        settings._basePaths.clear();

        const char *argvlp[] = {"cppcheck", "--relative-paths=C:/foo;C:\\bar", "file.cpp"};
        ASSERT(parser.ParseFromArgs(3, argvlp));
        ASSERT_EQUALS(true, settings._relativePaths);
        ASSERT_EQUALS(2, settings._basePaths.size());
        ASSERT_EQUALS("C:/foo", settings._basePaths[0]);
        ASSERT_EQUALS("C:/bar", settings._basePaths[1]);
    }

    void quietshort() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-q", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT_EQUALS(true, settings._errorsOnly);
    }

    void quietlong() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--quiet", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT_EQUALS(true, settings._errorsOnly);
    }

    void defines_noarg() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-D"};
        Settings settings;
        CmdLineParser parser(&settings);
        // Fails since -D has no param
        ASSERT_EQUALS(false, parser.ParseFromArgs(2, argv));
    }

    void defines_noarg2() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-D", "-v", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        // Fails since -D has no param
        ASSERT_EQUALS(false, parser.ParseFromArgs(4, argv));
    }

    void defines_noarg3() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-D", "--quiet", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        // Fails since -D has no param
        ASSERT_EQUALS(false, parser.ParseFromArgs(4, argv));
    }

    void defines() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-D_WIN32", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT_EQUALS("_WIN32=1", settings.userDefines);
    }

    void defines2() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-D_WIN32", "-DNODEBUG", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(4, argv));
        ASSERT_EQUALS("_WIN32=1;NODEBUG=1", settings.userDefines);
    }

    void defines3() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-D", "DEBUG", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(4, argv));
        ASSERT_EQUALS("DEBUG=1", settings.userDefines);
    }

    void defines4() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-DDEBUG=", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT_EQUALS("DEBUG", settings.userDefines);
    }

    void includesnopath() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-I", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        // Fails since -I has no param
        ASSERT_EQUALS(false, parser.ParseFromArgs(3, argv));
    }

    void includes() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-I", "include", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(4, argv));
        ASSERT_EQUALS("include/", settings._includePaths.front());
    }

    void includesslash() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-I", "include/", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(4, argv));
        ASSERT_EQUALS("include/", settings._includePaths.front());
    }

    void includesbackslash() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-I", "include\\", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(4, argv));
        ASSERT_EQUALS("include/", settings._includePaths.front());
    }

    void includesnospace() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-Iinclude", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT_EQUALS("include/", settings._includePaths.front());
    }

    void includes2() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-I", "include/", "-I", "framework/", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(6, argv));
        ASSERT_EQUALS("include/", settings._includePaths.front());
        settings._includePaths.pop_front();
        ASSERT_EQUALS("framework/", settings._includePaths.front());
    }

    void includesFile() {
        // TODO: Fails since cannot open the file
        REDIRECT;
        const char *argv[] = {"cppcheck", "--includes-file=inclpaths.txt", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT_EQUALS(true, parser.ParseFromArgs(3, argv));
    }

    void enabledAll() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--enable=all", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT(settings.isEnabled("style"));
        ASSERT(settings.isEnabled("unusedFunction"));
        ASSERT(settings.isEnabled("missingInclude"));
        ASSERT(!settings.isEnabled("internal"));
    }

    void enabledStyle() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--enable=style", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT(settings.isEnabled("style"));
        ASSERT(settings.isEnabled("performance"));
        ASSERT(settings.isEnabled("portability"));
        ASSERT(!settings.isEnabled("unusedFunction"));
        ASSERT(!settings.isEnabled("missingInclude"));
    }

    void enabledPerformance() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--enable=performance", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT(!settings.isEnabled("style"));
        ASSERT(settings.isEnabled("performance"));
        ASSERT(!settings.isEnabled("portability"));
        ASSERT(!settings.isEnabled("unusedFunction"));
        ASSERT(!settings.isEnabled("missingInclude"));
    }

    void enabledPortability() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--enable=portability", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT(!settings.isEnabled("style"));
        ASSERT(!settings.isEnabled("performance"));
        ASSERT(settings.isEnabled("portability"));
        ASSERT(!settings.isEnabled("unusedFunction"));
        ASSERT(!settings.isEnabled("missingInclude"));
    }

    void enabledUnusedFunction() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--enable=unusedFunction", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT(settings.isEnabled("unusedFunction"));
    }

    void enabledMissingInclude() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--enable=missingInclude", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT(settings.isEnabled("missingInclude"));
    }

#ifndef NDEBUG
    void enabledInternal() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--enable=internal", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT(settings.isEnabled("internal"));
    }
#endif

    void errorExitcode() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--error-exitcode=5", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT_EQUALS(5, settings._exitCode);
    }

    void errorExitcodeMissing() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--error-exitcode=", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        // Fails since exit code not given
        ASSERT_EQUALS(false, parser.ParseFromArgs(3, argv));
    }

    void errorExitcodeStr() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--error-exitcode=foo", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        // Fails since invalid exit code
        ASSERT_EQUALS(false, parser.ParseFromArgs(3, argv));
    }

    void exitcodeSuppressionsOld() {
        // TODO: Fails since cannot open the file
        REDIRECT;
        const char *argv[] = {"cppcheck", "--exitcode-suppressions", "suppr.txt", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        TODO_ASSERT_EQUALS(true, false, parser.ParseFromArgs(4, argv));
    }

    void exitcodeSuppressions() {
        // TODO: Fails since cannot open the file
        REDIRECT;
        const char *argv[] = {"cppcheck", "--exitcode-suppressions=suppr.txt", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        TODO_ASSERT_EQUALS(true, false, parser.ParseFromArgs(3, argv));
    }

    void exitcodeSuppressionsNoFile() {
        // TODO: Fails since cannot open the file
        REDIRECT;
        const char *argv[] = {"cppcheck", "--exitcode-suppressions", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        TODO_ASSERT_EQUALS(true, false, parser.ParseFromArgs(3, argv));
    }

    void fileList() {
        // TODO: Fails since cannot open the file
        REDIRECT;
        const char *argv[] = {"cppcheck", "--file-list", "files.txt", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        TODO_ASSERT_EQUALS(true, false, parser.ParseFromArgs(4, argv));
    }

    void fileListStdin() {
        // TODO: Give it some stdin to read from, fails because the list of
        // files in stdin (_pathnames) is empty
        REDIRECT;
        const char *argv[] = {"cppcheck", "--file-list=-", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        TODO_ASSERT_EQUALS(true, false, parser.ParseFromArgs(3, argv));
    }

    void inlineSuppr() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--inline-suppr", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
    }

    void jobs() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-j", "3", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(4, argv));
        ASSERT_EQUALS(3, settings._jobs);
    }

    void jobsMissingCount() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-j", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        // Fails since -j is missing thread count
        ASSERT_EQUALS(false, parser.ParseFromArgs(3, argv));
    }

    void jobsInvalid() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-j", "e", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        // Fails since invalid count given for -j
        ASSERT_EQUALS(false, parser.ParseFromArgs(4, argv));
    }

    void maxConfigs() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-f", "--max-configs=12", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(4, argv));
        ASSERT_EQUALS(12, settings._maxConfigs);
        ASSERT_EQUALS(false, settings._force);
    }

    void maxConfigsMissingCount() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--max-configs=", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        // Fails since --max-configs= is missing limit
        ASSERT_EQUALS(false, parser.ParseFromArgs(3, argv));
    }

    void maxConfigsInvalid() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--max-configs=e", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        // Fails since invalid count given for --max-configs=
        ASSERT_EQUALS(false, parser.ParseFromArgs(3, argv));
    }

    void maxConfigsTooSmall() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--max-configs=0", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        // Fails since limit must be greater than 0
        ASSERT_EQUALS(false, parser.ParseFromArgs(3, argv));
    }

    void reportProgressTest() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--report-progress", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT(settings.reportProgress);
    }

    void stdposix() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--std=posix", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT(settings.standards.posix);
    }

    void stdc99() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--std=c99", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT(settings.standards.c99);
    }

    void stdcpp11() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--std=c++11", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT(settings.standards.cpp11);
    }

    void suppressionsOld() {
        // TODO: Fails because there is no suppr.txt file!
        REDIRECT;
        const char *argv[] = {"cppcheck", "--suppressions", "suppr.txt", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(!parser.ParseFromArgs(4, argv));
    }

    void suppressions() {
        // TODO: Fails because there is no suppr.txt file!
        REDIRECT;
        const char *argv[] = {"cppcheck", "--suppressions-list=suppr.txt", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        TODO_ASSERT_EQUALS(true, false, parser.ParseFromArgs(3, argv));
    }

    void suppressionsNoFile() {
        REDIRECT;
        {
            CLEAR_REDIRECT_OUTPUT;
            const char *argv[] = {"cppcheck", "--suppressions-list=", "file.cpp"};
            Settings settings;
            CmdLineParser parser(&settings);
            ASSERT_EQUALS(false, parser.ParseFromArgs(3, argv));
            ASSERT_EQUALS(false, GET_REDIRECT_OUTPUT.find("If you want to pass two files") != std::string::npos);
        }

        {
            CLEAR_REDIRECT_OUTPUT;
            const char *argv[] = {"cppcheck", "--suppressions-list=a.suppr,b.suppr", "file.cpp"};
            Settings settings;
            CmdLineParser parser(&settings);
            ASSERT_EQUALS(false, parser.ParseFromArgs(3, argv));
            ASSERT_EQUALS(true, GET_REDIRECT_OUTPUT.find("If you want to pass two files") != std::string::npos);
        }

        {
            CLEAR_REDIRECT_OUTPUT;
            const char *argv[] = {"cppcheck", "--suppressions-list=a.suppr b.suppr", "file.cpp"};
            Settings settings;
            CmdLineParser parser(&settings);
            ASSERT_EQUALS(false, parser.ParseFromArgs(3, argv));
            ASSERT_EQUALS(true, GET_REDIRECT_OUTPUT.find("If you want to pass two files") != std::string::npos);
        }
    }

    void suppressionSingle() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--suppress=uninitvar", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT_EQUALS(true, settings.nomsg.isSuppressed("uninitvar", "file.cpp", 1U));
    }

    void suppressionSingleFile() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--suppress=uninitvar:file.cpp", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT_EQUALS(true, settings.nomsg.isSuppressed("uninitvar", "file.cpp", 1U));
    }

    void suppressionTwo() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--suppress=uninitvar,unnecessaryQualification", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        TODO_ASSERT_EQUALS(true, false, parser.ParseFromArgs(3, argv));
        TODO_ASSERT_EQUALS(true, false, settings.nomsg.isSuppressed("uninitvar", "file.cpp", 1U));
        TODO_ASSERT_EQUALS(true, false, settings.nomsg.isSuppressed("unnecessaryQualification", "file.cpp", 1U));
    }

    void suppressionTwoSeparate() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--suppress=uninitvar", "--suppress=unnecessaryQualification", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(4, argv));
        ASSERT_EQUALS(true, settings.nomsg.isSuppressed("uninitvar", "file.cpp", 1U));
        ASSERT_EQUALS(true, settings.nomsg.isSuppressed("unnecessaryQualification", "file.cpp", 1U));
    }

    void templates() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--template", "{file}:{line},{severity},{id},{message}", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(4, argv));
        ASSERT_EQUALS("{file}:{line},{severity},{id},{message}", settings._outputFormat);
    }

    void templatesGcc() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--template", "gcc", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(4, argv));
        ASSERT_EQUALS("{file}:{line}: {severity}: {message}", settings._outputFormat);
    }

    void templatesVs() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--template", "vs", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(4, argv));
        ASSERT_EQUALS("{file}({line}): {severity}: {message}", settings._outputFormat);
    }

    void templatesEdit() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--template", "edit", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(4, argv));
        ASSERT_EQUALS("{file} +{line}: {severity}: {message}", settings._outputFormat);
    }

    void xml() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--xml", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT(settings._xml);
        ASSERT_EQUALS(1, settings._xml_version);
    }

    void xmlver1() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--xml-version=1", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT(settings._xml);
        ASSERT_EQUALS(1, settings._xml_version);
    }

    void xmlver2() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--xml-version=2", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT(settings._xml);
        ASSERT_EQUALS(2, settings._xml_version);
    }

    void xmlver2both() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--xml", "--xml-version=2", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(4, argv));
        ASSERT(settings._xml);
        ASSERT_EQUALS(2, settings._xml_version);
    }

    void xmlver2both2() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--xml-version=2", "--xml", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(4, argv));
        ASSERT(settings._xml);
        ASSERT_EQUALS(2, settings._xml_version);
    }

    void xmlverunknown() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--xml", "--xml-version=3", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        // FAils since unknown XML format version
        ASSERT_EQUALS(false, parser.ParseFromArgs(4, argv));
    }

    void xmlverinvalid() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--xml", "--xml-version=a", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        // FAils since unknown XML format version
        ASSERT_EQUALS(false, parser.ParseFromArgs(4, argv));
    }

    void errorlist1() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--errorlist"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(2, argv));
    }

    void errorlistverbose1() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--verbose", "--errorlist"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT(settings._verbose);
    }

    void errorlistverbose2() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--errorlist", "--verbose"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT(settings._verbose);
    }

    void ignorepathsnopath() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-i"};
        Settings settings;
        CmdLineParser parser(&settings);
        // Fails since no ignored path given
        ASSERT_EQUALS(false, parser.ParseFromArgs(2, argv));
        ASSERT_EQUALS(0, parser.GetIgnoredPaths().size());
    }

    void ignorepaths1() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-isrc", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT_EQUALS(1, parser.GetIgnoredPaths().size());
        ASSERT_EQUALS("src/", parser.GetIgnoredPaths()[0]);
    }

    void ignorepaths2() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-i", "src", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(4, argv));
        ASSERT_EQUALS(1, parser.GetIgnoredPaths().size());
        ASSERT_EQUALS("src/", parser.GetIgnoredPaths()[0]);
    }

    void ignorepaths3() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-isrc", "-imodule", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(4, argv));
        ASSERT_EQUALS(2, parser.GetIgnoredPaths().size());
        ASSERT_EQUALS("src/", parser.GetIgnoredPaths()[0]);
        ASSERT_EQUALS("module/", parser.GetIgnoredPaths()[1]);
    }

    void ignorepaths4() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-i", "src", "-i", "module", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(6, argv));
        ASSERT_EQUALS(2, parser.GetIgnoredPaths().size());
        ASSERT_EQUALS("src/", parser.GetIgnoredPaths()[0]);
        ASSERT_EQUALS("module/", parser.GetIgnoredPaths()[1]);
    }

    void ignorefilepaths1() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-ifoo.cpp", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT_EQUALS(1, parser.GetIgnoredPaths().size());
        ASSERT_EQUALS("foo.cpp", parser.GetIgnoredPaths()[0]);
    }

    void ignorefilepaths2() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-isrc/foo.cpp", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT_EQUALS(1, parser.GetIgnoredPaths().size());
        ASSERT_EQUALS("src/foo.cpp", parser.GetIgnoredPaths()[0]);
    }

    void checkconfig() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--check-config", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT_EQUALS(true, settings.checkConfiguration);
    }

    void unknownParam() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "--foo", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(!parser.ParseFromArgs(3, argv));
    }

    void undefs() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-U_WIN32", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(3, argv));
        ASSERT_EQUALS(1, settings.userUndefs.size());
        ASSERT(settings.userUndefs.find("_WIN32") != settings.userUndefs.end());
    }

    void undefs2() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-U_WIN32", "-UNODEBUG", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        ASSERT(parser.ParseFromArgs(4, argv));
        ASSERT_EQUALS(2, settings.userUndefs.size());
        ASSERT(settings.userUndefs.find("_WIN32") != settings.userUndefs.end());
        ASSERT(settings.userUndefs.find("NODEBUG") != settings.userUndefs.end());
    }

    void undefs_noarg() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-U"};
        Settings settings;
        CmdLineParser parser(&settings);
        // Fails since -U has no param
        ASSERT_EQUALS(false, parser.ParseFromArgs(2, argv));
    }

    void undefs_noarg2() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-U", "-v", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        // Fails since -U has no param
        ASSERT_EQUALS(false, parser.ParseFromArgs(4, argv));
    }

    void undefs_noarg3() {
        REDIRECT;
        const char *argv[] = {"cppcheck", "-U", "--quiet", "file.cpp"};
        Settings settings;
        CmdLineParser parser(&settings);
        // Fails since -U has no param
        ASSERT_EQUALS(false, parser.ParseFromArgs(4, argv));
    }
};

REGISTER_TEST(TestCmdlineParser)
