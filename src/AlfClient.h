// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See http://alice-o2.web.cern.ch/license for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

/// \file AlfClient.h
/// \brief Definition of ALF client related classes
///
/// \author Pascal Boeschoten (pascal.boeschoten@cern.ch)
/// \author Kostas Alexopoulos (kostas.alexopoulos@cern.ch)

#ifndef ALICEO2_ALF_ALFCLIENT_H_
#define ALICEO2_ALF_ALFCLIENT_H_

#include <boost/format.hpp>
#include <string>

#include "DimServices/DimServices.h"
#include "Util.h"

namespace roc = AliceO2::roc;

namespace AliceO2
{
namespace Alf
{

constexpr const uint32_t errHex = 0xffffffff;
constexpr const char* errString = "";

class RegisterReadRpc : DimRpcInfoWrapper
{
 public:
  RegisterReadRpc(const std::string& serviceName)
    : DimRpcInfoWrapper(serviceName)
  {
  }

  uint32_t readRegister(uint64_t registerAddress)
  {
    setString((boost::format("0x%x") % registerAddress).str());
    std::string toConvert;
    uint32_t converted;
    try {
      toConvert = stripPrefix(getString());
      converted = Util::stringToHex(toConvert);
    } catch (const AlfException& e) {
      getErrorLogger() << "RegisterReadRpc: " << boost::diagnostic_information(e, true) << endm;
      return errHex;
    }

    return converted;
  }
};

class RegisterWriteRpc : DimRpcInfoWrapper
{
 public:
  RegisterWriteRpc(const std::string& serviceName)
    : DimRpcInfoWrapper(serviceName)
  {
  }

  void writeRegister(uint64_t registerAddress, uint32_t registerValue)
  {
    setString((boost::format("0x%x%s0x%x") % registerAddress % argumentSeparator() % registerValue).str());
    try {
      getString();
    } catch (const AlfException& e) {
      getErrorLogger() << "RegisterWriteRpc: " << boost::diagnostic_information(e, true) << endm;
    }
  }
};

class ScaSequenceRpc : DimRpcInfoWrapper
{
 public:
  ScaSequenceRpc(const std::string& serviceName)
    : DimRpcInfoWrapper(serviceName)
  {
  }

  std::string write(const std::string& buffer)
  {
    setString(buffer);
    std::string ret;
    try {
      ret = getString();
    } catch (const AlfException& e) {
      getErrorLogger() << "ScaSequence: " << boost::diagnostic_information(e, true) << endm;
      return errString;
    }
    return ret;
  }

  std::string write(const std::vector<std::pair<std::string, std::string>>& sequence)
  {
    std::stringstream buffer;
    for (size_t i = 0; i < sequence.size(); ++i) {
      buffer << sequence[i].first << pairSeparator() << sequence[i].second;
      if (i + 1 < sequence.size()) {
        buffer << argumentSeparator();
      }
    }
    return write(buffer.str());
  }
};

class SwtSequenceRpc : DimRpcInfoWrapper
{
 public:
  SwtSequenceRpc(const std::string& serviceName)
    : DimRpcInfoWrapper(serviceName)
  {
  }

  std::string write(const std::string& buffer)
  {
    setString(buffer);
    std::string ret;
    try {
      ret = getString();
    } catch (const AlfException& e) {
      getErrorLogger() << "SwtSequence: " << boost::diagnostic_information(e, true) << endm;
      return errString;
    }
    return ret;
  }

  std::string write(const std::vector<std::pair<std::string, std::string>>& sequence)
  {
    std::stringstream buffer;
    for (size_t i = 0; i < sequence.size(); ++i) {
      buffer << sequence[i].first << pairSeparator() << sequence[i].second;
      if (i + 1 < sequence.size()) {
        buffer << argumentSeparator();
      }
    }
    return write(buffer.str());
  }
};

class IcSequenceRpc : DimRpcInfoWrapper
{
 public:
  IcSequenceRpc(const std::string& serviceName)
    : DimRpcInfoWrapper(serviceName)
  {
  }

  std::string write(const std::string& buffer)
  {
    setString(buffer);
    std::string ret;
    try {
      ret = getString();
    } catch (const AlfException& e) {
      getErrorLogger() << "IcSequence: " << boost::diagnostic_information(e, true) << endm;
      return errString;
    }
    return ret;
  }

  std::string write(const std::vector<std::pair<std::string, std::string>>& sequence)
  {
    std::stringstream buffer;
    for (size_t i = 0; i < sequence.size(); ++i) {
      buffer << sequence[i].first << pairSeparator() << sequence[i].second;
      if (i + 1 < sequence.size()) {
        buffer << argumentSeparator();
      }
    }
    return write(buffer.str());
  }
};

class IcGbtI2cWriteRpc : DimRpcInfoWrapper
{
 public:
  IcGbtI2cWriteRpc(const std::string& serviceName)
    : DimRpcInfoWrapper(serviceName)
  {
  }

  void write(uint32_t value)
  {
    setString((boost::format("0x%x") % value).str());
    try {
      getString();
    } catch (const AlfException& e) {
      getErrorLogger() << "IcGbtI2cWriteRpc: " << boost::diagnostic_information(e, true) << endm;
    }
  }
};

} // namespace Alf
} // namespace AliceO2

#endif // ALICEO2_ALF_ALFCLIENT_H_
