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
    // reduce contrast by lightening blacks and dark greys, mute reds
    DECLARE_QGC_COLOR(window,               "#FFFBF2", "#FFFBF2", "#0D1112", "#0D1112")
    DECLARE_QGC_COLOR(windowTransparent,    "#CCFFFBF2", "#CCFFFBF2", "#CC0D1112", "#CC0D1112")
    DECLARE_QGC_COLOR(windowShadeLight,     "#DFE2DB", "#DFE2DB", "#2A2527", "#2A2527")
    DECLARE_QGC_COLOR(windowShade,          "#DFE2DB", "#DFE2DB", "#7F0D10", "#7F0D10")
    DECLARE_QGC_COLOR(windowShadeDark,      "#8F1A1A", "#8F1A1A", "#8F1A1A", "#7F0D10")
    DECLARE_QGC_COLOR(text,                 "#2A2527", "#2A2527", "#DFE2DB", "#FFFBF2")
    DECLARE_QGC_COLOR(windowTransparentText,"#2A2527", "#2A2527", "#DFE2DB", "#FFFBF2")
    DECLARE_QGC_COLOR(warningText,          "#8F1A1A", "#8F1A1A", "#FFFBF2", "#FFFBF2")
    DECLARE_QGC_COLOR(button,               "#FFFBF2", "#FFFBF2", "#7F0D10", "#8F1A1A")
    DECLARE_QGC_COLOR(buttonBorder,         "#DFE2DB", "#DFE2DB", "#7F0D10", "#7F0D10")
    DECLARE_QGC_COLOR(buttonText,           "#2A2527", "#2A2527", "#FFFBF2", "#FFFBF2")
    DECLARE_QGC_COLOR(buttonHighlight,      "#FFF1F1", "#FFF1F1", "#8F1A1A", "#7F0D10")
    DECLARE_QGC_COLOR(buttonHighlightText,  "#2A2527", "#FFFBF2", "#2A2527", "#FFFBF2")
    DECLARE_QGC_COLOR(primaryButton,        "#8F1A1A", "#7F0D10", "#7F0D10", "#8F1A1A")
    DECLARE_QGC_COLOR(primaryButtonText,    "#FFFBF2", "#FFFBF2", "#FFFBF2", "#FFFBF2")
    DECLARE_QGC_COLOR(textField,            "#FFFBF2", "#FFFBF2", "#2A2527", "#2A2527")
    DECLARE_QGC_COLOR(textFieldText,        "#2A2527", "#2A2527", "#DFE2DB", "#DFE2DB")
    DECLARE_QGC_COLOR(mapButton,            "#DFE2DB", "#2A2527", "#DFE2DB", "#2A2527")
    DECLARE_QGC_COLOR(mapButtonHighlight,   "#DFE2DB", "#8F1A1A", "#DFE2DB", "#8F1A1A")
    DECLARE_QGC_COLOR(mapIndicator,         "#7F0D10", "#8F1A1A", "#8F1A1A", "#8F1A1A")
    DECLARE_QGC_COLOR(mapIndicatorChild,    "#8F1A1A", "#7F0D10", "#7F0D10", "#7F0D10")
    DECLARE_QGC_COLOR(colorGreen,           "#DFE2DB", "#DFE2DB", "#8F1A1A", "#8F1A1A")
    DECLARE_QGC_COLOR(colorYellow,          "#DFE2DB", "#DFE2DB", "#7F0D10", "#7F0D10")
    DECLARE_QGC_COLOR(colorYellowGreen,     "#DFE2DB", "#DFE2DB", "#8F1A1A", "#8F1A1A")
    DECLARE_QGC_COLOR(colorOrange,          "#8F1A1A", "#8F1A1A", "#7F0D10", "#7F0D10")
    DECLARE_QGC_COLOR(colorRed,             "#8F1A1A", "#8F1A1A", "#B02A2A", "#B02A2A")
    DECLARE_QGC_COLOR(colorGrey,            "#808080", "#808080", "#2A2527", "#2A2527")
    DECLARE_QGC_COLOR(colorBlue,            "#7F0D10", "#7F0D10", "#7F0D10", "#7F0D10")
    DECLARE_QGC_COLOR(alertBackground,      "#EECC44", "#EECC44", "#EECC44", "#EECC44")
    DECLARE_QGC_COLOR(alertBorder,          "#808080", "#808080", "#808080", "#808080")
    DECLARE_QGC_COLOR(alertText,            "#000000", "#000000", "#000000", "#000000")
    DECLARE_QGC_COLOR(missionItemEditor,    "#DFE2DB", "#DFE2DB", "#2A2527", "#2A2527")
    DECLARE_QGC_COLOR(toolStripHoverColor,  "#DFE2DB", "#2A2527", "#DFE2DB", "#2A2527")
    DECLARE_QGC_COLOR(statusFailedText,     "#2A2527", "#2A2527", "#DFE2DB", "#FFFBF2")
    DECLARE_QGC_COLOR(statusPassedText,     "#2A2527", "#2A2527", "#DFE2DB", "#FFFBF2")
    DECLARE_QGC_COLOR(statusPendingText,    "#2A2527", "#2A2527", "#DFE2DB", "#FFFBF2")
    DECLARE_QGC_COLOR(toolbarBackground,    "#00FFFFFF", "#00FFFFFF", "#0A0A0A10", "#0A0A0A10")
    DECLARE_QGC_COLOR(toolbarDivider,       "#00000000", "#00000000", "#00000000", "#00000000")
    DECLARE_QGC_COLOR(groupBorder,          "#BBBBBB", "#BBBBBB", "#2A2527", "#2A2527")

    // Colors not affecting by theming
    //                                              Disabled    Enabled
    DECLARE_QGC_NONTHEMED_COLOR(brandingPurple,     "#8F1A1A", "#8F1A1A")
    DECLARE_QGC_NONTHEMED_COLOR(brandingBlue,       "#7F0D10", "#7F0D10")
    DECLARE_QGC_NONTHEMED_COLOR(toolStripFGColor,   "#707070", "#FFFBF2")

    // Colors not affecting by theming or enable/disable
    DECLARE_QGC_SINGLE_COLOR(mapWidgetBorderLight,          "#FFFBF2")
    DECLARE_QGC_SINGLE_COLOR(mapWidgetBorderDark,           "#0D1112")
    DECLARE_QGC_SINGLE_COLOR(mapMissionTrajectory,          "#8F1A1A")
    DECLARE_QGC_SINGLE_COLOR(surveyPolygonInterior,         "#7F0D10")
    DECLARE_QGC_SINGLE_COLOR(surveyPolygonTerrainCollision, "#0D1112")

// Colors for UTM Adapter
#ifdef QGC_UTM_ADAPTER
    DECLARE_QGC_COLOR(switchUTMSP,        "#b0e0e6", "#b0e0e6", "#b0e0e6", "#b0e0e6");
    DECLARE_QGC_COLOR(sliderUTMSP,        "#9370db", "#9370db", "#9370db", "#9370db");
    DECLARE_QGC_COLOR(successNotifyUTMSP, "#3cb371", "#3cb371", "#3cb371", "#3cb371");
#endif
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
