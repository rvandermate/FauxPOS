#include "checkout.h"

namespace dialog
{
    Checkout::Checkout( QString const& total )
    {
        m_ui.setupUi( this );
        m_ui.label->setText( m_ui.label->text().replace( "$0.00", total ) );
        connect( m_ui.cash, &QPushButton::clicked, [ this ] { accept(); } );
        connect( m_ui.card, &QPushButton::clicked, [ this ] { accept(); } );
    }
}