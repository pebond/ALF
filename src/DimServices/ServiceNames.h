// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See http://alice-o2.web.cern.ch/license for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

/// \file ServiceNames.h
/// \brief Definition of DIM service names
///
/// \author Pascal Boeschoten (pascal.boeschoten@cern.ch)

#ifndef ALICEO2_ALF_SRC_DIMSERVICES_SERVICENAMES_H
#define ALICEO2_ALF_SRC_DIMSERVICES_SERVICENAMES_H

#include <string>

#include "Common.h"

namespace AliceO2
{
namespace Alf
{

class ServiceNames
{
 public:
  ServiceNames(AlfLink link)
    : mAlfId(link.alfId), mSerial(link.serial), mLink(link.linkId)
  {
  }

  std::string registerRead() const;
  std::string registerWrite() const;
  std::string scaSequence() const;
  std::string swtSequence() const;
  std::string icSequence() const;
  std::string icGbtI2cWrite() const;

 private:
  std::string format(std::string name) const;
  std::string mAlfId;
  const int mSerial;
  const int mLink;
};

} // namespace Alf
} // namespace AliceO2

#endif // ALICEO2_ALF_SRC_DIMSERVICES_SERVICENAMES_H
