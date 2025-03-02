#ifndef T_ICON_H
#define T_ICON_H

#include <QMetaEnum>

#include "T_BasePage.h"
class ElaLineEdit;
class ElaListView;
class T_IconModel;
class T_IconDelegate;
class ElaPivot;
class T_Icon : public T_BasePage {
  Q_OBJECT
public:
  Q_INVOKABLE explicit T_Icon(QWidget *parent = nullptr);
  ~T_Icon();
  Q_SLOT void onSearchEditTextEdit(const QString &searchText);

private:
  QMetaEnum _elaIconMetaEnum;   // 改名为_elaIconMetaEnum
  QMetaEnum _remixIconMetaEnum; // 添加RemixIcon元数据枚举
  ElaLineEdit *_searchEdit{nullptr};
  ElaListView *_iconView;
  T_IconModel *_iconModel;
  T_IconDelegate *_iconDelegate;
  ElaPivot *_iconTypePivot{nullptr};

  void updateIconList(int pivotIndex);
};

#endif // T_ICON_H
