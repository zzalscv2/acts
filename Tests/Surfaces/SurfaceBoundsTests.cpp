// This file is part of the ACTS project.
//
// Copyright (C) 2017-2018 ACTS project team
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#define BOOST_TEST_MODULE Surface Bounds Tests

#include <boost/test/included/unit_test.hpp>
// leave blank line

#include <boost/test/data/test_case.hpp>
// leave blank line

#include <boost/test/output_test_stream.hpp>
// leave blank line

//
#include "ACTS/Surfaces/SurfaceBounds.hpp"
#include "ACTS/Utilities/Definitions.hpp"

namespace Acts {

/// Class to implement pure virtual method of SurfaceBounds for testing only
class SurfaceBoundsStub : public SurfaceBounds
{
public:
  /// Implement ctor and pure virtual methods of SurfaceBounds
  explicit SurfaceBoundsStub(size_t nValues = 0) : m_values(nValues)
  {
    for (size_t i = 0; i < nValues; ++i) {
      m_values[i] = i;
    }
  }
  virtual ~SurfaceBoundsStub() { /*nop*/}
  SurfaceBounds*
  clone() const final
  {
    return nullptr;
  }
  BoundsType
  type() const final
  {
    return SurfaceBounds::Other;
  }
  std::vector<TDD_real_t>
  valueStore() const
  {
    return m_values;
  }
  bool
  inside(const Vector2D& /*lpos*/, const BoundaryCheck& /*bcheck*/) const final
  {
    return true;
  }
  double
  distanceToBoundary(const Vector2D& /*lpos*/) const final
  {
    return 10.;
  }
  std::ostream&
  dump(std::ostream& sl) const final
  {
    sl << "SurfaceBoundsStub";
    return sl;
  }

private:
  std::vector<TDD_real_t> m_values;
};

namespace Test {
  BOOST_AUTO_TEST_SUITE(Surfaces)
  /// Unit test for creating compliant/non-compliant SurfaceBounds object
  BOOST_AUTO_TEST_CASE(SurfaceBoundsConstruction)
  {
    SurfaceBoundsStub u;
    SurfaceBoundsStub s(1);  // would act as size_t cast to SurfaceBounds
    SurfaceBoundsStub t(s);
    SurfaceBoundsStub v(u);
  }
  BOOST_AUTO_TEST_CASE(SurfaceBoundsProperties)
  {
    SurfaceBoundsStub       surface(5);
    std::vector<TDD_real_t> reference{0, 1, 2, 3, 4};
    BOOST_TEST(reference == surface.valueStore());
  }
  /// Unit test for testing SurfaceBounds properties
  BOOST_AUTO_TEST_CASE(SurfaceBoundsEquality)
  {
    SurfaceBoundsStub surface(1);
    SurfaceBoundsStub copiedSurface(surface);
    SurfaceBoundsStub differentSurface(2);
    BOOST_TEST(surface == copiedSurface);
    BOOST_TEST(surface != differentSurface);
    SurfaceBoundsStub assignedSurface;
    assignedSurface = surface;
    BOOST_TEST(surface == assignedSurface);
    BOOST_TEST(surface.valueStore() == assignedSurface.valueStore());
  }
  BOOST_AUTO_TEST_SUITE_END()

}  // end of namespace Test

}  // end of namespace Acts
