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
// Edited by WIZAPPLY 2024/1/6

#include "MeasurementInterface.h"


MeasurementInterface::MeasurementInterface()
  : _doConfigure(true),
    _bitrate(500000),
    _samplePoint(875),
    _isCanFD(false),
    _fdBitrate(4000000),
    _fdSamplePoint(875),

    _isListenOnlyMode(false),
    _isOneShotMode(false),
    _isTripleSampling(false),
    _doAutoRestart(false),
    _autoRestartMs(100)
{
}

unsigned MeasurementInterface::bitrate() const
{
    return _bitrate;
}

void MeasurementInterface::setBitrate(unsigned bitrate)
{
    _bitrate = bitrate;
}

void MeasurementInterface::cloneFrom(MeasurementInterface &origin)
{
    *this = origin;
}

bool MeasurementInterface::doConfigure() const
{
    return _doConfigure;
}

void MeasurementInterface::setDoConfigure(bool doConfigure)
{
    _doConfigure = doConfigure;
}

bool MeasurementInterface::isListenOnlyMode() const
{
    return _isListenOnlyMode;
}

void MeasurementInterface::setListenOnlyMode(bool isListenOnlyMode)
{
    _isListenOnlyMode = isListenOnlyMode;
}

bool MeasurementInterface::isOneShotMode() const
{
    return _isOneShotMode;
}

void MeasurementInterface::setOneShotMode(bool isOneShotMode)
{
    _isOneShotMode = isOneShotMode;
}

bool MeasurementInterface::isTripleSampling() const
{
    return _isTripleSampling;
}

void MeasurementInterface::setTripleSampling(bool isTripleSampling)
{
    _isTripleSampling = isTripleSampling;
}

bool MeasurementInterface::isCanFD() const
{
    return _isCanFD;
}

void MeasurementInterface::setCanFD(bool isCanFD)
{
    _isCanFD = isCanFD;
}

int MeasurementInterface::samplePoint() const
{
    return _samplePoint;
}

void MeasurementInterface::setSamplePoint(int samplePoint)
{
    _samplePoint = samplePoint;
}

unsigned MeasurementInterface::fdBitrate() const
{
    return _fdBitrate;
}

void MeasurementInterface::setFdBitrate(unsigned fdBitrate)
{
    _fdBitrate = fdBitrate;
}

unsigned MeasurementInterface::fdSamplePoint() const
{
    return _fdSamplePoint;
}

void MeasurementInterface::setFdSamplePoint(unsigned fdSamplePoint)
{
    _fdSamplePoint = fdSamplePoint;
}

bool MeasurementInterface::doAutoRestart() const
{
    return _doAutoRestart;
}

void MeasurementInterface::setAutoRestart(bool doAutoRestart)
{
    _doAutoRestart = doAutoRestart;
}

int MeasurementInterface::autoRestartMs() const
{
    return _autoRestartMs;
}

void MeasurementInterface::setAutoRestartMs(int autoRestartMs)
{
    _autoRestartMs = autoRestartMs;
}
