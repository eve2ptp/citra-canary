// Copyright 2023 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include <algorithm>
#include <sstream>
#include "common/file_util.h"
#include "common/ini.h"
#include "common/logging/log.h"

namespace Common {

INIReader::INIReader(const std::string& filename) {
    FileUtil::IOFile file{filename, "r"};
    if (!file.IsOpen()) {
        return;
    }

    std::string buf(file.GetSize(), '\0');
    const size_t read_size = file.ReadBytes(buf.data(), buf.size());
    if (!read_size) {
        return;
    }

    // Resize the string to the read size to trim excess data read at the end of file.
    buf.resize(read_size);

    std::stringstream ss{buf};
    std::string section;
    std::string line;

    while (std::getline(ss, line)) {
        if (line.empty()) {
            continue;
        }

        // Remove all whitespace from the line
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());

        // Check if the line is a comment
        if (line[0] == '#' || line[0] == ';') {
            continue;
        }

        // Start of a new section
        if (line[0] == '[') {
            section = line.substr(1, line.find(']') - 1);
            continue;
        }

        // Not a comment, must be a name=value pair
        const size_t assign_pos = line.find('=');
        const std::string name = line.substr(0, assign_pos);
        const std::string value = line.substr(assign_pos + 1, line.size() - 1);
        if (name.empty()) {
            continue;
        }

        // Check if it already exists before adding it
        const auto [it, new_name] = values[section].try_emplace(name);
        if (!new_name) {
            LOG_WARNING(Common, "Section {} contains duplicate name {}, ignoring!", section, name);
            continue;
        }
        it->second = value;
    }
    is_parsed = true;
}

bool INIReader::IsOpen() const {
    return is_parsed;
}

bool INIReader::Save(const std::string& filename) {
    FileUtil::IOFile file{filename, "w"};
    if (!file.IsOpen()) {
        LOG_ERROR(Common, "Unable to open file {} for saving", filename);
        return false;
    }

    for (const auto& [section, keys] : values) {
        const std::string header = fmt::format("[{}]\n", section);
        file.WriteString(header);
        for (const auto& [key, value] : keys) {
            const std::string pair = fmt::format("{}={}\n", key, value);
            file.WriteString(pair);
        }
        file.WriteString("\n");
    }

    file.Flush();
    return true;
}

bool INIReader::HasSection(const std::string& section) {
    return values.count(section) > 0;
}

const std::set<std::string> INIReader::Sections() const {
    std::set<std::string> retval;
    for (auto const& element : values) {
        retval.insert(element.first);
    }
    return retval;
}

const std::set<std::string> INIReader::Keys(const std::string& section) const {
    auto const _section = Get(section);
    std::set<std::string> retval;
    for (auto const& element : _section) {
        retval.insert(element.first);
    }
    return retval;
}

const INIReader::Section& INIReader::Get(const std::string& section) const {
    const auto it = values.find(section);
    if (it == values.end()) {
        return dummy_section;
    }
    return it->second;
}

std::string INIReader::Get(const std::string& section, const std::string& name,
                           std::string default_value) const {
    const Section& _section = Get(section);
    const auto it = _section.find(name);
    if (it == _section.end()) {
        return default_value;
    }
    return it->second;
}

long INIReader::GetInteger(const std::string& section, const std::string& name,
                           long default_value) const {
    std::string value = Get(section, name, "");
    size_t pos{};
    long n = std::stol(value, &pos);
    return pos > 0 ? n : default_value;
}

double INIReader::GetReal(const std::string& section, const std::string& name,
                          double default_value) const {
    std::string value = Get(section, name, "");
    size_t pos{};
    double n = std::stod(value, &pos);
    return pos > 0 ? n : default_value;
}

bool INIReader::GetBoolean(const std::string& section, const std::string& name,
                           bool default_value) const {
    std::string valstr = Get(section, name, "");
    // Convert to lower case to make string comparisons case-insensitive
    std::transform(valstr.begin(), valstr.end(), valstr.begin(), ::tolower);
    if (valstr == "true" || valstr == "yes" || valstr == "on" || valstr == "1") {
        return true;
    } else if (valstr == "false" || valstr == "no" || valstr == "off" || valstr == "0") {
        return false;
    } else {
        return default_value;
    }
}

void INIReader::SetInteger(const std::string& section, const std::string& name, long value) {
    values[section][name] = std::to_string(value);
}

void INIReader::SetBoolean(const std::string& section, const std::string& name, bool value) {
    values[section][name] = value ? "true" : "false";
}

void INIReader::SetReal(const std::string& section, const std::string& name, double value) {
    values[section][name] = std::to_string(value);
}

} // namespace Common
