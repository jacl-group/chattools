#include <iostream>
#include <string>
#include <vector>

#include <boost/program_options.hpp>

#include <sqlite3.h>

#include <Utils.h>

namespace po = boost::program_options;

using namespace std;

int main(int argc, const char *argv[]) {
    std::cout << "chattools" << std::endl;

    vector<string> commands;

    // https://stackoverflow.com/questions/39932089/how-to-add-a-description-to-boostprogram-options-positional-options/39934380

    po::options_description desc{"Options"};
    bool force;
    desc.add_options()
            ("help,h", "Help Screen")
            ("test", "Test option")
            ("mkusers", po::value<string>()->implicit_value("./"), "Make user database")
            ("force", po::bool_switch(&force), "Force operation")
            ;

    string const COMMANDS_KEY("commands");

    // Hide the 'commands' options in a separate description
    po::options_description desc_hidden("Hidden options");
    desc_hidden.add_options()
            (COMMANDS_KEY.c_str(), po::value(&commands), "commands");
    //(COMMANDS_KEY.c_str(), po::value(&commands)->required(), "commands");

    // This description is used for parsing and validation
    po::options_description cmdline_options;
    cmdline_options.add(desc).add(desc_hidden);

    // And this one to display help
    po::options_description visible_options;
    visible_options.add(desc);

    po::positional_options_description pos;
    pos.add(COMMANDS_KEY.c_str(), -1);

    po::variables_map vm;
    try {
        // Only parse the options, so we can catch the explicit `--files`
        auto parsed = po::command_line_parser(argc, argv)
            .options(cmdline_options)
            .positional(pos)
            .run();

        // Make sure there were no non-positional `files` options
        for (auto const& opt : parsed.options) {
            if ((opt.position_key == -1) && (opt.string_key == COMMANDS_KEY)) {
                throw po::unknown_option(COMMANDS_KEY);
            }
        }

        po::store(parsed, vm);
        po::notify(vm);
    } catch (const po::error &e) {
        std::cerr << "couldn't parse command line arguments properly:\n";
        std::cerr << e.what() << endl << endl;
        std::cerr << desc << endl;
        return 1;
    }

    notify(vm);

    if (vm.count("help") /*|| !vm.count("commands")*/) {
        std::cout << desc << '\n';
        return 1;
    }

    if(vm.count("mkusers")) {
        string directory = vm["mkusers"].as<std::string>();
        try {
            MkUsers users(directory, force);
            users.create();
        } catch(const runtime_error& e) {
            //std::cerr << ":\n";
            std::cerr << e.what() << endl << endl;
            std::cerr << desc << endl;
            return 1;
        }
    }

    if (!commands.empty()) {
        std::cout << "commands: \n";
        for (auto const& command : commands) {
            std::cout << " * " << command << "\n";
        }
    }

    return 0;
}
