#pragma once

#include <QObject>
#include <QString>

class PenController final : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool iptsdDetected READ iptsdDetected NOTIFY iptsdDetectedChanged)
    Q_PROPERTY(bool bluetoothConnected READ bluetoothConnected NOTIFY bluetoothConnectedChanged)
    Q_PROPERTY(int batteryPercent READ batteryPercent NOTIFY batteryPercentChanged)
    Q_PROPERTY(bool batteryAvailable READ batteryAvailable NOTIFY batteryAvailableChanged)
    Q_PROPERTY(bool pressureAvailable READ pressureAvailable NOTIFY pressureAvailableChanged)
    Q_PROPERTY(bool tiltAvailable READ tiltAvailable NOTIFY tiltAvailableChanged)
    Q_PROPERTY(bool hoverAvailable READ hoverAvailable NOTIFY hoverAvailableChanged)
    Q_PROPERTY(bool stylusEnabled READ stylusEnabled WRITE setStylusEnabled NOTIFY stylusEnabledChanged)
    Q_PROPERTY(bool disableOnStylus READ disableOnStylus WRITE setDisableOnStylus NOTIFY disableOnStylusChanged)
    Q_PROPERTY(bool disableOnPalm READ disableOnPalm WRITE setDisableOnPalm NOTIFY disableOnPalmChanged)
    Q_PROPERTY(int gracePeriod READ gracePeriod WRITE setGracePeriod NOTIFY gracePeriodChanged)
    Q_PROPERTY(double tipDistance READ tipDistance WRITE setTipDistance NOTIFY tipDistanceChanged)
    Q_PROPERTY(double tipThreshold READ tipThreshold WRITE setTipThreshold NOTIFY tipThresholdChanged)
    Q_PROPERTY(QString pressureCurve READ pressureCurve WRITE setPressureCurve NOTIFY pressureCurveChanged)
    Q_PROPERTY(int smoothing READ smoothing WRITE setSmoothing NOTIFY smoothingChanged)
    Q_PROPERTY(QString leftButtonAction READ leftButtonAction WRITE setLeftButtonAction NOTIFY leftButtonActionChanged)
    Q_PROPERTY(QString rightButtonAction READ rightButtonAction WRITE setRightButtonAction NOTIFY rightButtonActionChanged)
    Q_PROPERTY(bool hoverIndicator READ hoverIndicator WRITE setHoverIndicator NOTIFY hoverIndicatorChanged)
    Q_PROPERTY(QString status READ status NOTIFY statusChanged)
    Q_PROPERTY(QString updateStatus READ updateStatus NOTIFY updateStatusChanged)

public:
    explicit PenController(QObject *parent = nullptr);

    bool iptsdDetected() const { return m_iptsdDetected; }
    bool bluetoothConnected() const { return m_bluetoothConnected; }
    int batteryPercent() const { return m_batteryPercent; }
    bool batteryAvailable() const { return m_batteryAvailable; }
    bool pressureAvailable() const { return m_pressureAvailable; }
    bool tiltAvailable() const { return m_tiltAvailable; }
    bool hoverAvailable() const { return m_hoverAvailable; }
    bool stylusEnabled() const { return m_stylusEnabled; }
    bool disableOnStylus() const { return m_disableOnStylus; }
    bool disableOnPalm() const { return m_disableOnPalm; }
    int gracePeriod() const { return m_gracePeriod; }
    double tipDistance() const { return m_tipDistance; }
    double tipThreshold() const { return m_tipThreshold; }
    QString pressureCurve() const { return m_pressureCurve; }
    int smoothing() const { return m_smoothing; }
    QString leftButtonAction() const { return m_leftButtonAction; }
    QString rightButtonAction() const { return m_rightButtonAction; }
    bool hoverIndicator() const { return m_hoverIndicator; }
    QString status() const { return m_status; }
    QString updateStatus() const { return m_updateStatus; }

    void setStylusEnabled(bool value); void setDisableOnStylus(bool value); void setDisableOnPalm(bool value);
    void setGracePeriod(int value); void setTipDistance(double value); void setTipThreshold(double value);
    void setPressureCurve(const QString &value); void setSmoothing(int value);
    void setLeftButtonAction(const QString &value); void setRightButtonAction(const QString &value);
    void setHoverIndicator(bool value);

    Q_INVOKABLE void save();
    Q_INVOKABLE void reset();
    Q_INVOKABLE void setProfile(const QString &profile);
    Q_INVOKABLE void pairPen();
    Q_INVOKABLE void checkForUpdates();
    Q_INVOKABLE void announce(const QString &message);
    Q_INVOKABLE QString integrationSummary() const;

signals:
    void iptsdDetectedChanged(); void bluetoothConnectedChanged(); void batteryPercentChanged();
    void batteryAvailableChanged(); void pressureAvailableChanged(); void tiltAvailableChanged();
    void hoverAvailableChanged(); void stylusEnabledChanged(); void disableOnStylusChanged();
    void disableOnPalmChanged(); void gracePeriodChanged(); void tipDistanceChanged();
    void tipThresholdChanged(); void pressureCurveChanged(); void smoothingChanged();
    void leftButtonActionChanged(); void rightButtonActionChanged(); void hoverIndicatorChanged();
    void statusChanged(); void updateStatusChanged();

private:
    void load(); void setStatus(const QString &value); void detectBluetooth();

    bool m_iptsdDetected = false;
    bool m_bluetoothConnected = false;
    int m_batteryPercent = -1;
    bool m_batteryAvailable = false;
    bool m_pressureAvailable = true;
    bool m_tiltAvailable = false;
    bool m_hoverAvailable = false;
    bool m_stylusEnabled = true;
    bool m_disableOnStylus = true;
    bool m_disableOnPalm = true;
    int m_gracePeriod = 1200;
    double m_tipDistance = 0.0;
    double m_tipThreshold = 0.12;
    QString m_pressureCurve = QStringLiteral("soft");
    int m_smoothing = 3;
    QString m_leftButtonAction = QStringLiteral("Undo");
    QString m_rightButtonAction = QStringLiteral("Eraser");
    bool m_hoverIndicator = true;
    QString m_status;
    QString m_updateStatus = QStringLiteral("Release channel ready");
};
