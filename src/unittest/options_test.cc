#include <map>
#include <vector>

#include "clustering/administration/main/options.hpp"
#include "unittest/gtest.hpp"

namespace unittest {

TEST(OptionsTest, CommandLineParsing) {
    const std::vector<const char *> command_line = {
        "--no-parameter",
        "--optional", "optional1",
        "--optional-repeat", "optional-repeat1",
        "--mandatory", "mandatory1",
        "--optional-repeat", "optional-repeat2",
        "-o", "optional-repeat3",
        "--mandatory-repeat", "mandatory-repeat1",
        "--mandatory-repeat", "mandatory-repeat2",
        "--mandatory-repeat", "mandatory-repeat3",
        "--override-default", "override-default1"
    };

    const std::vector<options::option_t> options = {
        options::option_t(options::names_t("--no-parameter"),
                          options::OPTIONAL_NO_PARAMETER),
        options::option_t(options::names_t("--optional"),
                          options::OPTIONAL),
        options::option_t(options::names_t("--optional-repeat", "-o"),
                          options::OPTIONAL_REPEAT),
        options::option_t(options::names_t("--mandatory"),
                          options::MANDATORY),
        options::option_t(options::names_t("--mandatory-repeat"),
                          options::MANDATORY_REPEAT),
        options::option_t(options::names_t("--override-default"),
                          options::OPTIONAL,
                          "default-not-overridden")
    };

    const std::map<std::string, std::vector<std::string> > opts
        = options::parse_command_line(command_line.size(), command_line.data(), options);

    const std::map<std::string, std::vector<std::string> > expected_parse = {
        { "--no-parameter", { "" } },
        { "--optional", { "optional1" } },
        { "--optional-repeat", { "optional-repeat1", "optional-repeat2", "optional-repeat3" } },
        { "--mandatory", { "mandatory1" } },
        { "--mandatory-repeat", { "mandatory-repeat1", "mandatory-repeat2", "mandatory-repeat3" } },
        { "--override-default", { "override-default1" } }
    };

    ASSERT_EQ(expected_parse, opts);
}


}  // namespace unittest
