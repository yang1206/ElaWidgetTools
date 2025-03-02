#ifndef T_ICONMODEL_H
#define T_ICONMODEL_H

#include <QAbstractListModel>
#include <QMetaEnum>

#include "stdafx.h"
class T_IconModel : public QAbstractListModel {
  Q_OBJECT
  Q_PROPERTY_CREATE(bool, IsSearchMode)
public:
  explicit T_IconModel(QObject *parent = nullptr);
  ~T_IconModel();
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  void setSearchKeyList(QStringList list);
  QStringList getSearchKeyList();
  void setIconTypeFilter(int filterType);

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  QString getIconNameFromModelIndex(const QModelIndex &index) const;

private:
  QMetaEnum _elaIconMetaEnum;   // 改名
  QMetaEnum _remixIconMetaEnum; // 添加RemixIcon元数据枚举
  QStringList _searchKeyList;
  int _rowCount;
  int _elaIconCount;   // ElaIcon的数量
  int _remixIconCount; // RemixIcon的数量

  int _iconTypeFilter{0}; // 0: 全部, 1: ElaIcon, 2: RemixIcon
};

#endif // T_ICONMODEL_H
