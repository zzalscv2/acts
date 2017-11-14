// This file is part of the ACTS project.
//
// Copyright (C) 2016 ACTS project team
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

///////////////////////////////////////////////////////////////////
// SurfaceArrayCreator.h, ACTS project
///////////////////////////////////////////////////////////////////

#ifndef ACTS_TOOLS_SURFACERARRAYCREATOR_H
#define ACTS_TOOLS_SURFACERARRAYCREATOR_H 1

#include "ACTS/Surfaces/Surface.hpp"
#include "ACTS/Utilities/Definitions.hpp"
#include "ACTS/Utilities/Logger.hpp"
#include "ACTS/Utilities/Units.hpp"


namespace Acts {

namespace Test {
  struct SurfaceArrayCreatorFixture;
}

typedef BinnedArray<const Surface*> SurfaceArray;
using SurfaceMatcher
    = std::function<bool(BinningValue, const Surface*, const Surface*)>;

class BinUtility;

typedef std::vector<const Surface*> SurfaceVector;
typedef std::vector<SurfaceVector>  SurfaceMatrix;
typedef std::vector<SurfaceMatrix>  SurfaceGrid;

typedef std::vector<Vector3D> V3Vector;
typedef std::vector<V3Vector> V3Matrix;

/// @class SurfaceArrayCreator
///
/// It is designed create sub surface arrays to be ordered on Surfaces
///
/// @todo write more documentation on how this is done
class SurfaceArrayCreator
{
public:
  friend Acts::Test::SurfaceArrayCreatorFixture;

  /// Constructor
  ///
  /// @param logger logging instance
  SurfaceArrayCreator(std::unique_ptr<const Logger> logger
                      = getDefaultLogger("SurfaceArrayCreator", Logging::INFO))
    : m_logger(std::move(logger))
  {
  }

  /// Destructor
  virtual ~SurfaceArrayCreator() = default;

  /// SurfaceArrayCreator interface method
  ///
  /// - create an array in a cylinder, binned in phi, z when extremas and
  /// bin numbers are known
  /// @param surfaces is the vector of pointers to sensitive surfaces
  /// to be ordered on the cylinder
  /// @pre the pointers to the sensitive surfaces in the surfaces vectors all
  /// need to be valid, since no check is performed
  /// @param R is the radius of the cylinder
  /// @param minPhi is the minimal phi position of the surfaces
  /// @param maxPhi is the maximal phi position of the surfaces
  /// @param halfZ is the half length in z of the cylinder
  /// @param binsPhi is the number of bins in phi for the surfaces
  /// @param binsZ is the number of bin in Z for the surfaces
  /// @param transform is the (optional) additional transform applied
  ///
  /// @return a unique pointer to a new SurfaceArray
  std::unique_ptr<SurfaceArray>
  surfaceArrayOnCylinder(const std::vector<const Surface*>& surfaces,
                         double                             R,
                         double                             minPhi,
                         double                             maxPhi,
                         double                             halfZ,
                         size_t                             binsPhi,
                         size_t                             binsZ,
                         std::shared_ptr<const Transform3D> transform
                         = nullptr) const;

  /// SurfaceArrayCreator interface method
  ///
  /// - create an array in a cylinder, binned in phi, z when extremas and bin
  /// numbers are unknown - this method goes through the surfaces and finds out
  /// the needed information
  /// @param surfaces is the vector of pointers to sensitive surfaces
  /// to be ordered on the cylinder
  /// @pre the pointers to the sensitive surfaces in the surfaces vectors all
  /// need to be valid, since no check is performed
  /// @param bTypePhi the binning type in phi direction (equidistant/aribtrary)
  /// @param bTypeZ the binning type in z direction (equidistant/aribtrary)
  /// @param transform is the (optional) additional transform applied
  ///
  /// @return a unique pointer a new SurfaceArray
  std::unique_ptr<Acts::SurfaceArray>
  surfaceArrayOnCylinder(const std::vector<const Surface*>& surfaces,
                         BinningType bTypePhi    = equidistant,
                         BinningType bTypeZ      = equidistant,
                         double      envelopePhi = 0,
                         double      envelopeZ   = 0,
                         std::shared_ptr<const Transform3D> transform = nullptr,
                         SurfaceMatcher _matcher = isSurfaceEquivalent) const;

  /// SurfaceArrayCreator interface method
  /// - create an array on a disc, binned in r, phi when extremas and
  /// bin numbers are known
  ///
  /// @param surfaces is the vector of pointers to sensitive surfaces
  /// to be ordered on the disc
  /// @pre the pointers to the sensitive surfaces in the surfaces vectors all
  /// need to be valid, since no check is performed
  /// @param rMin is the minimimal radius of the disc
  /// @param rMax is the maximal radius of the disc
  /// @param minPhi is the minimal phi position of the surfaces
  /// @param maxPhi is the maximal phi position of the surfaces
  /// @param binsPhi is the number of bins in phi for the surfaces
  /// @param binsR is the number of bin in R for the surfaces
  /// @param transform is the (optional) additional transform applied
  ///
  /// @return a unique pointer a new SurfaceArray
  std::unique_ptr<SurfaceArray>
  surfaceArrayOnDisc(const std::vector<const Surface*>& surfaces,
                     double                             minR,
                     double                             maxR,
                     double                             minPhi,
                     double                             maxPhi,
                     size_t                             binsR,
                     size_t                             binsPhi,
                     std::shared_ptr<const Transform3D> transform
                     = nullptr) const;

  /// SurfaceArrayCreator interface method
  ///
  /// - create an array in a cylinder, binned in phi, r when extremas and bin
  /// numbers are unknown - this method goes through the surfaces and finds out
  /// the needed information
  /// @param surfaces is the vector of pointers to sensitive surfaces
  /// to be ordered on the disc
  /// @pre the pointers to the sensitive surfaces in the surfaces vectors all
  /// need to be valid, since no check is performed
  /// @param bTypeR the binning type in r direction (equidistant/aribtrary)
  /// @param bTypePhi the binning type in phi direction (equidistant/aribtrary)
  /// @param transform is the (optional) additional transform applied
  ///
  /// @return a unique pointer a new SurfaceArray
  std::unique_ptr<Acts::SurfaceArray>
  surfaceArrayOnDisc(const std::vector<const Surface*>& surfaces,
                     BinningType                        bTypeR,
                     BinningType                        bTypePhi,
                     double                             envelopeR   = 0,
                     double                             envelopePhi = 0,
                     std::shared_ptr<const Transform3D> transform   = nullptr,
                     SurfaceMatcher _matcher = isSurfaceEquivalent) const;

  /// SurfaceArrayCreator interface method
  /// - create an array on a plane
  ///
  /// @param surfaces is the vector of pointers to sensitive surfaces
  /// to be ordered on the plane
  /// @pre the pointers to the sensitive surfaces in the surfaces vectors all
  /// need to be valid, since no check is performed
  /// @param halflengthX is the half length in X
  /// @param halflengthY is the half length in Y
  /// @param binsX is the number of bins in X
  /// @param binsY is the number of bins in Y
  /// @param transform is the (optional) additional transform applied
  ///
  /// @return a unique pointer a new SurfaceArray
  std::unique_ptr<SurfaceArray>
  surfaceArrayOnPlane(const std::vector<const Surface*>& surfaces,
                      double                             halflengthX,
                      double                             halflengthY,
                      size_t                             binsX,
                      size_t                             binsY,
                      std::shared_ptr<const Transform3D> transform
                      = nullptr) const;

  /// Set logging instance
  /// @param logger is the logging instance to be set
  void
  setLogger(std::unique_ptr<const Logger> logger)
  {
    m_logger = std::move(logger);
  }

private:
  /// Private access to logger
  const Logger&
  logger() const
  {
    return *m_logger;
  }

  size_t
  determineBinCount(const std::vector<const Surface*>& surfaces,
                    BinningValue                       bValue,
                    SurfaceMatcher                     _matcher) const;

  /// SurfaceArrayCreator internal method
  /// Creates an arbitrary BinUtility from a vector of (unsorted) surfaces with
  /// PlanarBounds
  /// It loops through the surfaces and finds out the needed information
  /// First the surfaces are sorted in the binning direction and the so called
  /// "key" surfaces (surfaces with different positions in the binning
  /// direction) are extracted. The boundary value between two surfaces is the
  /// mean value of the two center position in the binning direction. The first
  /// and the last boundaries are calculated from the vertices of the first and
  /// last surface.
  /// @note currently implemented for phi, r and z bining
  /// @todo implement for x,y binning
  /// @param surfaces are the sensitive surfaces to be
  /// @param bValue the BinningValue in which direction should be binned
  /// (currently possible: binPhi, binR, binZ)
  /// @param transform is the (optional) additional transform applied
  /// @return a unique pointer a one dimensional BinUtility
  Acts::BinUtility
  createArbitraryBinUtility(const std::vector<const Surface*>& surfaces,
                            BinningValue                       bValue,
                            std::shared_ptr<const Transform3D> transform
                            = nullptr) const;
  /// SurfaceArrayCreator internal method
  /// Creates an equidistant BinUtility when the extremas and the bin number are
  /// It loops through the surfaces ggand finds out the needed information
  /// First the surfaces are sorted in the binning direction and the so called
  /// "key" surfaces (surfaces with different positions in the binning
  /// direction) are extracted. The number of key surfaces euqals the number of
  /// bins. Afterwards the minimum and maximum are calculated by
  /// subtracting/adding half of a bin size to the center position (in the
  /// binning direction) to the first/last surface.
  /// @note currently implemented for phi, r and z bining
  /// @todo implement for x,y binning
  /// @param surfaces are the sensitive surfaces to be
  /// @param bValue the BinningValue in which direction should be binned
  /// (currently possible: binPhi, binR, binZ)
  /// @param transform is the (optional) additional transform applied
  /// @return a unique pointer a one dimensional BinUtility
  // Acts::BinUtility
  // createEquidistantBinUtility(
  // const std::vector<const Surface*>& surfaces,
  // BinningValue                       bValue,
  // std::shared_ptr<const Transform3D> transform = nullptr) const;

  static bool
  isSurfaceEquivalent(BinningValue bValue, const Surface* a, const Surface* b)
  {

    if (bValue == Acts::binPhi)
      return (std::abs(a->center().phi() - b->center().phi()) < 10e-12);

    if (bValue == Acts::binZ)
      return (std::abs(a->center().z() - b->center().z()) < Acts::units::_um);

    if (bValue == Acts::binR)
      return (std::abs(a->center().perp() - b->center().perp())
              < Acts::units::_um);

    return false;
  }

  // overload with matcher lambda, since default value / noop can not be
  // set
  Acts::BinUtility
  createEquidistantBinUtility(const std::vector<const Surface*>& surfaces,
                              BinningValue                       bValue,
                              double envelope = 0,
                              std::shared_ptr<const Transform3D> transform
                              = nullptr,
                              SurfaceMatcher matcher
                              = isSurfaceEquivalent) const;

  /// SurfaceArrayCreator internal method
  /// - create an equidistant BinUtility with all parameters given
  /// - if parameters are known this function is preferred
  /// currently implemented for phi, r and z bining
  /// @todo implement for x,y binning
  /// @param surfaces are the sensitive surfaces to be
  /// @param bValue the BinningValue in which direction should be binned
  /// (currently possible: binPhi, binR, binZ)
  /// @param bType the BinningType (equidistant or arbitrary binning)
  /// @param bins the number of bins
  /// @param min is the minimal position of the surfaces in the binning
  /// direction
  /// @param max is the maximal position of the surfaces in the binning
  /// direction
  /// @param transform is the (optional) additional transform applied
  /// @return a unique pointer a one dimensional BinUtility
  Acts::BinUtility
  createBinUtility(const std::vector<const Surface*>& surfaces,
                   BinningValue                       bValue,
                   BinningType                        bType,
                   size_t                             bins,
                   double                             min,
                   double                             max,
                   std::shared_ptr<const Transform3D> transform
                   = nullptr) const;

  /// logging instance
  std::unique_ptr<const Logger> m_logger;

  /// Private helper method to complete the binning
  ///
  /// @todo implement closest neighbour search
  ///
  ///  given a grid point o
  ///    |  0  |  1 |  2  |  3 |  4  |
  ///    ------------------------------
  ///  0 |  x  |    |     |    |  x  |
  ///  1 |     |    |  o  |    |     |
  ///  2 |  x  |    |     |    |  x  |
  ///
  /// This is being called when you chose to use more bins thans surfaces
  /// I.e. to put a finer granularity binning onto your surface
  /// Neighbour bins are then filled to contain pointers as well
  /// @param binUtility is the utility class that describes the binning
  /// @param v3Matrix the corresponding 3D positions filled for every grid point
  /// @param sVector is the filled vector of Surface and binning position
  /// @param sGrid the surfaces filled for every grid point
  /// binSystem is the full system of bins
  void
  completeBinning(const BinUtility&    binUtility,
                  const V3Matrix&      v3Matrix,
                  const SurfaceVector& sVector,
                  SurfaceGrid&         sGrid) const;

  /// Private helper method to complete the binning
  ///
  ///
  /// @todo write documentation
  ///
  void
  registerNeighbourHood(SurfaceArray& sArray) const;

  /// Private helper method to transform the  vertices of surface bounds into
  /// global coordinates
  /// @param surface the surface associated with the given vertices
  /// @param locVertices a vector of the vertices in local coordinates
  /// @return a vector of the vertices in global coordinates
  std::vector<Acts::Vector3D>
  makeGlobalVertices(const Acts::Surface&               surface,
                     const std::vector<Acts::Vector2D>& locVertices) const;
};

}  // namespace Acts

#endif  // ACTS_TOOLS_SURFACERARRAYCREATOR_H
