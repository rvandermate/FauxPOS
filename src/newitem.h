#pragma once
#include "ui_new_item.h"
#include <QDialog>
#include <QSettings>

namespace dialog
{
    struct NewItem : QDialog
    {
        NewItem( QString const& barcode, QSettings& db );
        void Accepted();

        Ui::NewItem m_ui{};
        QSettings& m_db;
    };
}