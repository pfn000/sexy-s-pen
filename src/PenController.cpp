#include "PenController.h"

#include <QFile>
#include <QProcess>
#include <QRegularExpression>
#include <QSettings>
#include <QStandardPaths>
#include <QTimer>

namespace {
QSettings settings() {
    return QSettings(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/sexy-s-pen.ini", QSettings::IniFormat);
}
}

PenController::PenController(QObject *parent) : QObject(parent) {
    QFile config(QStringLiteral("/etc/iptsd.conf"));
    m_iptsdDetected = config.exists();
    load();
    detectBluetooth();
    auto *timer = new QTimer(this);
    timer->setInterval(5000);
    connect(timer, &QTimer::timeout, this, &PenController::detectBluetooth);
    timer->start();
    m_status = m_iptsdDetected ? QStringLiteral("Surface Linux touch service detected") : QStringLiteral("IPTSD not detected; local profile mode");
}

void PenController::load() {
    auto s = settings();
    m_stylusEnabled = s.value("stylus/enabled", m_stylusEnabled).toBool();
    m_disableOnStylus = s.value("touch/disableOnStylus", m_disableOnStylus).toBool();
    m_disableOnPalm = s.value("touch/disableOnPalm", m_disableOnPalm).toBool();
    m_gracePeriod = s.value("touch/gracePeriod", m_gracePeriod).toInt();
    m_tipDistance = s.value("stylus/tipDistance", m_tipDistance).toDouble();
    m_tipThreshold = s.value("stylus/tipThreshold", m_tipThreshold).toDouble();
    m_pressureCurve = s.value("stylus/pressureCurve", m_pressureCurve).toString();
    m_smoothing = s.value("stylus/smoothing", m_smoothing).toInt();
    m_leftButtonAction = s.value("buttons/left", m_leftButtonAction).toString();
    m_rightButtonAction = s.value("buttons/right", m_rightButtonAction).toString();
    m_hoverIndicator = s.value("hover/indicator", m_hoverIndicator).toBool();
}

void PenController::setStatus(const QString &value) { if (m_status == value) return; m_status = value; emit statusChanged(); }

#define SETTER(name, member, signal) \
void PenController::set##name(decltype(member) value) { if (member == value) return; member = value; emit signal(); }
SETTER(StylusEnabled, m_stylusEnabled, stylusEnabledChanged)
SETTER(DisableOnStylus, m_disableOnStylus, disableOnStylusChanged)
SETTER(DisableOnPalm, m_disableOnPalm, disableOnPalmChanged)
SETTER(GracePeriod, m_gracePeriod, gracePeriodChanged)
SETTER(TipDistance, m_tipDistance, tipDistanceChanged)
SETTER(TipThreshold, m_tipThreshold, tipThresholdChanged)
SETTER(PressureCurve, m_pressureCurve, pressureCurveChanged)
SETTER(Smoothing, m_smoothing, smoothingChanged)
SETTER(LeftButtonAction, m_leftButtonAction, leftButtonActionChanged)
SETTER(RightButtonAction, m_rightButtonAction, rightButtonActionChanged)
SETTER(HoverIndicator, m_hoverIndicator, hoverIndicatorChanged)
#undef SETTER

void PenController::detectBluetooth() {
    QProcess probe;
    probe.start(QStringLiteral("bluetoothctl"), {QStringLiteral("info")});
    probe.waitForFinished(700);
    const QString output = QString::fromLocal8Bit(probe.readAllStandardOutput());
    const bool connected = output.contains(QStringLiteral("Connected: yes"), Qt::CaseInsensitive);
    if (m_bluetoothConnected != connected) { m_bluetoothConnected = connected; emit bluetoothConnectedChanged(); }

    int battery = -1;
    const QString marker = QStringLiteral("Battery Percentage:");
    const int pos = output.indexOf(marker, 0, Qt::CaseInsensitive);
    if (pos >= 0) {
        const QString tail = output.mid(pos + marker.size()).trimmed();
        const int valueStart = tail.indexOf(QRegularExpression(QStringLiteral("\\d+")));
        if (valueStart >= 0) battery = tail.mid(valueStart).section(QRegularExpression(QStringLiteral("\\D")), 0, 0).toInt();
    }
    const bool available = battery >= 0 && battery <= 100;
    if (m_batteryPercent != battery) { m_batteryPercent = battery; emit batteryPercentChanged(); }
    if (m_batteryAvailable != available) { m_batteryAvailable = available; emit batteryAvailableChanged(); }
    if (connected && !available) setStatus(QStringLiteral("Pen connected · battery not reported by BlueZ"));
    else if (connected) setStatus(QStringLiteral("Pen connected · live status available"));
}

void PenController::save() {
    auto s = settings();
    s.setValue("stylus/enabled", m_stylusEnabled); s.setValue("touch/disableOnStylus", m_disableOnStylus);
    s.setValue("touch/disableOnPalm", m_disableOnPalm); s.setValue("touch/gracePeriod", m_gracePeriod);
    s.setValue("stylus/tipDistance", m_tipDistance); s.setValue("stylus/tipThreshold", m_tipThreshold);
    s.setValue("stylus/pressureCurve", m_pressureCurve); s.setValue("stylus/smoothing", m_smoothing);
    s.setValue("buttons/left", m_leftButtonAction); s.setValue("buttons/right", m_rightButtonAction);
    s.setValue("hover/indicator", m_hoverIndicator); s.sync();
    setStatus(QStringLiteral("Profile saved · system settings remain protected until explicitly applied"));
}

void PenController::reset() {
    m_stylusEnabled = true; m_disableOnStylus = true; m_disableOnPalm = true; m_gracePeriod = 1200;
    m_tipDistance = 0.0; m_tipThreshold = 0.12; m_pressureCurve = QStringLiteral("soft"); m_smoothing = 3;
    m_leftButtonAction = QStringLiteral("Undo"); m_rightButtonAction = QStringLiteral("Eraser"); m_hoverIndicator = true;
    emit stylusEnabledChanged(); emit disableOnStylusChanged(); emit disableOnPalmChanged(); emit gracePeriodChanged();
    emit tipDistanceChanged(); emit tipThresholdChanged(); emit pressureCurveChanged(); emit smoothingChanged();
    emit leftButtonActionChanged(); emit rightButtonActionChanged(); emit hoverIndicatorChanged();
    setStatus(QStringLiteral("Balanced defaults restored"));
}

void PenController::setProfile(const QString &profile) {
    if (profile == "Writing") { m_disableOnStylus = true; m_disableOnPalm = true; m_gracePeriod = 1800; m_pressureCurve = "soft"; m_smoothing = 5; }
    else if (profile == "Drawing") { m_disableOnStylus = true; m_disableOnPalm = true; m_gracePeriod = 900; m_pressureCurve = "linear"; m_smoothing = 2; }
    else if (profile == "Touch-first") { m_disableOnStylus = false; m_disableOnPalm = false; m_gracePeriod = 0; m_pressureCurve = "soft"; m_smoothing = 2; }
    else { m_disableOnStylus = true; m_disableOnPalm = true; m_gracePeriod = 1200; m_pressureCurve = "soft"; m_smoothing = 3; }
    emit disableOnStylusChanged(); emit disableOnPalmChanged(); emit gracePeriodChanged(); emit pressureCurveChanged(); emit smoothingChanged();
    setStatus(profile + QStringLiteral(" profile loaded"));
}

void PenController::pairPen() {
    QProcess::startDetached(QStringLiteral("systemsettings"), {QStringLiteral("kcm_bluetooth")});
    setStatus(QStringLiteral("Bluetooth settings opened · put the pen into pairing mode"));
}

void PenController::checkForUpdates() {
    m_updateStatus = QStringLiteral("Check the latest verified GitHub Release or run flatpak update / pacman -Syu");
    emit updateStatusChanged();
}

void PenController::announce(const QString &message) {
    setStatus(message);
}

QString PenController::integrationSummary() const {
    if (!m_iptsdDetected) return QStringLiteral("Install iptsd from linux-surface to connect palm rejection to the Surface touchscreen daemon.");
    return QStringLiteral("IPTSD detected. Pressure is available in this profile; tilt and hover unlock when the kernel/compositor reports those axes.");
}
