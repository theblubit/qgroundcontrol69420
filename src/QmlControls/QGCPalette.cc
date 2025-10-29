/*  */ /****************************************************************************
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

#include <QtCore/QDebug>

#include "QGCCorePlugin.h"

QList<QGCPalette*> QGCPalette::_paletteObjects;

QGCPalette::Theme QGCPalette::_theme = QGCPalette::Dark;

QMap<int, QMap<int, QMap<QString, QColor>>> QGCPalette::_colorInfoMap;

QStringList QGCPalette::_colors;

QGCPalette::QGCPalette(QObject* parent) : QObject(parent), _colorGroupEnabled(true) {
    if (_colorInfoMap.isEmpty()) {
        _buildMap();
    }

    // We have to keep track of all QGCPalette objects in the system so we can signal theme change to all of them
    _paletteObjects += this;
}

QGCPalette::~QGCPalette() {
    bool fSuccess = _paletteObjects.removeOne(this);
    if (!fSuccess) {
        qWarning() << "Internal error";
    }
}

void QGCPalette::_buildMap() {

    //                                      Light                 Dark
    //                                      Disabled   Enabled    Disabled   Enabled
    DECLARE_QGC_COLOR(window, "#ffffff", "#ffffff", "#000000", "#000000")
    DECLARE_QGC_COLOR(windowShadeLight, "#f0f0f0", "#f0f0f0", "#1a1a1a", "#1a1a1a")
    DECLARE_QGC_COLOR(windowShade, "#e0e0e0", "#e0e0e0", "#333333", "#333333")
    DECLARE_QGC_COLOR(windowShadeDark, "#d0d0d0", "#d0d0d0", "#4d4d4d", "#4d4d4d")
    DECLARE_QGC_COLOR(text, "#000000", "#000000", "#ffffff", "#ffffff")
    DECLARE_QGC_COLOR(windowTransparentText, "#000000", "#000000", "#ffffff", "#ffffff")
    DECLARE_QGC_COLOR(warningText, "#000000", "#000000", "#ffffff", "#ffffff")
    DECLARE_QGC_COLOR(button, "#4a5d23", "#3e4f1e", "#4a5d23", "#5a6d33")
    DECLARE_QGC_COLOR(buttonBorder, "#2d3a14", "#2d3a14", "#6a7d43", "#6a7d43")
    DECLARE_QGC_COLOR(buttonText, "#ffffff", "#ffffff", "#ffffff", "#ffffff")
    DECLARE_QGC_COLOR(buttonHighlight, "#5a6d33", "#6a7d43", "#6a7d43", "#7a8d53")
    DECLARE_QGC_COLOR(buttonHighlightText, "#ffffff", "#ffffff", "#ffffff", "#ffffff")
    DECLARE_QGC_COLOR(primaryButton, "#3e4f1e", "#2d3a14", "#5a6d33", "#6a7d43")
    DECLARE_QGC_COLOR(primaryButtonText, "#ffffff", "#ffffff", "#ffffff", "#ffffff")
    DECLARE_QGC_COLOR(textField, "#ffffff", "#ffffff", "#1a1a1a", "#1a1a1a")
    DECLARE_QGC_COLOR(textFieldText, "#000000", "#000000", "#ffffff", "#ffffff")
    DECLARE_QGC_COLOR(mapButton, "#4a5d23", "#3e4f1e", "#5a6d33", "#6a7d43")
    DECLARE_QGC_COLOR(mapButtonHighlight, "#5a6d33", "#6a7d43", "#6a7d43", "#7a8d53")
    DECLARE_QGC_COLOR(mapIndicator, "#4a5d23", "#3e4f1e", "#5a6d33", "#6a7d43")
    DECLARE_QGC_COLOR(mapIndicatorChild, "#4a5d23", "#3e4f1e", "#5a6d33", "#6a7d43")
    DECLARE_QGC_COLOR(colorGreen, "#3e4f1e", "#2d3a14", "#5a6d33", "#6a7d43")
    DECLARE_QGC_COLOR(colorYellow, "#808080", "#808080", "#b0b0b0", "#b0b0b0")
    DECLARE_QGC_COLOR(colorYellowGreen, "#4a5d23", "#3e4f1e", "#5a6d33", "#6a7d43")
    DECLARE_QGC_COLOR(colorOrange, "#808080", "#808080", "#b0b0b0", "#b0b0b0")
    DECLARE_QGC_COLOR(colorRed, "#404040", "#404040", "#d0d0d0", "#d0d0d0")
    DECLARE_QGC_COLOR(colorGrey, "#808080", "#808080", "#b0b0b0", "#b0b0b0")
    DECLARE_QGC_COLOR(colorBlue, "#808080", "#808080", "#b0b0b0", "#b0b0b0")
    DECLARE_QGC_COLOR(alertBackground, "#f0f0f0", "#f0f0f0", "#1a1a1a", "#1a1a1a")
    DECLARE_QGC_COLOR(alertBorder, "#2d3a14", "#2d3a14", "#6a7d43", "#6a7d43")
    DECLARE_QGC_COLOR(alertText, "#2d3a14", "#2d3a14", "#6a7d43", "#6a7d43")
    DECLARE_QGC_COLOR(missionItemEditor, "#4a5d23", "#3e4f1e", "#5a6d33", "#6a7d43")
    DECLARE_QGC_COLOR(toolStripHoverColor, "#5a6d33", "#6a7d43", "#6a7d43", "#7a8d53")
    DECLARE_QGC_COLOR(statusFailedText, "#000000", "#000000", "#ffffff", "#ffffff")
    DECLARE_QGC_COLOR(statusPassedText, "#2d3a14", "#2d3a14", "#6a7d43", "#6a7d43")
    DECLARE_QGC_COLOR(statusPendingText, "#808080", "#808080", "#b0b0b0", "#b0b0b0")
    DECLARE_QGC_COLOR(toolbarBackground, "#f0f0f0", "#e0e0e0", "#1a1a1a", "#333333")
    DECLARE_QGC_COLOR(groupBorder, "#2d3a14", "#2d3a14", "#6a7d43", "#6a7d43")

    // Colors not affecting by theming
    //                                              Disabled    Enabled
    DECLARE_QGC_NONTHEMED_COLOR(brandingPurple, "#4a5d23", "#2d3a14")
    DECLARE_QGC_NONTHEMED_COLOR(brandingBlue, "#4a5d23", "#2d3a14")
    DECLARE_QGC_NONTHEMED_COLOR(toolStripFGColor, "#ffffff", "#ffffff")

    // Colors not affecting by theming or enable/disable
    DECLARE_QGC_SINGLE_COLOR(mapWidgetBorderLight, "#2d3a14")
    DECLARE_QGC_SINGLE_COLOR(mapWidgetBorderDark, "#6a7d43")
    DECLARE_QGC_SINGLE_COLOR(mapMissionTrajectory, "#3e4f1e")
    DECLARE_QGC_SINGLE_COLOR(surveyPolygonInterior, "#5a6d33")
    DECLARE_QGC_SINGLE_COLOR(surveyPolygonTerrainCollision, "#2d3a14")

// Colors for UTM Adapter
#ifdef QGC_UTM_ADAPTER
    DECLARE_QGC_COLOR(switchUTMSP, "#5a6d33", "#5a6d33", "#4a5d23", "#4a5d23");
    DECLARE_QGC_COLOR(sliderUTMSP, "#3e4f1e", "#3e4f1e", "#5a6d33", "#5a6d33");
    DECLARE_QGC_COLOR(successNotifyUTMSP, "#2d3a14", "#2d3a14", "#6a7d43", "#6a7d43");
#endif
}

void QGCPalette::setColorGroupEnabled(bool enabled) {
    _colorGroupEnabled = enabled;
    emit paletteChanged();
}

void QGCPalette::setGlobalTheme(Theme newTheme) {
    // Mobile build does not have themes
    if (_theme != newTheme) {
        _theme = newTheme;
        _signalPaletteChangeToAll();
    }
}

void QGCPalette::_signalPaletteChangeToAll() {
    // Notify all objects of the new theme
    for (QGCPalette* palette : std::as_const(_paletteObjects)) {
        palette->_signalPaletteChanged();
    }
}

void QGCPalette::_signalPaletteChanged() { emit paletteChanged(); }
