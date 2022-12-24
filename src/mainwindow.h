#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QMainWindow>
#include <QSettings>
#include <QSpacerItem>

struct MainWindow : QMainWindow
{
    MainWindow();

private:
    void enterItem( QString const& barcode );
    QString barcode_to_item( QString const& barcode );
    double price_for_item( QString const& barcode );
    void reset();

    double _total_price{};
    Ui::MainWindow m_ui{};
    QSettings m_db{ "VanderGear", "FauxPOS" };

    struct Item : QWidget
    {
        Item( QString name, QString price ) :
            _name( std::move( name ) ),
            _price( std::move( price ) )
        {
            auto layout{ new QHBoxLayout{ this } };
            layout->addWidget( new QLabel( _name ) );
            layout->addItem( new QSpacerItem( 10, 10, QSizePolicy::Expanding ) );
            layout->addWidget( new QLabel( _price ) );
            setLayout( layout );
        }

    private:
        QString _name;
        QString _price;
    };
};