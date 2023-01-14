// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include <memory>
#include <QWidget>

namespace Ui {
class ConfigureDebug;
}

namespace ConfigurationShared {
enum class CheckState;
}

class ConfigureDebug : public QWidget {
    Q_OBJECT

public:
    explicit ConfigureDebug(QWidget* parent = nullptr);
    ~ConfigureDebug() override;

    void ApplyConfiguration();
    void RetranslateUI();
    void SetConfiguration();
    void SetupPerGameUI();

    std::unique_ptr<Ui::ConfigureDebug> ui;
};
