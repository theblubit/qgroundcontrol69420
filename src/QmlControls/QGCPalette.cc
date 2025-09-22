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
    DECLARE_QGC_COLOR(window, "#ffccd5", "#ffccd5", "#590d22", "#590d22")
    DECLARE_QGC_COLOR(windowShadeLight, "#ffb3c1", "#ffb3c1", "#ffb3c1", "#ffb3c1")
    DECLARE_QGC_COLOR(windowShade, "#ff8fa3", "#ff8fa3", "#ff8fa3", "#ff8fa3")
    DECLARE_QGC_COLOR(windowShadeDark, "#ff758f", "#ff758f", "#ff758f", "#ff758f")
    DECLARE_QGC_COLOR(text, "#a4133c", "#590d22", "#ffb3c1", "#fff0f3")
    DECLARE_QGC_COLOR(warningText, "#ff4d6d", "#ff4d6d", "#c9184a", "#c9184a")
    DECLARE_QGC_COLOR(button, "#ffccd5", "#ffccd5", "#a4133c", "#a4133c")
    DECLARE_QGC_COLOR(buttonBorder, "#ffccd5", "#ffb3c1", "#a4133c", "#ff4d6d")
    DECLARE_QGC_COLOR(buttonText, "#a4133c", "#590d22", "#ffb3c1", "#fff0f3")
    DECLARE_QGC_COLOR(buttonHighlight, "#ff8fa3", "#ff4d6d", "#a4133c", "#ff758f")
    DECLARE_QGC_COLOR(buttonHighlightText, "#590d22", "#fff0f3", "#590d22", "#ffccd5")
    DECLARE_QGC_COLOR(primaryButton, "#ff4d6d", "#ff758f", "#ff4d6d", "#ff758f")
    DECLARE_QGC_COLOR(primaryButtonText, "#590d22", "#800f2f", "#590d22", "#800f2f")
    DECLARE_QGC_COLOR(textField, "#ffccd5", "#ffccd5", "#a4133c", "#ffccd5")
    DECLARE_QGC_COLOR(textFieldText, "#800f2f", "#590d22", "#590d22", "#590d22")
    DECLARE_QGC_COLOR(mapButton, "#ff4d6d", "#590d22", "#ff4d6d", "#590d22")
    DECLARE_QGC_COLOR(mapButtonHighlight, "#ff4d6d", "#c9184a", "#ff4d6d", "#c9184a")
    DECLARE_QGC_COLOR(mapIndicator, "#ff4d6d", "#c9184a", "#ff4d6d", "#c9184a")
    DECLARE_QGC_COLOR(mapIndicatorChild, "#ff4d6d", "#a4133c", "#ff4d6d", "#a4133c")
    DECLARE_QGC_COLOR(colorGreen, "#cherry-blossom-pink", "#cherry-blossom-pink", "#cherry-blossom-pink", "#cherry-blossom-pink")
    DECLARE_QGC_COLOR(colorYellow, "#pink", "#pink", "#pink", "#pink")
    DECLARE_QGC_COLOR(colorYellowGreen, "#lavender-blush", "#lavender-blush", "#lavender-blush", "#lavender-blush")
    DECLARE_QGC_COLOR(colorOrange, "#rose-red", "#rose-red", "#rose-red", "#rose-red")
    DECLARE_QGC_COLOR(colorRed, "#c9184a", "#c9184a", "#ff4d6d", "#ff4d6d")
    DECLARE_QGC_COLOR(colorGrey, "#a4133c", "#a4133c", "#ffb3c1", "#ffb3c1")
    DECLARE_QGC_COLOR(colorBlue, "#amaranth-purple", "#amaranth-purple", "#amaranth-purple", "#amaranth-purple")
    DECLARE_QGC_COLOR(alertBackground, "#ffb3c1", "#ffb3c1", "#ffb3c1", "#ffb3c1")
    DECLARE_QGC_COLOR(alertBorder, "#a4133c", "#a4133c", "#a4133c", "#a4133c")
    DECLARE_QGC_COLOR(alertText, "#590d22", "#590d22", "#fff0f3", "#fff0f3")
    DECLARE_QGC_COLOR(missionItemEditor, "#ff4d6d", "#ffb3c1", "#ff4d6d", "#ff758f")
    DECLARE_QGC_COLOR(toolStripHoverColor, "#ff4d6d", "#a4133c", "#ff4d6d", "#ff758f")
    DECLARE_QGC_COLOR(statusFailedText, "#a4133c", "#590d22", "#ffb3c1", "#fff0f3")
    DECLARE_QGC_COLOR(statusPassedText, "#a4133c", "#590d22", "#ffb3c1", "#fff0f3")
    DECLARE_QGC_COLOR(statusPendingText, "#a4133c", "#590d22", "#ffb3c1", "#fff0f3")
    DECLARE_QGC_COLOR(toolbarBackground, "#ffccd5", "#ffccd5", "#590d22", "#590d22")
    DECLARE_QGC_COLOR(groupBorder, "#a4133c", "#a4133c", "#590d22", "#590d22")

    // Colors not affecting by theming
    //                                              Disabled    Enabled
    DECLARE_QGC_NONTHEMED_COLOR(brandingPurple, "#a4133c", "#a4133c")
    DECLARE_QGC_NONTHEMED_COLOR(brandingBlue, "#ff4d6d", "#ff758f")
    DECLARE_QGC_NONTHEMED_COLOR(toolStripFGColor, "#a4133c", "#fff0f3")

    // Colors not affecting by theming or enable/disable
    DECLARE_QGC_SINGLE_COLOR(mapWidgetBorderLight, "#fff0f3")
    DECLARE_QGC_SINGLE_COLOR(mapWidgetBorderDark, "#590d22")
    DECLARE_QGC_SINGLE_COLOR(mapMissionTrajectory, "#ff4d6d")
    DECLARE_QGC_SINGLE_COLOR(surveyPolygonInterior, "#ffb3c1")
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
