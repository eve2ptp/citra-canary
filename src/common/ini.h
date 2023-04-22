// Copyright 2023 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include <set>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace Common {

class INIReader {
    using Section = std::unordered_map<std::string, std::string>;

public:
    INIReader() = default;
    explicit INIReader(const std::string& filename);

    /// Returns true if the ini file was opened and parsed
    bool IsOpen() const;

    /// Writes the contents of the INI file
    bool Save(const std::string& filename);

    /// Returns true if the INI file exists
    bool HasSection(const std::string& section);

    /// Returns the list of sections found in the INI file
    const std::set<std::string> Sections() const;

    /// Returns the list of keys in the given section
    const std::set<std::string> Keys(const std::string& section) const;

    /// Returns the map representing the values in a section of the INI file
    const Section& Get(const std::string& section) const;

    /**
     * @brief Return the value of the given key in the given section, return default
     * if not found
     * @param section The section name
     * @param name The key name
     * @param default_v The default value
     * @return The value of the given key in the given section, return default if
     * not found
     */
    std::string Get(const std::string& section, const std::string& name,
                    std::string default_value) const;

    long GetInteger(const std::string& section, const std::string& name, long default_value) const;

    bool GetBoolean(const std::string& section, const std::string& name, bool default_value) const;

    double GetReal(const std::string& section, const std::string& name, double default_value) const;

    /**
     * @brief Sets a key-value pair into the INI file
     * @param section The section name
     * @param name The key name
     * @param v The value to insert
     * @throws std::runtime_error if the key already exists in the section
     */
    void Set(const std::string& section, const std::string& name, const std::string& value);

    void SetInteger(const std::string& section, const std::string& name, long value);

    void SetBoolean(const std::string& section, const std::string& name, bool value);

    void SetReal(const std::string& section, const std::string& name, double value);

protected:
    std::unordered_map<std::string, Section> values;
    Section dummy_section{};
    bool is_parsed{};
};

} // namespace Common
