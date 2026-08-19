import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

ApplicationWindow {
    id: win
    visible: true
    width: 1040
    height: 760
    minimumWidth: 820
    minimumHeight: 620
    title: "Sexy S-Pen"
    color: palette.window

    SystemPalette { id: palette; colorGroup: SystemPalette.Active }
    property color ink: "#8b6cff"
    property color hot: "#ff6b9d"
    property color card: palette.base
    property bool pairing: false

    Timer { id: pairTimer; interval: 2200; onTriggered: { pairing = false; penController.pairPen() } }

    header: ToolBar {
        height: 78
        background: Rectangle { color: palette.window; border.color: palette.mid; border.width: 1 }
        RowLayout {
            anchors.fill: parent; anchors.leftMargin: 28; anchors.rightMargin: 26; spacing: 14
            Rectangle { width: 44; height: 44; radius: 14; color: ink
                Label { anchors.centerIn: parent; text: "✦"; color: "white"; font.pixelSize: 24 }
            }
            ColumnLayout { Layout.fillWidth: true; spacing: 0
                Label { text: "Sexy S-Pen"; color: palette.text; font.pixelSize: 24; font.weight: Font.DemiBold }
                Label { text: "Surface Linux · artist control centre"; color: palette.placeholderText; font.pixelSize: 12 }
            }
            Label { text: penController.bluetoothConnected ? "Connected" : "Ready to pair"; color: penController.bluetoothConnected ? "#28c76f" : palette.placeholderText }
            ToolButton { text: "◐"; font.pixelSize: 20; onClicked: win.color = win.color === palette.window ? palette.base : palette.window; ToolTip.visible: hovered; ToolTip.text: "Toggle appearance" }
            Button { text: "Save"; highlighted: true; onClicked: penController.save() }
        }
    }

    ScrollView {
        anchors.fill: parent; anchors.margins: 24; clip: true
        ColumnLayout {
            width: Math.max(win.width - 48, 770); spacing: 18

            Rectangle {
                Layout.fillWidth: true; height: 172; radius: 28; color: card; border.color: palette.mid; border.width: 1
                RowLayout { anchors.fill: parent; anchors.margins: 25; spacing: 24
                    Item { Layout.preferredWidth: 120; Layout.fillHeight: true
                        Rectangle { anchors.centerIn: parent; width: 82; height: 82; radius: 41; color: ink; opacity: 0.16
                            Rectangle { anchors.centerIn: parent; width: 60; height: 60; radius: 30; color: ink
                                Label { anchors.centerIn: parent; text: "✎"; color: "white"; font.pixelSize: 32 }
                            }
                            SequentialAnimation on scale { loops: Animation.Infinite; running: penController.bluetoothConnected; NumberAnimation { to: 1.08; duration: 1200; easing.type: Easing.InOutQuad }; NumberAnimation { to: 1.0; duration: 1200; easing.type: Easing.InOutQuad } }
                        }
                    }
                    ColumnLayout { Layout.fillWidth: true; spacing: 6
                        Label { text: pairing ? "Pairing flow ready" : penController.bluetoothConnected ? "Your pen is in the zone" : "Make the pen feel like magic"; color: palette.text; font.pixelSize: 23; font.weight: Font.DemiBold }
                        Label { text: penController.status; color: palette.placeholderText; Layout.fillWidth: true; elide: Text.ElideRight }
                        RowLayout { spacing: 8
                            CapabilityChip { label: "Pressure"; enabledState: penController.pressureAvailable }
                            CapabilityChip { label: "Tilt"; enabledState: penController.tiltAvailable }
                            CapabilityChip { label: "Hover"; enabledState: penController.hoverAvailable }
                        }
                    }
                    ColumnLayout { Layout.preferredWidth: 160; spacing: 5
                        Label { text: penController.batteryAvailable ? penController.batteryPercent + "%" : "—"; color: palette.text; font.pixelSize: 30; font.weight: Font.DemiBold; horizontalAlignment: Text.AlignRight; Layout.fillWidth: true }
                        Label { text: penController.batteryAvailable ? "live battery" : "battery unknown"; color: palette.placeholderText; horizontalAlignment: Text.AlignRight; Layout.fillWidth: true }
                        ProgressBar { Layout.fillWidth: true; from: 0; to: 100; value: penController.batteryAvailable ? penController.batteryPercent : 0; visible: penController.batteryAvailable }
                    }
                }
            }

            RowLayout { Layout.fillWidth: true; spacing: 18
                Button { Layout.fillWidth: true; text: pairing ? "Listening for pen…" : "Pair / reconnect pen"; enabled: !pairing; onClicked: { pairing = true; pairTimer.restart() } }
                Button { Layout.fillWidth: true; text: "Open calibration"; onClicked: penController.setStatus("Use Plasma Drawing Tablet calibration for four-point parallax correction") }
                Button { Layout.fillWidth: true; text: "Reset"; onClicked: penController.reset() }
            }

            RowLayout { Layout.fillWidth: true; spacing: 18
                ColumnLayout { Layout.fillWidth: true; spacing: 18
                    Card {
                        title: "Palm intelligence"; subtitle: "Keep your hand down. Keep your ideas moving."
                        SettingRow { title: "Reject touch near pen"; detail: "Stylus proximity"; checked: penController.disableOnStylus; onToggled: penController.disableOnStylus = checked }
                        SettingRow { title: "Reject palm contacts"; detail: "Surface IPTS"; checked: penController.disableOnPalm; onToggled: penController.disableOnPalm = checked }
                        RowLayout { Layout.fillWidth: true
                            Label { text: "Grace period"; color: palette.text; Layout.fillWidth: true }
                            Slider { from: 0; to: 3000; value: penController.gracePeriod; Layout.preferredWidth: 180; onMoved: penController.gracePeriod = Math.round(value) }
                            Label { text: penController.gracePeriod + " ms"; color: palette.placeholderText; Layout.preferredWidth: 58 }
                        }
                    }
                    Card {
                        title: "Artist feel"; subtitle: "Pressure, speed, and smoothing without the guesswork."
                        RowLayout { Layout.fillWidth: true
                            Label { text: "Tip threshold"; color: palette.text; Layout.fillWidth: true }
                            Slider { from: 0; to: 1; value: penController.tipThreshold; Layout.preferredWidth: 180; onMoved: penController.tipThreshold = value }
                            Label { text: Math.round(penController.tipThreshold * 100) + "%"; color: palette.placeholderText; Layout.preferredWidth: 42 }
                        }
                        RowLayout { Layout.fillWidth: true
                            Label { text: "Pressure curve"; color: palette.text; Layout.fillWidth: true }
                            ComboBox { model: ["soft", "linear", "firm"]; currentIndex: model.indexOf(penController.pressureCurve); onActivated: penController.pressureCurve = currentText }
                        }
                        RowLayout { Layout.fillWidth: true
                            Label { text: "Brush smoothing"; color: palette.text; Layout.fillWidth: true }
                            Slider { from: 0; to: 10; stepSize: 1; value: penController.smoothing; Layout.preferredWidth: 180; onMoved: penController.smoothing = Math.round(value) }
                            Label { text: penController.smoothing + "/10"; color: palette.placeholderText; Layout.preferredWidth: 42 }
                        }
                    }
                }
                ColumnLayout { Layout.preferredWidth: 320; spacing: 18
                    Card {
                        title: "Profiles"; subtitle: "One tap for how you work right now."
                        ComboBox { Layout.fillWidth: true; model: ["Balanced", "Writing", "Drawing", "Touch-first"]; currentIndex: 0; onActivated: penController.setProfile(currentText) }
                        ProfileButton { label: "Writing mode"; hint: "Maximum palm calm"; onClicked: penController.setProfile("Writing") }
                        ProfileButton { label: "Drawing mode"; hint: "Fast, expressive strokes"; onClicked: penController.setProfile("Drawing") }
                    }
                    Card {
                        title: "Buttons & hover"; subtitle: "Your shortcuts, your way."
                        Label { text: "Side action"; color: palette.placeholderText; font.pixelSize: 12 }
                        ComboBox { Layout.fillWidth: true; model: ["Undo", "Eraser", "Middle click", "Custom shortcut"]; currentIndex: model.indexOf(penController.leftButtonAction); onActivated: penController.leftButtonAction = currentText }
                        Label { text: "Rear / eraser"; color: palette.placeholderText; font.pixelSize: 12 }
                        ComboBox { Layout.fillWidth: true; model: ["Eraser", "Right click", "Redo", "Custom shortcut"]; currentIndex: model.indexOf(penController.rightButtonAction); onActivated: penController.rightButtonAction = currentText }
                        SettingRow { title: "Show hover indicator"; detail: penController.hoverAvailable ? "Live proximity" : "Waiting for axis"; checked: penController.hoverIndicator; onToggled: penController.hoverIndicator = checked }
                    }
                }
            }

            Rectangle { Layout.fillWidth: true; height: 76; radius: 22; color: "#171722"
                RowLayout { anchors.fill: parent; anchors.margins: 18; spacing: 14
                    Label { text: "✦"; color: hot; font.pixelSize: 20 }
                    ColumnLayout { Layout.fillWidth: true; spacing: 2
                        Label { text: "Sexy S-Pen is community-built"; color: "#f4f1ff"; font.weight: Font.DemiBold }
                        Label { text: "If this makes your workflow nicer, sharing the project helps it grow."; color: "#bcb7d1"; font.pixelSize: 12 }
                    }
                    RowLayout { spacing: 8
                        Button { text: "GitHub"; onClicked: Qt.openUrlExternally("https://github.com/pfn000/sexy-s-pen") }
                        Button { text: "Liberapay"; onClicked: Qt.openUrlExternally("https://liberapay.com/pfn000/") }
                    }
                }
            }
            RowLayout { Layout.fillWidth: true
                Label { text: penController.updateStatus; color: palette.placeholderText; Layout.fillWidth: true }
                Button { text: "Check updates"; onClicked: penController.checkForUpdates() }
            }
        }
    }

    component Card: Rectangle {
        property string title
        property string subtitle
        default property alias content: body.data
        Layout.fillWidth: true; radius: 24; color: card; border.color: palette.mid; border.width: 1
        implicitHeight: body.implicitHeight + 92
        ColumnLayout { id: body; anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top; anchors.margins: 22; spacing: 12
            Label { text: parent.parent.title; color: palette.text; font.pixelSize: 18; font.weight: Font.DemiBold }
            Label { text: parent.parent.subtitle; color: palette.placeholderText; font.pixelSize: 12; wrapMode: Text.WordWrap; Layout.fillWidth: true }
        }
    }
    component SettingRow: RowLayout {
        property string title; property string detail; property bool checked; signal toggled(bool checked)
        Layout.fillWidth: true
        ColumnLayout { Layout.fillWidth: true; spacing: 1; Label { text: title; color: palette.text }; Label { text: detail; color: palette.placeholderText; font.pixelSize: 11 } }
        Switch { checked: parent.checked; onToggled: parent.toggled(checked) }
    }
    component CapabilityChip: Rectangle {
        property string label; property bool enabledState
        width: 72; height: 25; radius: 12; color: enabledState ? "#e7e0ff" : palette.alternateBase
        Label { anchors.centerIn: parent; text: label; color: enabledState ? "#6248c8" : palette.placeholderText; font.pixelSize: 11 }
    }
    component ProfileButton: Button { property string label; property string hint; text: label + "  ·  " + hint; Layout.fillWidth: true }
}
