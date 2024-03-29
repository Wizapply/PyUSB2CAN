/*

  Copyright (c) 2015, 2016 Hubert Denkmair <hubert@denkmair.de>

  This file is part of cangaroo.

  cangaroo is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  cangaroo is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with cangaroo.  If not, see <http://www.gnu.org/licenses/>.

*/

#pragma once

class MeasurementInterface
{
public:
    MeasurementInterface();

    void cloneFrom(MeasurementInterface &origin);

    bool doConfigure() const;
    void setDoConfigure(bool doConfigure);

    bool isListenOnlyMode() const;
    void setListenOnlyMode(bool isListenOnlyMode);

    bool isOneShotMode() const;
    void setOneShotMode(bool isOneShotMode);

    bool isTripleSampling() const;
    void setTripleSampling(bool isTripleSampling);

    bool isCanFD() const;
    void setCanFD(bool isCanFD);

    unsigned bitrate() const;
    void setBitrate(unsigned bitrate);

    int samplePoint() const;
    void setSamplePoint(int samplePoint);

    unsigned fdBitrate() const;
    void setFdBitrate(unsigned fdBitrate);

    unsigned fdSamplePoint() const;
    void setFdSamplePoint(unsigned fdSamplePoint);

    bool doAutoRestart() const;
    void setAutoRestart(bool doAutoRestart);

    int autoRestartMs() const;
    void setAutoRestartMs(int autoRestartMs);

private:
    bool _doConfigure;

    unsigned _bitrate;
    unsigned _samplePoint;

    bool _isCanFD;
    unsigned _fdBitrate;
    unsigned _fdSamplePoint;

    bool _isListenOnlyMode;
    bool _isOneShotMode;
    bool _isTripleSampling;
    bool _doAutoRestart;
    int _autoRestartMs;
};
