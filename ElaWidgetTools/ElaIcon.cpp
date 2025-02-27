#include "ElaIcon.h"
#include <QPainter>
#include <QPixmap>

Q_SINGLETON_CREATE_CPP(ElaIcon)

ElaIcon::ElaIcon()
{
    initFontConfigs();
}

ElaIcon::~ElaIcon()
{
}

void ElaIcon::initFontConfigs()
{
    // 初始化字体配置
    fontConfigs[ElaFontType::FontAwesome] = FontConfig("ElaAwesome", 25);
    fontConfigs[ElaFontType::RemixIcon] = FontConfig("RemixIcon", 25);
}

QIcon ElaIcon::createIcon(const QString& fontFamily, unsigned short unicode,
                         int size, const QColor& color,
                         int width, int height)
{
    QFont iconFont = QFont(fontFamily);
    QPixmap pix(width > 0 ? width : size, height > 0 ? height : size);
    pix.fill(Qt::transparent);

    QPainter painter;
    painter.begin(&pix);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);

    if (color != Qt::black) {
        painter.setPen(color);
    }

    iconFont.setPixelSize(size);
    painter.setFont(iconFont);
    painter.drawText(pix.rect(), Qt::AlignCenter, QChar(unicode));
    painter.end();

    return QIcon(pix);
}

// Font Awesome 图标实现
QIcon ElaIcon::getElaIcon(ElaIconType::IconName awesome)
{
    return createIcon(fontConfigs[ElaFontType::FontAwesome].fontFamily,
                     (unsigned short)awesome);
}

QIcon ElaIcon::getElaIcon(ElaIconType::IconName awesome, QColor iconColor)
{
    return createIcon(fontConfigs[ElaFontType::FontAwesome].fontFamily,
                     (unsigned short)awesome, 30, iconColor);
}

QIcon ElaIcon::getElaIcon(ElaIconType::IconName awesome, int pixelSize)
{
    return createIcon(fontConfigs[ElaFontType::FontAwesome].fontFamily,
                     (unsigned short)awesome, pixelSize);
}

QIcon ElaIcon::getElaIcon(ElaIconType::IconName awesome, int pixelSize, QColor iconColor)
{
    return createIcon(fontConfigs[ElaFontType::FontAwesome].fontFamily,
                     (unsigned short)awesome, pixelSize, iconColor);
}

QIcon ElaIcon::getElaIcon(ElaIconType::IconName awesome, int pixelSize, int fixedWidth, int fixedHeight)
{
    return createIcon(fontConfigs[ElaFontType::FontAwesome].fontFamily,
                     (unsigned short)awesome, pixelSize, Qt::black, fixedWidth, fixedHeight);
}

QIcon ElaIcon::getElaIcon(ElaIconType::IconName awesome, int pixelSize, int fixedWidth, int fixedHeight, QColor iconColor)
{
    return createIcon(fontConfigs[ElaFontType::FontAwesome].fontFamily,
                     (unsigned short)awesome, pixelSize, iconColor, fixedWidth, fixedHeight);
}

// Remix Icon 图标实现
QIcon ElaIcon::getRemixIcon(RemixIconType::IconName remix)
{
    return createIcon(fontConfigs[ElaFontType::RemixIcon].fontFamily,
                     (unsigned short)remix);
}

QIcon ElaIcon::getRemixIcon(RemixIconType::IconName remix, QColor iconColor)
{
    return createIcon(fontConfigs[ElaFontType::RemixIcon].fontFamily,
                     (unsigned short)remix, 30, iconColor);
}

QIcon ElaIcon::getRemixIcon(RemixIconType::IconName remix, int pixelSize)
{
    return createIcon(fontConfigs[ElaFontType::RemixIcon].fontFamily,
                     (unsigned short)remix, pixelSize);
}

QIcon ElaIcon::getRemixIcon(RemixIconType::IconName remix, int pixelSize, QColor iconColor)
{
    return createIcon(fontConfigs[ElaFontType::RemixIcon].fontFamily,
                     (unsigned short)remix, pixelSize, iconColor);
}

QIcon ElaIcon::getRemixIcon(RemixIconType::IconName remix, int pixelSize, int fixedWidth, int fixedHeight)
{
    return createIcon(fontConfigs[ElaFontType::RemixIcon].fontFamily,
                     (unsigned short)remix, pixelSize, Qt::black, fixedWidth, fixedHeight);
}

QIcon ElaIcon::getRemixIcon(RemixIconType::IconName remix, int pixelSize, int fixedWidth, int fixedHeight, QColor iconColor)
{
    return createIcon(fontConfigs[ElaFontType::RemixIcon].fontFamily,
                     (unsigned short)remix, pixelSize, iconColor, fixedWidth, fixedHeight);
}