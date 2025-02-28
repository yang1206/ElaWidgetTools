#include "T_IconModel.h"

#include "Def.h"
T_IconModel::T_IconModel(QObject* parent)
    : QAbstractListModel{parent}
{
    _elaIconMetaEnum = QMetaEnum::fromType<ElaIconType::IconName>();
    _remixIconMetaEnum = QMetaEnum::fromType<RemixIconType::IconName>();
    _elaIconCount = _elaIconMetaEnum.keyCount() - 1;
    _remixIconCount = _remixIconMetaEnum.keyCount() - 1;
    _rowCount = _elaIconCount + _remixIconCount;
    _pIsSearchMode = false;
}

T_IconModel::~T_IconModel()
{
}

int T_IconModel::rowCount(const QModelIndex& parent) const
{
    return _rowCount;
}

void T_IconModel::setSearchKeyList(QStringList list)
{
    beginResetModel();
    this->_searchKeyList = list;
    if (_pIsSearchMode)
    {
        _rowCount = this->getSearchKeyList().count();
    }
    else
    {
        _rowCount = _elaIconCount + _remixIconCount;
    }
    endResetModel();
}

QStringList T_IconModel::getSearchKeyList()
{
    return this->_searchKeyList;
}

QVariant T_IconModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::UserRole)
    {
        if (!_pIsSearchMode)
        {
            if (index.row() >= _rowCount)
            {
                return QVariant();
            }

            // ElaIcon
            if (index.row() < _elaIconCount) {
                return QStringList{
                    QString("ElaIcon:") + _elaIconMetaEnum.key(index.row() + 1),
                    QChar(_elaIconMetaEnum.value(index.row() + 1))
                };
            }
            // RemixIcon
            else {
                int remixIndex = index.row() - _elaIconCount;
                return QStringList{
                    QString("RemixIcon:") + _remixIconMetaEnum.key(remixIndex + 1),
                    QChar(_remixIconMetaEnum.value(remixIndex + 1))
                };
            }
        }
        else
        {
            if (index.row() >= _searchKeyList.count())
            {
                return QVariant();
            }

            QString fullKey = _searchKeyList.at(index.row());
            QStringList parts = fullKey.split(":");

            if (parts.size() != 2) {
                return QVariant();
            }

            QString iconType = parts[0];
            QString iconName = parts[1];

            if (iconType == "ElaIcon") {
                return QStringList{
                    fullKey,
                    QChar(_elaIconMetaEnum.keyToValue(iconName.toUtf8().constData()))
                };
            } else if (iconType == "RemixIcon") {
                return QStringList{
                    fullKey,
                    QChar(_remixIconMetaEnum.keyToValue(iconName.toUtf8().constData()))
                };
            }
        }
    }
    return QVariant();
}

QString T_IconModel::getIconNameFromModelIndex(const QModelIndex& index) const
{
    QString iconName;
    if (_pIsSearchMode)
    {
        if (index.row() < _searchKeyList.count())
        {
            QString fullKey = _searchKeyList.at(index.row());
            QStringList parts = fullKey.split(":");

            if (parts.size() == 2) {
                if (parts[0] == "ElaIcon") {
                    iconName = QString("ElaIconType::") + parts[1];
                } else if (parts[0] == "RemixIcon") {
                    iconName = QString("RemixIconType::") + parts[1];
                }
            }
        }
    }
    else
    {
        if (index.row() < _elaIconCount) {
            iconName = QString("ElaIconType::") + _elaIconMetaEnum.key(index.row() + 1);
        } else if (index.row() < _rowCount) {
            int remixIndex = index.row() - _elaIconCount;
            iconName = QString("RemixIconType::") + _remixIconMetaEnum.key(remixIndex + 1);
        }
    }
    return iconName;
}
