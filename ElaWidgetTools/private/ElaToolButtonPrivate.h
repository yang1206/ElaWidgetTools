#ifndef ELATOOLBUTTONPRIVATE_H
#define ELATOOLBUTTONPRIVATE_H

#include <QObject>

#include "Def.h"
#include "stdafx.h"
class ElaToolButton;
class ElaToolButtonStyle;
class ElaToolButtonPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(ElaToolButton)
public:
    explicit ElaToolButtonPrivate(QObject* parent = nullptr);
    ~ElaToolButtonPrivate();

private:
    ElaToolButtonStyle* _toolButtonStyle{nullptr};
    ElaFontType::FontFamily _iconFontType{ElaFontType::FontAwesome};
};

#endif // ELATOOLBUTTONPRIVATE_H
