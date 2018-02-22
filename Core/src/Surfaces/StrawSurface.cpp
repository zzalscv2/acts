// This file is part of the ACTS project.
//
// Copyright (C) 2016-2018 ACTS project team
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

///////////////////////////////////////////////////////////////////
// StrawSurface.cpp, ACTS project
///////////////////////////////////////////////////////////////////

#include "ACTS/Surfaces/StrawSurface.hpp"

#include <iomanip>
#include <iostream>

#include "ACTS/Surfaces/InfiniteBounds.hpp"
#include "ACTS/Utilities/Identifier.hpp"

Acts::StrawSurface::StrawSurface(std::shared_ptr<const Transform3D> htrans,
                                 double                             radius,
                                 double                             halez)
  : GeometryObject(), LineSurface(htrans, radius, halez)
{
}

Acts::StrawSurface::StrawSurface(std::shared_ptr<const Transform3D> htrans,
                                 std::shared_ptr<const LineBounds>  lbounds)
  : GeometryObject(), LineSurface(htrans, lbounds)
{
}

Acts::StrawSurface::StrawSurface(std::shared_ptr<const LineBounds> lbounds,
                                 const DetectorElementBase&        detelement,
                                 const Identifier&                 id)
  : GeometryObject(), LineSurface(lbounds, detelement, id)
{
}

Acts::StrawSurface::StrawSurface(const Acts::StrawSurface& other)
  : GeometryObject(), LineSurface(other)
{
}

Acts::StrawSurface::StrawSurface(const StrawSurface& other,
                                 const Transform3D&  htrans)
  : LineSurface(other, htrans)
{
}

Acts::StrawSurface::~StrawSurface()
{
}

Acts::StrawSurface&
Acts::StrawSurface::operator=(const StrawSurface& other)
{
  if (this != &other) {
    LineSurface::operator=(other);
    m_bounds             = other.m_bounds;
  }
  return *this;
}

Acts::StrawSurface*
Acts::StrawSurface::clone(const Transform3D* shift) const
{
  if (shift) new StrawSurface(*this, *shift);
  return new StrawSurface(*this);
}
