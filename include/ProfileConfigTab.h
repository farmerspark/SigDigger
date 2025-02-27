//
//    filename: description
//    Copyright (C) 2018 Gonzalo José Carracedo Carballal
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as
//    published by the Free Software Foundation, either version 3 of the
//    License, or (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful, but
//    WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public
//    License along with this program.  If not, see
//    <http://www.gnu.org/licenses/>
//
#ifndef PROFILECONFIGTAB_H
#define PROFILECONFIGTAB_H

#include <ConfigTab.h>
#include <Suscan/AnalyzerParams.h>
#include <Suscan/Source.h>

#include <QComboBox>
#include <SaveProfileDialog.h>

#define SIGDIGGER_MIN_RADIO_FREQ  -3e11
#define SIGDIGGER_MAX_RADIO_FREQ   3e11

namespace Ui {
  class ProfileConfigTab;
}

namespace SigDigger {
  class DeviceTweaks;
  class ProfileConfigTab : public ConfigTab
  {
    Q_OBJECT

    Ui::ProfileConfigTab *ui;
    DeviceTweaks         *tweaks = nullptr;
    bool modified      = false;
    bool needsRestart  = false;
    bool refreshing    = true;
    bool hasTweaks     = false;

    Suscan::Source::Config profile;
    Suscan::Source::Device remoteDevice;

    int savedLocalDeviceIndex = 0;

    SaveProfileDialog saveProfileDialog;

    void connectAll(void);

    void populateProfileCombo(void);
    void populateDeviceCombo(void);
    void populateRemoteDeviceCombo(void);

    void populateCombos(void);
    void refreshAntennas(void);
    void refreshSampRates(void);
    void refreshProfileUi(void);
    void refreshFrequencyLimits(void);
    void refreshUi(void);
    void refreshAnalyzerTypeUi(void);
    void refreshUiState(void);
    void sampRateCtlHint(int);
    void refreshTrueSampleRate(void);
    void loadProfile(Suscan::Source::Config &config);
    void guessParamsFromFileName(void);
    void updateRemoteParams(void);
    void configChanged(bool restart = false);
    bool shouldDisregardTweaks(void);

    int  findRemoteProfileIndex(void);
    unsigned int getSelectedSampleRate(void) const;
    void setSelectedSampleRate(unsigned int);

    static QString getSampRateString(qreal rate);
    static QString getBaseName(const QString &string);

  public:
    void save(void) override;

    void setUnchanged(void);
    bool hasChanged(void) const override;
    bool shouldRestart(void) const;

    void setProfile(const Suscan::Source::Config &profile);
    void setAnalyzerParams(const Suscan::AnalyzerParams &params);
    void setGain(std::string const &name, float value);
    void setFrequency(qint64 freq);
    void notifySingletonChanges(void);

    bool remoteSelected(void) const;

    float getGain(std::string const &name) const;
    Suscan::Source::Config getProfile(void) const;
    Suscan::AnalyzerParams getAnalyzerParams(void);

    explicit ProfileConfigTab(QWidget *parent = nullptr);
    ~ProfileConfigTab();

  public slots:
    void onLoadProfileClicked(void);
    void onToggleSourceType(bool);
    void onDeviceChanged(int);
    void onFormatChanged(int);
    void onAntennaChanged(int);
    void onAnalyzerTypeChanged(int);
    void onCheckButtonsToggled(bool);
    void onSpinsChanged(void);
    void onBandwidthChanged(double);
    void onBrowseCaptureFile(void);
    void onSaveProfile(void);
    void onChangeConnectionType(void);
    void onRemoteParamsChanged(void);
    void onRefreshRemoteDevices(void);
    void onRemoteProfileSelected(void);
    void onChangeSourceTimeUTC(void);
    void onDeviceTweaksClicked(void);
    void onDeviceTweaksAccepted(void);
  };
}

#endif // PROFILECONFIGTAB_H
