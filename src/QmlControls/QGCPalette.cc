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
    DECLARE_QGC_COLOR(window, "#ffffff", "#f5f5f5", "#222222", "#111111")
    DECLARE_QGC_COLOR(windowShadeLight, "#e0e0e0", "#cccccc", "#444444", "#333333")
    DECLARE_QGC_COLOR(windowShade, "#cccccc", "#bbbbbb", "#333333", "#222222")
    DECLARE_QGC_COLOR(windowShadeDark, "#bbbbbb", "#aaaaaa", "#222222", "#111111")
    DECLARE_QGC_COLOR(text, "#222222", "#111111", "#f5f5f5", "#ffffff")
    DECLARE_QGC_COLOR(warningText, "#c9184a", "#c9184a", "#c9184a", "#c9184a")
    DECLARE_QGC_COLOR(button, "#f5f5f5", "#e0e0e0", "#333333", "#222222")
    DECLARE_QGC_COLOR(buttonBorder, "#cccccc", "#bbbbbb", "#c9184a", "#c9184a")
    DECLARE_QGC_COLOR(buttonText, "#222222", "#111111", "#f5f5f5", "#ffffff")
    DECLARE_QGC_COLOR(buttonHighlight, "#bbbbbb", "#c9184a", "#bbbbbb", "#c9184a")
    DECLARE_QGC_COLOR(buttonHighlightText, "#111111", "#ffffff", "#111111", "#ffffff")
    DECLARE_QGC_COLOR(primaryButton, "#e0e0e0", "#c9184a", "#333333", "#c9184a")
    DECLARE_QGC_COLOR(primaryButtonText, "#111111", "#ffffff", "#f5f5f5", "#ffffff")
    DECLARE_QGC_COLOR(textField, "#ffffff", "#f5f5f5", "#222222", "#111111")
    DECLARE_QGC_COLOR(textFieldText, "#222222", "#111111", "#f5f5f5", "#ffffff")
    DECLARE_QGC_COLOR(mapButton, "#bbbbbb", "#c9184a", "#bbbbbb", "#c9184a")
    DECLARE_QGC_COLOR(mapButtonHighlight, "#c9184a", "#bbbbbb", "#c9184a", "#bbbbbb")
    DECLARE_QGC_COLOR(mapIndicator, "#bbbbbb", "#c9184a", "#bbbbbb", "#c9184a")
    DECLARE_QGC_COLOR(mapIndicatorChild, "#bbbbbb", "#c9184a", "#bbbbbb", "#c9184a")
    DECLARE_QGC_COLOR(colorGreen, "#bbbbbb", "#bbbbbb", "#bbbbbb", "#bbbbbb")
    DECLARE_QGC_COLOR(colorYellow, "#bbbbbb", "#bbbbbb", "#bbbbbb", "#bbbbbb")
    DECLARE_QGC_COLOR(colorYellowGreen, "#bbbbbb", "#bbbbbb", "#bbbbbb", "#bbbbbb")
    DECLARE_QGC_COLOR(colorOrange, "#bbbbbb", "#bbbbbb", "#bbbbbb", "#bbbbbb")
    DECLARE_QGC_COLOR(colorRed, "#c9184a", "#c9184a", "#c9184a", "#c9184a")
    DECLARE_QGC_COLOR(colorGrey, "#bbbbbb", "#bbbbbb", "#bbbbbb", "#bbbbbb")
    DECLARE_QGC_COLOR(colorBlue, "#bbbbbb", "#bbbbbb", "#bbbbbb", "#bbbbbb")
    DECLARE_QGC_COLOR(alertBackground, "#f5f5f5", "#f5f5f5", "#222222", "#222222")
    DECLARE_QGC_COLOR(alertBorder, "#c9184a", "#c9184a", "#c9184a", "#c9184a")
    DECLARE_QGC_COLOR(alertText, "#c9184a", "#c9184a", "#c9184a", "#c9184a")
    DECLARE_QGC_COLOR(missionItemEditor, "#bbbbbb", "#c9184a", "#bbbbbb", "#c9184a")
    DECLARE_QGC_COLOR(toolStripHoverColor, "#bbbbbb", "#c9184a", "#bbbbbb", "#c9184a")
    DECLARE_QGC_COLOR(statusFailedText, "#c9184a", "#c9184a", "#c9184a", "#c9184a")
    DECLARE_QGC_COLOR(statusPassedText, "#bbbbbb", "#bbbbbb", "#bbbbbb", "#bbbbbb")
    DECLARE_QGC_COLOR(statusPendingText, "#bbbbbb", "#bbbbbb", "#bbbbbb", "#bbbbbb")
    DECLARE_QGC_COLOR(toolbarBackground, "#f5f5f5", "#e0e0e0", "#222222", "#111111")
    DECLARE_QGC_COLOR(groupBorder, "#bbbbbb", "#bbbbbb", "#bbbbbb", "#bbbbbb")

    // Colors not affecting by theming
    //                                              Disabled    Enabled
    DECLARE_QGC_NONTHEMED_COLOR(brandingPurple, "#bbbbbb", "#bbbbbb")
    DECLARE_QGC_NONTHEMED_COLOR(brandingBlue, "#bbbbbb", "#bbbbbb")
    DECLARE_QGC_NONTHEMED_COLOR(toolStripFGColor, "#bbbbbb", "#bbbbbb")

    // Colors not affecting by theming or enable/disable
    DECLARE_QGC_SINGLE_COLOR(mapWidgetBorderLight, "#e0e0e0")
    DECLARE_QGC_SINGLE_COLOR(mapWidgetBorderDark, "#222222")
    DECLARE_QGC_SINGLE_COLOR(mapMissionTrajectory, "#c9184a")
    DECLARE_QGC_SINGLE_COLOR(surveyPolygonInterior, "#bbbbbb")
    DECLARE_QGC_SINGLE_COLOR(surveyPolygonTerrainCollision, "#c9184a")

// Colors for UTM Adapter
#ifdef QGC_UTM_ADAPTER
    DECLARE_QGC_COLOR(switchUTMSP, "#b0e0e6", "#b0e0e6", "#b0e0e6", "#b0e0e6");
    DECLARE_QGC_COLOR(sliderUTMSP, "#9370db", "#9370db", "#9370db", "#9370db");
    DECLARE_QGC_COLOR(successNotifyUTMSP, "#3cb371", "#3cb371", "#3cb371", "#3cb371");
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
