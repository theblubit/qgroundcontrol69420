# Complete BluGC UI Editing Guide

## Table of Contents
1. [Overview](#overview)
2. [Architecture](#architecture)
3. [Key UI Components](#key-ui-components)
4. [Development Environment](#development-environment)
5. [QML Basics for BluGC](#qml-basics-for-blugc)
6. [Main UI Structure](#main-ui-structure)
7. [Flight Display Interface](#flight-display-interface)
8. [Multi-Vehicle Management](#multi-vehicle-management)
9. [Toolbar and Indicators](#toolbar-and-indicators)
10. [Custom Controls](#custom-controls)
11. [Styling and Theming](#styling-and-theming)
12. [Map Interface](#map-interface)
13. [Settings and Configuration](#settings-and-configuration)
14. [Adding New UI Components](#adding-new-ui-components)
15. [Common Modifications](#common-modifications)
16. [Best Practices](#best-practices)
17. [Debugging UI Issues](#debugging-ui-issues)
18. [Build and Deploy](#build-and-deploy)

## Overview

BluGC is a fork of QGroundControl designed for managing multiple drone instances via wireless connections. The UI is built using Qt/QML with a modular architecture that separates concerns between flight control, vehicle management, and user interface components.

### Key Technologies
- **Qt 6.8.3**: Core framework
- **QML**: Declarative UI language
- **C++**: Backend logic and controllers
- **JavaScript**: UI logic and interactions

## Architecture

### Directory Structure
```
src/
├── UI/                     # Main UI components
│   ├── MainWindow.qml      # Root application window
│   ├── toolbar/            # Status indicators and controls
│   └── AppSettings/        # Settings panels
├── FlightDisplay/          # Flight interface components
├── QmlControls/           # Reusable UI controls
├── FlightMap/             # Map-related components
├── AnalyzeView/           # Data analysis interface
└── Vehicle/               # Vehicle-specific logic
```

### Component Hierarchy
```
MainWindow.qml
├── FlyView.qml (Flight Display)
├── PlanView.qml (Mission Planning)
├── AnalyzeView.qml (Data Analysis)
└── AppSettings.qml (Settings)
```

## Key UI Components

### 1. Main Window (`src/UI/MainWindow.qml`)
The root application window that manages:
- Global properties and state
- View switching
- First-run prompts
- Global actions and signals

### 2. Flight Display (`src/FlightDisplay/`)
Core flight interface components:
- `FlyView.qml`: Main flight view
- `FlyViewMap.qml`: Flight map display
- `FlyViewVideo.qml`: Video streaming
- `GuidedActionsController.qml`: Flight actions
- `MultiVehicleList.qml`: Vehicle management

### 3. QML Controls (`src/QmlControls/`)
Reusable UI components:
- `QGCButton.qml`: Standard buttons
- `QGCTextField.qml`: Text input fields
- `ToolStrip.qml`: Tool strips
- `InstrumentValueGrid.qml`: Telemetry displays

## Development Environment

### Prerequisites
- Qt 6.8.3 or later
- Qt Creator (recommended IDE)
- CMake
- C++ compiler (GCC/Clang/MSVC)

### Setup
1. Install Qt with QML modules
2. Clone BluGC repository
3. Open `CMakeLists.txt` in Qt Creator
4. Configure build settings
5. Build and run

### Live Reload
Enable QML live reload for faster development:
```bash
export QML_IMPORT_TRACE=1
export QT_QUICK_CONTROLS_STYLE=Material
```

## QML Basics for BluGC

### Component Structure
```qml
import QtQuick
import QtQuick.Controls
import QGroundControl
import QGroundControl.Controls

Rectangle {
    id: root
    width: 200
    height: 100
    
    property string customText: "Hello"
    property color backgroundColor: qgcPal.window
    
    QGCLabel {
        text: root.customText
        anchors.centerIn: parent
    }
}
```

### Common Imports
```qml
import QtQuick                    // Core QML types
import QtQuick.Controls          // UI controls
import QtQuick.Layouts           // Layout managers
import QGroundControl            // Core QGC functionality
import QGroundControl.Controls   // Custom QGC controls
import QGroundControl.FactControls // Parameter controls
```

### Property Bindings
```qml
Rectangle {
    color: vehicle.armed ? "red" : "green"
    opacity: vehicle.connected ? 1.0 : 0.5
    visible: QGroundControl.multiVehicleManager.vehicles.count > 0
}
```

## Main UI Structure

### MainWindow.qml Key Sections

#### Global Properties
```qml
QtObject {
    id: globals
    readonly property var activeVehicle: QGroundControl.multiVehicleManager.activeVehicle
    readonly property real defaultTextHeight: ScreenTools.defaultFontPixelHeight
    property int validationErrorCount: 0
}
```

#### View Management
```qml
StackView {
    id: mainStack
    anchors.fill: parent
    
    Component {
        id: flyViewComponent
        FlyView { }
    }
    
    Component {
        id: planViewComponent  
        PlanView { }
    }
}
```

#### Toolbar Integration
```qml
FlyViewToolBar {
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.right: parent.right
    height: ScreenTools.toolbarHeight
}
```

## Flight Display Interface

### FlyView.qml Structure
```qml
Item {
    id: root
    
    property var planController: _planController
    property var guidedController: _guidedController
    
    // Map display
    FlyViewMap {
        anchors.fill: parent
        planController: root.planController
        guidedController: root.guidedController
    }
    
    // Video overlay
    FlyViewVideo {
        anchors.top: parent.top
        anchors.right: parent.right
        width: ScreenTools.defaultFontPixelWidth * 30
        height: ScreenTools.defaultFontPixelHeight * 20
    }
    
    // Instrument panel
    FlyViewInstrumentPanel {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: ScreenTools.defaultFontPixelWidth
    }
}
```

### Adding Custom Flight Display Elements
```qml
// Custom telemetry display
Rectangle {
    id: customTelemetry
    width: 200
    height: 100
    color: qgcPal.window
    border.color: qgcPal.text
    
    Column {
        anchors.centerIn: parent
        spacing: 5
        
        QGCLabel {
            text: "Altitude: " + (globals.activeVehicle ? globals.activeVehicle.altitudeRelative.valueString : "N/A")
        }
        
        QGCLabel {
            text: "Speed: " + (globals.activeVehicle ? globals.activeVehicle.groundSpeed.valueString : "N/A")
        }
    }
}
```

## Multi-Vehicle Management

### MultiVehicleSelector.qml Enhancement
```qml
RowLayout {
    spacing: 10
    
    Repeater {
        model: QGroundControl.multiVehicleManager.vehicles
        
        Rectangle {
            width: 60
            height: 40
            color: modelData === globals.activeVehicle ? qgcPal.buttonHighlight : qgcPal.button
            border.color: qgcPal.text
            
            QGCLabel {
                text: "V" + modelData.id
                anchors.centerIn: parent
                color: modelData.armed ? "red" : qgcPal.text
            }
            
            MouseArea {
                anchors.fill: parent
                onClicked: QGroundControl.multiVehicleManager.activeVehicle = modelData
            }
        }
    }
}
```

### Multi-Vehicle Status Grid
```qml
GridLayout {
    columns: 3
    columnSpacing: 10
    rowSpacing: 5
    
    Repeater {
        model: QGroundControl.multiVehicleManager.vehicles
        
        Rectangle {
            Layout.preferredWidth: 150
            Layout.preferredHeight: 100
            color: qgcPal.window
            border.color: modelData.connectionLost ? "red" : "green"
            
            Column {
                anchors.centerIn: parent
                spacing: 5
                
                QGCLabel {
                    text: "Vehicle " + modelData.id
                    font.bold: true
                }
                
                QGCLabel {
                    text: "Battery: " + modelData.battery.percentRemaining.valueString + "%"
                    color: modelData.battery.percentRemaining.value < 20 ? "red" : qgcPal.text
                }
                
                QGCLabel {
                    text: modelData.flightMode
                }
                
                QGCLabel {
                    text: modelData.armed ? "ARMED" : "DISARMED"
                    color: modelData.armed ? "red" : "green"
                }
            }
        }
    }
}
```

## Toolbar and Indicators

### Custom Indicator Creation
```qml
// CustomIndicator.qml
import QtQuick
import QtQuick.Controls
import QGroundControl
import QGroundControl.Controls

Rectangle {
    id: root
    width: ScreenTools.defaultFontPixelWidth * 8
    height: ScreenTools.defaultFontPixelHeight * 2
    color: qgcPal.window
    border.color: qgcPal.text
    
    property var vehicle: globals.activeVehicle
    property string indicatorText: "N/A"
    property color indicatorColor: qgcPal.text
    
    QGCLabel {
        text: root.indicatorText
        color: root.indicatorColor
        anchors.centerIn: parent
        font.pointSize: ScreenTools.smallFontPointSize
    }
    
    MouseArea {
        anchors.fill: parent
        onClicked: mainWindow.showIndicatorDrawer(indicatorDrawer, root)
    }
    
    Component {
        id: indicatorDrawer
        
        ToolIndicatorPage {
            contentComponent: Component {
                Column {
                    spacing: ScreenTools.defaultFontPixelWidth
                    
                    QGCLabel {
                        text: "Custom Indicator Details"
                        font.pointSize: ScreenTools.mediumFontPointSize
                    }
                    
                    // Add custom content here
                }
            }
        }
    }
}
```

### Adding Indicator to Toolbar
```qml
// In FlyViewToolBar.qml or similar
RowLayout {
    // Existing indicators...
    
    CustomIndicator {
        vehicle: globals.activeVehicle
        indicatorText: vehicle ? "CONN" : "DISC"
        indicatorColor: vehicle && vehicle.connectionLost ? "red" : "green"
    }
}
```

## Custom Controls

### Custom Button Component
```qml
// CustomButton.qml
import QtQuick
import QtQuick.Controls
import QGroundControl.Controls

Rectangle {
    id: root
    width: 100
    height: 40
    radius: 5
    
    property string text: ""
    property color backgroundColor: qgcPal.button
    property color textColor: qgcPal.buttonText
    property color hoverColor: qgcPal.buttonHighlight
    property bool enabled: true
    
    signal clicked()
    
    color: mouseArea.containsMouse && enabled ? hoverColor : backgroundColor
    opacity: enabled ? 1.0 : 0.5
    
    QGCLabel {
        text: root.text
        color: root.textColor
        anchors.centerIn: parent
    }
    
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        enabled: root.enabled
        onClicked: root.clicked()
    }
}
```

### Custom Input Field
```qml
// CustomTextField.qml
import QtQuick
import QtQuick.Controls
import QGroundControl.Controls

Rectangle {
    id: root
    width: 200
    height: 30
    color: qgcPal.textField
    border.color: textField.activeFocus ? qgcPal.accent : qgcPal.text
    
    property alias text: textField.text
    property alias placeholderText: textField.placeholderText
    property bool isValid: true
    
    TextField {
        id: textField
        anchors.fill: parent
        anchors.margins: 2
        background: null
        color: qgcPal.textFieldText
        
        onTextChanged: {
            // Add validation logic
            root.isValid = text.length > 0
        }
    }
    
    // Validation indicator
    Rectangle {
        width: 4
        height: parent.height
        anchors.right: parent.right
        color: root.isValid ? "green" : "red"
        visible: textField.text.length > 0
    }
}
```

## Styling and Theming

### QGC Palette Usage
```qml
Rectangle {
    color: qgcPal.window              // Background color
    border.color: qgcPal.text         // Text color
    
    QGCLabel {
        color: qgcPal.text            // Standard text
    }
    
    QGCButton {
        backgroundColor: qgcPal.button
        textColor: qgcPal.buttonText
    }
}
```

### Custom Color Scheme
```qml
// CustomPalette.qml
import QtQuick
import QGroundControl.Controls

QtObject {
    property color primaryColor: "#2196F3"
    property color secondaryColor: "#FFC107"
    property color errorColor: "#F44336"
    property color successColor: "#4CAF50"
    property color warningColor: "#FF9800"
    
    property color darkBackground: "#303030"
    property color lightBackground: "#FAFAFA"
    property color cardBackground: "#FFFFFF"
}
```

### Responsive Design
```qml
Rectangle {
    width: ScreenTools.isMobile ? parent.width : 400
    height: ScreenTools.isMobile ? 60 : 40
    
    QGCLabel {
        font.pointSize: ScreenTools.isMobile ? 
            ScreenTools.largeFontPointSize : 
            ScreenTools.defaultFontPointSize
    }
}
```

## Map Interface

### Custom Map Overlay
```qml
// CustomMapOverlay.qml
import QtQuick
import QtLocation
import QGroundControl.FlightMap

MapQuickItem {
    id: root
    
    property var vehicle
    property real vehicleLat: vehicle ? vehicle.coordinate.latitude : 0
    property real vehicleLon: vehicle ? vehicle.coordinate.longitude : 0
    
    coordinate: QtPositioning.coordinate(vehicleLat, vehicleLon)
    anchorPoint.x: sourceItem.width / 2
    anchorPoint.y: sourceItem.height / 2
    
    sourceItem: Rectangle {
        width: 40
        height: 40
        radius: 20
        color: vehicle && vehicle.armed ? "red" : "blue"
        border.color: "white"
        border.width: 2
        
        QGCLabel {
            text: vehicle ? vehicle.id : "?"
            color: "white"
            anchors.centerIn: parent
            font.bold: true
        }
    }
}
```

### Multi-Vehicle Map Display
```qml
// In FlyViewMap.qml
Repeater {
    model: QGroundControl.multiVehicleManager.vehicles
    
    CustomMapOverlay {
        vehicle: modelData
        visible: modelData.coordinate.isValid
    }
}
```

## Settings and Configuration

### Custom Settings Panel
```qml
// CustomSettingsPanel.qml
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QGroundControl.Controls

SettingsPage {
    id: root
    
    SettingsGroupLayout {
        Layout.fillWidth: true
        
        SettingsRowLayout {
            QGCLabel { text: "Custom Setting 1:" }
            QGCTextField {
                Layout.fillWidth: true
                text: QGroundControl.settingsManager.appSettings.customSetting1.value
                onEditingFinished: QGroundControl.settingsManager.appSettings.customSetting1.value = text
            }
        }
        
        SettingsRowLayout {
            QGCLabel { text: "Enable Feature:" }
            QGCCheckBox {
                checked: QGroundControl.settingsManager.appSettings.enableCustomFeature.value
                onClicked: QGroundControl.settingsManager.appSettings.enableCustomFeature.value = checked
            }
        }
        
        SettingsRowLayout {
            QGCLabel { text: "Refresh Rate:" }
            QGCSlider {
                Layout.fillWidth: true
                from: 1
                to: 60
                value: QGroundControl.settingsManager.appSettings.refreshRate.value
                onValueChanged: QGroundControl.settingsManager.appSettings.refreshRate.value = value
            }
        }
    }
}
```

## Adding New UI Components

### Step 1: Create Component File
```qml
// src/QmlControls/MyCustomComponent.qml
import QtQuick
import QtQuick.Controls
import QGroundControl.Controls

Rectangle {
    id: root
    width: 200
    height: 100
    
    property string title: "Custom Component"
    property var dataSource
    
    signal componentClicked()
    
    Column {
        anchors.centerIn: parent
        spacing: 10
        
        QGCLabel {
            text: root.title
            font.bold: true
        }
        
        QGCButton {
            text: "Action"
            onClicked: root.componentClicked()
        }
    }
}
```

### Step 2: Register in CMakeLists.txt
```cmake
# In src/QmlControls/CMakeLists.txt
set(QmlControlsSources
    # ... existing files ...
    MyCustomComponent.qml
)
```

### Step 3: Use in Other Components
```qml
import QGroundControl.Controls

MyCustomComponent {
    title: "Vehicle Status"
    dataSource: globals.activeVehicle
    onComponentClicked: {
        // Handle click
    }
}
```

## Common Modifications

### 1. Change Button Colors
```qml
QGCButton {
    backgroundColor: "#FF5722"  // Orange background
    textColor: "white"
    borderColor: "#D84315"
    
    // Or use conditional colors
    backgroundColor: vehicle.armed ? "red" : "green"
}
```

### 2. Add New Toolbar Indicator
```qml
// Create new indicator file
// Add to toolbar layout
// Implement click handler and drawer
```

### 3. Modify Flight Mode Display
```qml
Rectangle {
    color: {
        switch(vehicle.flightMode) {
            case "Manual": return "blue"
            case "Auto": return "green"
            case "RTL": return "orange"
            default: return qgcPal.button
        }
    }
    
    QGCLabel {
        text: vehicle.flightMode
        color: "white"
        anchors.centerIn: parent
    }
}
```

### 4. Custom Vehicle List
```qml
ListView {
    model: QGroundControl.multiVehicleManager.vehicles
    
    delegate: Rectangle {
        width: parent.width
        height: 60
        color: index % 2 ? qgcPal.alternateBase : qgcPal.base
        
        RowLayout {
            anchors.fill: parent
            anchors.margins: 10
            
            QGCLabel {
                text: "Vehicle " + modelData.id
                Layout.fillWidth: true
            }
            
            QGCLabel {
                text: modelData.flightMode
            }
            
            Rectangle {
                width: 20
                height: 20
                radius: 10
                color: modelData.armed ? "red" : "green"
            }
        }
        
        MouseArea {
            anchors.fill: parent
            onClicked: QGroundControl.multiVehicleManager.activeVehicle = modelData
        }
    }
}
```

## Best Practices

### 1. Component Organization
- Keep components small and focused
- Use descriptive names
- Group related components in folders
- Follow QGC naming conventions

### 2. Property Management
```qml
Rectangle {
    id: root
    
    // Public properties first
    property string title: ""
    property var vehicle
    
    // Private properties with underscore
    property var _controller: vehicle ? vehicle.controller : null
    property bool _isConnected: vehicle && !vehicle.connectionLost
    
    // Readonly properties
    readonly property bool isValid: _isConnected && vehicle.coordinate.isValid
}
```

### 3. Signal Handling
```qml
Connections {
    target: QGroundControl.multiVehicleManager
    
    function onActiveVehicleChanged(vehicle) {
        // Handle vehicle change
    }
    
    function onVehicleAdded(vehicle) {
        // Handle new vehicle
    }
}
```

### 4. Performance Optimization
```qml
// Use Loader for heavy components
Loader {
    active: visible && enabled
    sourceComponent: HeavyComponent { }
}

// Bind only when necessary
property bool expensiveProperty: visible ? calculateExpensiveValue() : false

// Use appropriate list models
ListView {
    model: QGroundControl.multiVehicleManager.vehicles
    cacheBuffer: 100  // Cache off-screen items
}
```

### 5. Error Handling
```qml
Rectangle {
    color: {
        try {
            return vehicle.battery.percentRemaining.value > 20 ? "green" : "red"
        } catch (error) {
            console.warn("Battery value error:", error)
            return qgcPal.button
        }
    }
}
```

## Debugging UI Issues

### 1. QML Debugging
```bash
# Enable QML debugging
export QML_IMPORT_TRACE=1
export QT_LOGGING_RULES="qt.qml.debug=true"

# Run with debugger
gdb ./QGroundControl
```

### 2. Visual Debugging
```qml
Rectangle {
    // Add debug borders
    border.color: "red"
    border.width: 1
    
    // Debug information
    Text {
        text: "Debug: " + parent.width + "x" + parent.height
        color: "red"
        anchors.top: parent.top
    }
}
```

### 3. Console Logging
```qml
Component.onCompleted: {
    console.log("Component loaded:", objectName)
}

onPropertyChanged: {
    console.log("Property changed:", property, "to:", value)
}
```

### 4. Common Issues
- **Binding loops**: Check for circular property dependencies
- **Performance**: Use profiler to identify bottlenecks
- **Memory leaks**: Ensure proper component cleanup
- **Layout issues**: Check anchor conflicts

## Build and Deploy

### 1. Development Build
```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make -j4
```

### 2. Release Build
```bash
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j4
```

### 3. QML Cache
```bash
# Pre-compile QML for better performance
qmlcachegen src/UI/MainWindow.qml
```

### 4. Testing Changes
1. Make UI modifications
2. Build project
3. Run and test
4. Use QML live reload for rapid iteration

### 5. Deployment
- Package with Qt deployment tools
- Include all QML files and resources
- Test on target platforms

## Advanced Topics

### 1. Custom C++ Integration
```cpp
// CustomController.h
class CustomController : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString status READ status NOTIFY statusChanged)
    
public:
    QString status() const { return _status; }
    
signals:
    void statusChanged();
    
private:
    QString _status;
};
```

### 2. Plugin Architecture
```qml
// Custom plugin integration
import MyCustomPlugin 1.0

MyCustomComponent {
    controller: MyCustomController { }
}
```

### 3. State Management
```qml
StateGroup {
    states: [
        State {
            name: "connected"
            when: vehicle && !vehicle.connectionLost
            PropertyChanges { target: statusIndicator; color: "green" }
        },
        State {
            name: "disconnected"
            when: !vehicle || vehicle.connectionLost
            PropertyChanges { target: statusIndicator; color: "red" }
        }
    ]
    
    transitions: [
        Transition {
            ColorAnimation { duration: 200 }
        }
    ]
}
```

This guide provides a comprehensive foundation for editing BluGC's UI. Start with simple modifications and gradually work toward more complex customizations as you become familiar with the codebase structure and QML patterns used throughout the application.
