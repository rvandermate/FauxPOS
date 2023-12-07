#include "mainwindow.h"
#include "checkout.h"
#include "newitem.h"

QString price_to_str( double const price )
{
    return "$" + QString::number( price, 'f', 2 );
}

MainWindow::MainWindow()
{
    m_ui.setupUi( this );
    m_ui.lineEdit->setFocus();
    connect( m_ui.lineEdit, &QLineEdit::editingFinished, [ this ] { enterItem( m_ui.lineEdit->text() ); } );
    connect( m_ui.checkout, &QPushButton::clicked, [ this ] {
        dialog::Checkout( price_to_str( _total_price ) ).exec();
        reset();
    } );
}

void MainWindow::reset()
{
    _total_price = 0;
    m_ui.total->setText( "Total: " + price_to_str( _total_price ) );
    m_ui.listWidget->clear();
    m_ui.lineEdit->clear();
    m_ui.lineEdit->setFocus();
}

QString MainWindow::barcode_to_item( QString const& barcode )
{
    m_db.beginGroup( barcode );
    auto const item_name{ m_db.value( "item_name", barcode ) };
    m_db.endGroup();
    return item_name.toString();
}

double MainWindow::price_for_item( QString const& barcode )
{
    m_db.beginGroup( barcode );
    auto const value{ m_db.value( "price", 1.00 ) };
    m_db.endGroup();
    return value.toDouble();
}

void MainWindow::enterItem( QString const& barcode )
{
    m_ui.lineEdit->clear();
    m_ui.lineEdit->setFocus();

    if( barcode.isEmpty() )
    {
        return;
    }

    if( !m_db.childGroups().contains( barcode ) )
    {
        if( QDialog::Accepted != dialog::NewItem( barcode, m_db ).exec() )
        {
            return;
        }
    }

    auto price{ price_for_item( barcode ) };
    _total_price += price;

    m_ui.total->setText( "Total: " + price_to_str( _total_price ) );

    auto item{ new QListWidgetItem };
    m_ui.listWidget->addItem( item );
    m_ui.listWidget->setItemWidget( item, new Item( barcode_to_item( barcode ), price_to_str( price ) ) );
}