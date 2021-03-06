/* +------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)            |
   |                          https://www.mrpt.org/                         |
   |                                                                        |
   | Copyright (c) 2005-2019, Individual contributors, see AUTHORS file     |
   | See: https://www.mrpt.org/Authors - All rights reserved.               |
   | Released under BSD License. See: https://www.mrpt.org/License          |
   +------------------------------------------------------------------------+ */
#pragma once
#include <mrpt/serialization/CArchive.h>
#include <mrpt/core/aligned_std_vector.h>
namespace mrpt::serialization
{
CArchive& operator>>(CArchive& s, mrpt::aligned_std_vector<float>& a);
CArchive& operator<<(CArchive& s, const mrpt::aligned_std_vector<float>& a);
}  // namespace mrpt::serialization
