# BluGC UI Navigation Guide

## Table of Contents
1. [Project Structure Overview](#project-structure-overview)
2. [Main UI Areas](#main-ui-areas)
3. [Navigation by Feature](#navigation-by-feature)
4. [File Organization](#file-organization)
5. [Common UI Modifications](#common-ui-modifications)
6. [Quick Reference](#quick-reference)

## Project Structure Overview

BluGC follows a modular architecture where UI components are organized by functionality:

```
src/
├── UI/                     # Main application windows and global UI
├── FlightDisplay/          # Flight interface and controls
├── QmlControls/           # Reusable UI components
├── FlightMap/             # Map-related UI components
├── AnalyzeView/           # Data analysis interface
├── Vehicle/               # Vehicle-specific UI elements
├── Settings/              # Configuration interfaces
└── AutoPilotPlugins/      # Vehicle-specific settings
```

## Main UI Areas

### 1. Application Shell (`src/UI/`)
**What it contains:** Main window, global navigation, toolbar structure
**When to modify:** Changing overall app layout, adding new main views, modifying global toolbar

**Key files:**
- `MainWindow.qml` - Root application window and view switching
- `toolbar/` - Status indicators and main toolbar elements
- `AppSettings/` - Application settings panels

### 2. Flight Display (`src/FlightDisplay/`)
**What it contains:** Main flight interface, vehicle controls, flight actions
**When to modify:** Changing flight interface, adding flight controls, modifying vehicle interaction

**Key areas:**
- `FlyView.qml` - Main flight view layout
- `FlyViewMap.qml` - Flight map display
- `FlyViewVideo.qml` - Video streaming interface
- `MultiVehicleList.qml` - Multi-vehicle management
- `GuidedActions*.qml` - Flight action buttons (Takeoff, Land, RTL, etc.)

### 3. Reusable Controls (`src/QmlControls/`)
**What it contains:** Custom buttons, input fields, displays, common UI patterns
**When to modify:** Creating new UI components, modifying existing control behavior

**Important components:**
- `QGCButton.qml` - Standard button styling
- `ToolStrip*.qml` - Toolbar components
- `InstrumentValue*.qml` - Telemetry displays
- `*Editor.qml` - Various configuration editors

### 4. Map Interface (`src/FlightMap/`)
**What it contains:** Map display, vehicle markers, mission visualization
**When to modify:** Changing map appearance, adding map overlays, modifying vehicle display on map

### 5. Analysis Interface (`src/AnalyzeView/`)
**What it contains:** Data analysis, log viewing, system health monitoring
**When to modify:** Adding analysis tools, modifying data visualization

## Navigation by Feature

### Multi-Vehicle Management
**Primary locations:**
- `src/UI/toolbar/MultiVehicleSelector.qml` - Vehicle switching dropdown
- `src/FlightDisplay/MultiVehicleList.qml` - Vehicle list display
- `src/FlightDisplay/FlyView.qml` - Main multi-vehicle interface

**Related files:**
- `src/QmlControls/VehicleSummaryRow.qml` - Individual vehicle status
- `src/Vehicle/` - Vehicle-specific logic and UI

### Flight Controls and Actions
**Primary locations:**
- `src/FlightDisplay/GuidedActions*.qml` - Flight action buttons
- `src/FlightDisplay/FlyViewToolStrip.qml` - Flight tool strip
- `src/FlightDisplay/FlyViewToolBar.qml` - Flight toolbar

**Button locations:**
- Takeoff: `GuidedActionTakeoff.qml`
- Land: `GuidedActionLand.qml`
- RTL: `GuidedActionRTL.qml`
- Pause: `GuidedActionPause.qml`

### Status Indicators
**Primary locations:**
- `src/UI/toolbar/` - All status indicators
  - `BatteryIndicator.qml` - Battery status
  - `GPSIndicator.qml` - GPS status
  - `LinkIndicator.qml` - Connection status
  - `ArmedIndicator.qml` - Armed/disarmed status
  - `FlightModeIndicator.qml` - Current flight mode

### Video Display
**Primary locations:**
- `src/FlightDisplay/FlyViewVideo.qml` - Main video interface
- `src/FlightDisplay/FlightDisplayView*.qml` - Video backend implementations
- `src/VideoManager/` - Video streaming logic

### Settings and Configuration
**Primary locations:**
- `src/UI/AppSettings/` - Application settings
  - `GeneralSettings.qml` - General preferences
  - `LinkSettings.qml` - Communication settings
  - `VideoSettings.qml` - Video configuration
  - `MapSettings.qml` - Map preferences

### Mission Planning
**Primary locations:**
- `src/QmlControls/PlanView.qml` - Mission planning interface
- `src/QmlControls/MissionItem*.qml` - Mission item editors
- `src/QmlControls/SimpleItemEditor.qml` - Basic mission item editor

## File Organization

### Naming Conventions
- **Views:** End with `View.qml` (e.g., `FlyView.qml`)
- **Editors:** End with `Editor.qml` (e.g., `MissionItemEditor.qml`)
- **Indicators:** End with `Indicator.qml` (e.g., `BatteryIndicator.qml`)
- **Actions:** Start with `Guided` for flight actions (e.g., `GuidedActionTakeoff.qml`)
- **Controls:** Descriptive names (e.g., `QGCButton.qml`, `ToolStrip.qml`)

### Directory Purpose
- **UI/**: Global application structure
- **FlightDisplay/**: Active flight operations
- **QmlControls/**: Reusable components
- **AnalyzeView/**: Post-flight analysis
- **Settings/**: Configuration backends
- **Vehicle/**: Vehicle-specific implementations

## Common UI Modifications

### Changing Button Appearance
**Location:** `src/QmlControls/QGCButton.qml` or specific button files
**Affects:** All buttons using that component

### Modifying Status Indicators
**Location:** `src/UI/toolbar/[IndicatorName]Indicator.qml`
**Affects:** Specific indicator in the toolbar

### Customizing Flight Interface
**Location:** `src/FlightDisplay/FlyView.qml`
**Affects:** Main flight display layout

### Adding New Toolbar Elements
**Location:** `src/UI/toolbar/` (create new file) + `src/QmlControls/FlyViewToolBar.qml` (add reference)
**Affects:** Main toolbar

### Modifying Multi-Vehicle Display
**Location:** `src/FlightDisplay/MultiVehicleList.qml` and `src/UI/toolbar/MultiVehicleSelector.qml`
**Affects:** How multiple vehicles are shown and selected

### Changing Map Display
**Location:** `src/FlightMap/` and `src/FlightDisplay/FlyViewMap.qml`
**Affects:** Map appearance and vehicle markers

### Customizing Video Interface
**Location:** `src/FlightDisplay/FlyViewVideo.qml`
**Affects:** Video display size, position, and controls

### Modifying Settings Panels
**Location:** `src/UI/AppSettings/[SettingName]Settings.qml`
**Affects:** Specific settings category

## Quick Reference

### Want to change...

**Main window layout?**
→ `src/UI/MainWindow.qml`

**Flight interface layout?**
→ `src/FlightDisplay/FlyView.qml`

**Takeoff button?**
→ `src/FlightDisplay/GuidedActionTakeoff.qml`

**Battery indicator?**
→ `src/UI/toolbar/BatteryIndicator.qml`

**Vehicle selection?**
→ `src/UI/toolbar/MultiVehicleSelector.qml`

**Video display?**
→ `src/FlightDisplay/FlyViewVideo.qml`

**Map appearance?**
→ `src/FlightDisplay/FlyViewMap.qml`

**Button styling?**
→ `src/QmlControls/QGCButton.qml`

**Toolbar layout?**
→ `src/QmlControls/FlyViewToolBar.qml`

**Settings panels?**
→ `src/UI/AppSettings/[Category]Settings.qml`

**Mission planning?**
→ `src/QmlControls/PlanView.qml`

**Data analysis?**
→ `src/AnalyzeView/`

### File Relationships

**MainWindow.qml** loads → **FlyView.qml** → contains → **FlyViewMap.qml**, **FlyViewVideo.qml**, **FlyViewToolBar.qml**

**FlyViewToolBar.qml** contains → **Various indicators** from `src/UI/toolbar/`

**ToolStrip components** use → **ToolStripAction** components → which use **QGCButton** styling

**Settings panels** in `AppSettings/` are loaded by → **AppSettings.qml** → which is accessed from **MainWindow.qml**

### Build System Integration

After modifying UI files:
1. Files are automatically included in build (QML files)
2. New files need to be added to `CMakeLists.txt` in respective directories
3. Rebuild project to see changes
4. Use Qt Creator's QML preview for rapid iteration

### Testing Your Changes

1. **Modify the target file** based on this guide
2. **Build the project** (Ctrl+B in Qt Creator)
3. **Run BluGC** to see changes
4. **Use QML debugger** if issues arise

This guide focuses on navigation and understanding rather than implementation details. Use it to quickly locate the files you need to modify for specific UI changes in BluGC.
