#include "TraceFilterModel.h"

TraceFilterModel::TraceFilterModel(QObject *parent)
    : QSortFilterProxyModel{parent},
    _filterText("")
{
   setRecursiveFilteringEnabled(false);
}


void TraceFilterModel::setFilterText(QString filtertext)
{
    _filterText = filtertext;
}

bool TraceFilterModel::filterAcceptsRow(int source_row, const QModelIndex & source_parent) const
{
    // Pass all on no filter
    if(_filterText.length() == 0)
        return true;

    QModelIndex idx0 = sourceModel()->index(source_row, 1, source_parent); // Channel
    QModelIndex idx1 = sourceModel()->index(source_row, 3, source_parent); // CAN ID
    QModelIndex idx2 = sourceModel()->index(source_row, 4, source_parent); // Sender
    QModelIndex idx3 = sourceModel()->index(source_row, 5, source_parent); // Name

    QString datastr0 = sourceModel()->data(idx0).toString();
    QString datastr1 = sourceModel()->data(idx1).toString();
    QString datastr2 = sourceModel()->data(idx2).toString();
    QString datastr3 = sourceModel()->data(idx3).toString();

    fprintf(stderr, "Data for acceptance is %s\r\n", datastr1.toStdString().c_str());

    QRegularExpression _filterTextRE(_filterText);

    if( datastr0.contains(_filterTextRE) ||
        datastr1.contains(_filterTextRE) ||
        datastr2.contains(_filterTextRE) ||
        datastr3.contains(_filterTextRE))
        return true;
    else
        return false;
}
