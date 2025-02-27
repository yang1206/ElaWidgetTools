#ifndef ELAICON_H
#define ELAICON_H
#include <QIcon>
#include <QMap>
#include "Def.h"
#include "singleton.h"
#include "stdafx.h"
class ELA_EXPORT ElaIcon
{
    Q_SINGLETON_CREATE_H(ElaIcon)
private:
    explicit ElaIcon();
    ~ElaIcon();

    enum FontType {
        FontAwesome,
        MaterialIcons
    };

    // 字体配置结构体
    struct FontConfig {
        QString fontFamily;
        int defaultSize;
        FontConfig(const QString& family = "", int size = 25)
            : fontFamily(family), defaultSize(size) {}
    };

    QMap<ElaFontType::FontFamily, FontConfig> fontConfigs;

    // 通用的图标生成方法
    QIcon createIcon(const QString& fontFamily, unsigned short unicode,
                    int size = 30, const QColor& color = Qt::black,
                    int width = 0, int height = 0);

    void initFontConfigs();

public:
    QIcon getElaIcon(ElaIconType::IconName awesome);
    QIcon getElaIcon(ElaIconType::IconName awesome, QColor iconColor);
    QIcon getElaIcon(ElaIconType::IconName awesome, int pixelSize);
    QIcon getElaIcon(ElaIconType::IconName awesome, int pixelSize, QColor iconColor);
    QIcon getElaIcon(ElaIconType::IconName awesome, int pixelSize, int fixedWidth, int fixedHeight);
    QIcon getElaIcon(ElaIconType::IconName awesome, int pixelSize, int fixedWidth, int fixedHeight, QColor iconColor);


    // Remix Icon 图标方法
    QIcon getRemixIcon(RemixIconType::IconName remix);
    QIcon getRemixIcon(RemixIconType::IconName remix, QColor iconColor);
    QIcon getRemixIcon(RemixIconType::IconName remix, int pixelSize);
    QIcon getRemixIcon(RemixIconType::IconName remix, int pixelSize, QColor iconColor);
    QIcon getRemixIcon(RemixIconType::IconName remix, int pixelSize, int fixedWidth, int fixedHeight);
    QIcon getRemixIcon(RemixIconType::IconName remix, int pixelSize, int fixedWidth, int fixedHeight, QColor iconColor);
};

#endif // ELAICON_H
