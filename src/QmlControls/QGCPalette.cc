/****************************************************************************
 *
 * (c) 2009-2024 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/


/// @file
///     @author Don Gagne <don@thegagnes.com>

#include "QGCPalette.h"
#include "QGCCorePlugin.h"

#include <QtCore/QDebug>

QList<QGCPalette*>   QGCPalette::_paletteObjects;

QGCPalette::Theme QGCPalette::_theme = QGCPalette::Dark;

QMap<int, QMap<int, QMap<QString, QColor>>> QGCPalette::_colorInfoMap;

QStringList QGCPalette::_colors;

QGCPalette::QGCPalette(QObject* parent) :
    QObject(parent),
    _colorGroupEnabled(true)
{
    if (_colorInfoMap.isEmpty()) {
        _buildMap();
    }

    // We have to keep track of all QGCPalette objects in the system so we can signal theme change to all of them
    _paletteObjects += this;
}

QGCPalette::~QGCPalette()
{
    bool fSuccess = _paletteObjects.removeOne(this);
    if (!fSuccess) {
        qWarning() << "Internal error";
    }
}

void QGCPalette::_buildMap()
{
    //                                      Light                 Dark
    //                                      Disabled   Enabled    Disabled   Enabled

    // Monochrome palette: white/greys for Light theme, dark greys/black for Dark theme
    DECLARE_QGC_COLOR(window,               "#FFFFFF", "#FFFFFF", "#0D0D0D", "#0D0D0D")
    DECLARE_QGC_COLOR(windowTransparent,    "#80FFFFFF", "#80FFFFFF", "#800D0D0D", "#800D0D0D")
    DECLARE_QGC_COLOR(windowShadeLight,     "#F5F5F5", "#F5F5F5", "#303030", "#303030")
    DECLARE_QGC_COLOR(windowShade,          "#EFEFEF", "#EFEFEF", "#2B2B2B", "#2B2B2B")
    DECLARE_QGC_COLOR(windowShadeDark,      "#E0E0E0", "#E0E0E0", "#1F1F1F", "#1F1F1F")

    // Text / labels
    DECLARE_QGC_COLOR(text,                 "#808080", "#1F1F1F", "#BFBFBF", "#FFFFFF")
    DECLARE_QGC_COLOR(windowTransparentText,"#808080", "#1F1F1F", "#BFBFBF", "#FFFFFF")
    DECLARE_QGC_COLOR(warningText,          "#4A4A4A", "#1F1F1F", "#D0D0D0", "#FFFFFF")

    // Buttons
    DECLARE_QGC_COLOR(button,               "#F2F2F2", "#F2F2F2", "#2B2B2B", "#2B2B2B")
    DECLARE_QGC_COLOR(buttonBorder,         "#D0D0D0", "#D0D0D0", "#3A3A3A", "#3A3A3A")
    DECLARE_QGC_COLOR(buttonText,           "#808080", "#000000", "#BFBFBF", "#FFFFFF")
    DECLARE_QGC_COLOR(buttonHighlight,      "#EAEAEA", "#EAEAEA", "#3A3A3A", "#3A3A3A")
    DECLARE_QGC_COLOR(buttonHighlightText,  "#1F1F1F", "#FFFFFF", "#1F1F1F", "#FFFFFF")

    // Primary button: black in Light theme, white in Dark theme (text inversed)
    DECLARE_QGC_COLOR(primaryButton,        "#000000", "#000000", "#FFFFFF", "#FFFFFF")
    DECLARE_QGC_COLOR(primaryButtonText,    "#FFFFFF", "#FFFFFF", "#000000", "#000000")

    // Text fields
    DECLARE_QGC_COLOR(textField,            "#FFFFFF", "#FFFFFF", "#1F1F1F", "#1F1F1F")
    DECLARE_QGC_COLOR(textFieldText,        "#1F1F1F", "#1F1F1F", "#FFFFFF", "#FFFFFF")

    // Map / misc indicators -> keep monochrome accents
    DECLARE_QGC_COLOR(mapButton,            "#EAEAEA", "#2A2A2A", "#EAEAEA", "#2A2A2A")
    DECLARE_QGC_COLOR(mapButtonHighlight,   "#DADADA", "#3A3A3A", "#DADADA", "#3A3A3A")
    DECLARE_QGC_COLOR(mapIndicator,         "#7F7F7F", "#9A9A9A", "#9A9A9A", "#9A9A9A")
    DECLARE_QGC_COLOR(mapIndicatorChild,    "#9A9A9A", "#7F7F7F", "#7F7F7F", "#7F7F7F")

    // Generic named colors -> map to grey scale
    DECLARE_QGC_COLOR(colorGreen,           "#BDBDBD", "#BDBDBD", "#7F7F7F", "#7F7F7F")
    DECLARE_QGC_COLOR(colorYellow,          "#BDBDBD", "#BDBDBD", "#7F7F7F", "#7F7F7F")
    DECLARE_QGC_COLOR(colorYellowGreen,     "#BDBDBD", "#BDBDBD", "#7F7F7F", "#7F7F7F")
    DECLARE_QGC_COLOR(colorOrange,          "#BDBDBD", "#BDBDBD", "#7F7F7F", "#7F7F7F")
    DECLARE_QGC_COLOR(colorRed,             "#BDBDBD", "#BDBDBD", "#7F7F7F", "#7F7F7F")
    DECLARE_QGC_COLOR(colorGrey,            "#808080", "#808080", "#2A2A2A", "#2A2A2A")
    DECLARE_QGC_COLOR(colorBlue,            "#808080", "#808080", "#2A2A2A", "#2A2A2A")

    DECLARE_QGC_COLOR(alertBackground,      "#F5F5F5", "#F5F5F5", "#2B2B2B", "#2B2B2B")
    DECLARE_QGC_COLOR(alertBorder,          "#BDBDBD", "#BDBDBD", "#3A3A3A", "#3A3A3A")
    DECLARE_QGC_COLOR(alertText,            "#1F1F1F", "#1F1F1F", "#FFFFFF", "#FFFFFF")

    DECLARE_QGC_COLOR(missionItemEditor,    "#EFEFEF", "#EFEFEF", "#2A2A2A", "#2A2A2A")
    DECLARE_QGC_COLOR(toolStripHoverColor,  "#EAEAEA", "#2A2A2A", "#EAEAEA", "#2A2A2A")
    DECLARE_QGC_COLOR(statusFailedText,     "#1F1F1F", "#1F1F1F", "#FFFFFF", "#FFFFFF")
    DECLARE_QGC_COLOR(statusPassedText,     "#1F1F1F", "#1F1F1F", "#FFFFFF", "#FFFFFF")
    DECLARE_QGC_COLOR(statusPendingText,    "#1F1F1F", "#1F1F1F", "#FFFFFF", "#FFFFFF")

    DECLARE_QGC_COLOR(toolbarBackground,    "#00FFFFFF", "#00FFFFFF", "#0A0A0A10", "#0A0A0A10")
    DECLARE_QGC_COLOR(toolbarDivider,       "#00000000", "#00000000", "#00000000", "#00000000")
    DECLARE_QGC_COLOR(groupBorder,          "#BDBDBD", "#BDBDBD", "#2A2A2A", "#2A2A2A")

    // Non-themed branding colors -> neutral greys
    DECLARE_QGC_NONTHEMED_COLOR(brandingPurple,     "#808080", "#808080")
    DECLARE_QGC_NONTHEMED_COLOR(brandingBlue,       "#808080", "#808080")
    DECLARE_QGC_NONTHEMED_COLOR(toolStripFGColor,   "#707070", "#FFFFFF")

    // Map widget and survey colors in monochrome
    DECLARE_QGC_SINGLE_COLOR(mapWidgetBorderLight,          "#FFFFFF")
    DECLARE_QGC_SINGLE_COLOR(mapWidgetBorderDark,           "#0D0D0D")
    DECLARE_QGC_SINGLE_COLOR(mapMissionTrajectory,          "#9A9A9A")
    DECLARE_QGC_SINGLE_COLOR(surveyPolygonInterior,         "#7F7F7F")
    DECLARE_QGC_SINGLE_COLOR(surveyPolygonTerrainCollision, "#0D0D0D")
}

void QGCPalette::setColorGroupEnabled(bool enabled)
{
    _colorGroupEnabled = enabled;
    emit paletteChanged();
}

void QGCPalette::setGlobalTheme(Theme newTheme)
{
    // Mobile build does not have themes
    if (_theme != newTheme) {
        _theme = newTheme;
        _signalPaletteChangeToAll();
    }
}

void QGCPalette::_signalPaletteChangeToAll()
{
    // Notify all objects of the new theme
    for (QGCPalette *palette : std::as_const(_paletteObjects)) {
        palette->_signalPaletteChanged();
    }
}

void QGCPalette::_signalPaletteChanged()
{
    emit paletteChanged();
}
