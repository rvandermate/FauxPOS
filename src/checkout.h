#pragma once

#include "ui_checkout.h"
#include <QDialog>

namespace dialog
{
    struct Checkout : QDialog
    {
        Checkout( QString const& total );

        Ui::Checkout m_ui{};
    };
}