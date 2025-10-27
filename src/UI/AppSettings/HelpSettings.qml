/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick
import QtQuick.Layouts

import QGroundControl
import QGroundControl.Controls



Rectangle {
    color:          qgcPal.window
    anchors.fill:   parent

    readonly property real _margins: ScreenTools.defaultFontPixelHeight

    QGCPalette { id: qgcPal; colorGroupEnabled: true }

    QGCFlickable {
        anchors.margins:    _margins
        anchors.fill:       parent
        contentWidth:       aboutColumn.width
        contentHeight:      aboutColumn.height
        clip:               true

        Column {
            id: aboutColumn
            width: parent.width - (_margins * 2)
            spacing: ScreenTools.defaultFontPixelHeight

            QGCLabel {
                text: qsTr("BLUGC – Autonomous UAV Software")
                font.pointSize: ScreenTools.largeFontPointSize
                font.bold: true
            }

            GridLayout {
                width: parent.width
                columns: 2
                columnSpacing: ScreenTools.defaultFontPixelWidth * 2
                rowSpacing: ScreenTools.defaultFontPixelHeight * 0.5

                QGCLabel { text: qsTr("Version:"); font.bold: true }
                QGCLabel { text: qsTr("v1.0") }

                QGCLabel { text: qsTr("Author:"); font.bold: true }
                QGCLabel { text: qsTr("Blubit Solutions") }

                QGCLabel { text: qsTr("Team:"); font.bold: true }
                QGCLabel { text: qsTr("Latency Zero") }

                QGCLabel { text: qsTr("Date:"); font.bold: true }
                QGCLabel { text: qsTr("27/10/2025") }
            }

            QGCLabel {
                text: qsTr("About")
                font.pointSize: ScreenTools.mediumFontPointSize
                font.bold: true
            }

            Text {
                width: parent.width
                wrapMode: Text.WordWrap
                color: qgcPal.text
                font.family: ScreenTools.normalFontFamily
                font.pointSize: ScreenTools.defaultFontPointSize
                text: "BLUGC is a fully autonomous UAV software platform developed by Blubit Solutions for Team Latency Zero to enable intelligent, self-managing drone operations with minimal human intervention. The software provides end-to-end automation for mission planning, execution, monitoring, and data management, combining AI-driven decision-making, real-time telemetry analysis, and dynamic mission adaptation. It generates optimized flight paths and waypoints, continuously monitors UAV status and sensor inputs, and autonomously adjusts missions in-flight, including rerouting UAVs and reallocating tasks among multiple drones. BLUGC features a modular architecture, supporting multi-UAV coordination, optional specialized modules for payload delivery, surveillance, mapping, precision agriculture, and object tracking, while incorporating advanced safety and reliability protocols such as obstacle avoidance, fail-safe mechanisms, emergency landing procedures, and mission continuity safeguards. By providing a comprehensive autonomous operational framework, BLUGC empowers Team Latency Zero to conduct complex UAV missions efficiently, safely, and consistently, significantly reducing human workload while maximizing operational effectiveness across diverse applications."
            }
        }
    }
}
