#include "newitem.h"

namespace dialog
{
    NewItem::NewItem( QString const& barcode, QSettings& db ) :
        m_db{ db }
    {
        m_ui.setupUi( this );
        m_ui.barcode->setText( barcode );
        connect( this, &QDialog::accepted, [ this ] { Accepted(); } );
    }

    void NewItem::Accepted()
    {
        m_db.beginGroup( m_ui.barcode->text() );
        if( auto const& name = m_ui.name->text(); !name.isEmpty() )
        {
            m_db.setValue( "item_name", m_ui.name->text() );
        }
        m_db.setValue( "price", m_ui.price->value() );
        m_db.endGroup();
        m_db.sync();
    }
}