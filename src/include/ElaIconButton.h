#ifndef ELAICONBUTTON_H
#define ELAICONBUTTON_H

#include <QPushButton>

#include "Def.h"
#include "stdafx.h"
class ElaIconButtonPrivate;
class ELA_EXPORT ElaIconButton : public QPushButton
{
    Q_OBJECT
    Q_Q_CREATE(ElaIconButton)
    Q_PROPERTY_CREATE_Q_H(int, BorderRadius)
    Q_PROPERTY_CREATE_Q_H(QColor, LightHoverColor);
    Q_PROPERTY_CREATE_Q_H(QColor, DarkHoverColor);
    Q_PROPERTY_CREATE_Q_H(QColor, LightIconColor);
    Q_PROPERTY_CREATE_Q_H(QColor, DarkIconColor);
    Q_PROPERTY_CREATE_Q_H(QColor, LightHoverIconColor);
    Q_PROPERTY_CREATE_Q_H(QColor, DarkHoverIconColor);
    Q_PROPERTY_CREATE_Q_H(bool, IsSelected);

public:
    ElaIconButton(ElaIconType::IconName awesome, QWidget* parent = nullptr);
    ElaIconButton(ElaIconType::IconName awesome, int pixelSize, QWidget* parent = nullptr);
    ElaIconButton(ElaIconType::IconName awesome, int pixelSize, int fixedWidth, int fixedHeight, QWidget* parent = nullptr);
    ~ElaIconButton();
    void setAwesome(ElaIconType::IconName awesome);
    ElaIconType::IconName getAwesome() const;

protected:
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    virtual void enterEvent(QEnterEvent* event) override;
#else
    virtual void enterEvent(QEvent* event) override;
#endif
    virtual void leaveEvent(QEvent* event) override;
    virtual void paintEvent(QPaintEvent* event) override;
};

#endif // ELAICONBUTTON_H
